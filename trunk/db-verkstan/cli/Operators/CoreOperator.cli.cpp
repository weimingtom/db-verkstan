#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/Operators/CoreOperator.hpp"

namespace Verkstan
{
    CoreOperator::CoreOperator(String^ name,
                                 int operatorId,
                                 Constants::OperatorTypes type,
                                 List<OperatorProperty^>^ properties,
                                 List<OperatorInput^>^ inputs)
                                 : Operator(name, operatorId, type, properties)
    {
        this->dirty = true;
        this->inputs = inputs;

        inputConnections = gcnew List<Operator^>();
        outputConnections = gcnew List<Operator^>();
    }

    CoreOperator::~CoreOperator()
    {
        Disconnect();

        delete Core::operators[Id];
        Core::operators[Id] = 0;
    }

    void CoreOperator::CascadeProcess()
    {
        if (!dirty)
            return;

        for (int i = 0; i < inputConnections->Count; i++)
            inputConnections[i]->CascadeProcess();
        
        if (IsProcessable())
        {
            Process();
            dirty = false;
        }
    }

    void CoreOperator::Process()
    {
        getOperator()->process();
    }

    void CoreOperator::SetDirty(bool dirty)
    {
        this->dirty = dirty;

        for (int i = 0; i < outputConnections->Count; i++)
            outputConnections[i]->SetDirty(dirty);
    }

    bool CoreOperator::IsDirty()
    {
        return dirty;
    }

    unsigned char CoreOperator::GetByteProperty(int index)
    {
        return getOperator()->getByteProperty(index);
    }

    void CoreOperator::SetByteProperty(int index, unsigned char value)
    {
        SetDirty(true);
        getOperator()->setByteProperty(index, value); 
    }

    int CoreOperator::GetIntProperty(int index)
    {
         return getOperator()->getIntProperty(index);
    }

    void CoreOperator::SetIntProperty(int index, int value)
    {
        SetDirty(true);
        getOperator()->setIntProperty(index, value); 
    }

    float CoreOperator::GetFloatProperty(int index)
    {
        return getOperator()->getFloatProperty(index);
    }

    void CoreOperator::SetFloatProperty(int index, float value)
    {
        SetDirty(true);
        getOperator()->setFloatProperty(index, value); 
    }

    String^ CoreOperator::GetStringProperty(int index)
    {   
        return gcnew String(getOperator()->getStringProperty(index));   
    }

    void CoreOperator::SetStringProperty(int index, String^ string)
    {
        SetDirty(true);

        // Pin memory so GC can't move it while native function is called
        pin_ptr<const wchar_t> wch = PtrToStringChars(string);
     
        // Conversion to char* :
        // Can just convert wchar_t* to char* using one of the 
        // conversion functions such as: 
        // WideCharToMultiByte()
        // wcstombs_s()
        // ... etc
        size_t convertedChars = 0;
        size_t sizeInBytes = ((string->Length + 1) * 2);
        errno_t err = 0;
        char *ch = (char*)malloc(sizeInBytes);

        err = wcstombs_s(&convertedChars, 
                         ch, 
                         sizeInBytes,
                         wch, 
                         sizeInBytes);

        getOperator()->setStringProperty(index, ch); 
    }

    void CoreOperator::flushInputConnections()
    {
        for (int i = 0; i < getOperator()->numberOfInputs; i++)
            getOperator()->inputs[i] = -1;

        for (int i = 0; i < inputConnections->Count; i++)
        {
            Operator^ ob = inputConnections[i];
            bool accepted = false;
            int j = 0;
            for (j; j < inputs->Count; j++)
            {
                if (inputs[j]->Type == ob->Type
                    && getOperator()->inputs[j] == -1)
                {
                    getOperator()->inputs[j] = ob->Id;
                    accepted = true;
                    break;
                }
            }

			j--;

            if (!accepted 
                && inputs[j]->Infinite
                && inputs[j]->Type == ob->Type)
            {
                for (j; j < DB_MAX_OPERATOR_CONNECTIONS; j++)
                {
                    if (getOperator()->inputs[j] == -1)
                    {
                        getOperator()->inputs[j] = ob->Id;
                        accepted = true;
                        break;
                    }
                }
            }
        }

        getOperator()->numberOfInputs= inputConnections->Count;
        SetDirty(true);
    }

    void CoreOperator::flushOutputConnections()
    {
        for (int i = 0; i < getOperator()->numberOfOutputs; i++)
            getOperator()->outputs[i] = -1;

        for (int i = 0; i < outputConnections->Count; i++)
            getOperator()->outputs[i] = outputConnections[i]->Id;
       
        getOperator()->numberOfOutputs = outputConnections->Count;
    }

    void CoreOperator::ConnectInWith(Operator^ operatorBinding)
    {
        if (inputs->Count == 0)
            return;

        bool accepted = false;
        int i = 0;
        for (i; i < inputs->Count; i++)
        {
            if (inputs[i]->Type == operatorBinding->Type
                && getOperator()->inputs[i] == -1)
            {
                inputConnections->Add(operatorBinding);
                accepted = true;
                break;
            }
        }

        i--;

        if (!accepted 
            && inputs[i]->Infinite
            && inputs[i]->Type == operatorBinding->Type)
        {
            for (i; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
            {
                if (getOperator()->inputs[i] == -1)
                {
                    inputConnections->Add(operatorBinding);
                    accepted = true;
                    break;
                }
            }
        }
             
        if (!accepted)
            return;

        flushInputConnections();
    }

    void CoreOperator::ConnectOutWith(Operator^ op)
    {
        outputConnections->Add(op);
        
        flushOutputConnections();
    }

    void CoreOperator::DisconnectInFrom(Operator^ op)
    {
        inputConnections->Remove(op);
        flushInputConnections();
    }

    void CoreOperator::DisconnectIns()
    {
        inputConnections->Clear();
        flushInputConnections();
    }

    void CoreOperator::DisconnectOutFrom(Operator^ op)
    {
        outputConnections->Remove(op);
        flushOutputConnections();
    }

    void CoreOperator::Disconnect()
    {
        for (int i = 0; i < inputConnections->Count; i++)
            inputConnections[i]->DisconnectOutFrom(this);
        inputConnections->Clear();
        flushInputConnections();

        for (int i = 0; i < outputConnections->Count; i++)
            outputConnections[i]->DisconnectInFrom(this);
        outputConnections->Clear();
        flushOutputConnections();
    }

    bool CoreOperator::IsProcessable()
    {
        if (!inputs->Count == inputConnections->Count)
            return false;

        for (int i = 0; i < inputConnections->Count; i++)
            if (!inputConnections[i]->IsProcessable())
                return false;

        return true;
    }

    Core::Operator* CoreOperator::getOperator()
    {
        return Core::operators[Id];
    }
}