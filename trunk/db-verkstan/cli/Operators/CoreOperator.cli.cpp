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
        delete VerkstanCore::operators[Id];
        VerkstanCore::operators[Id] = 0;
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
        VerkstanCore::operators[Id]->process();
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
        return VerkstanCore::operators[Id]->getByteProperty(index);
    }

    void CoreOperator::SetByteProperty(int index, unsigned char value)
    {
        SetDirty(true);
        VerkstanCore::operators[Id]->setByteProperty(index, value); 
    }

    int CoreOperator::GetIntProperty(int index)
    {
         return VerkstanCore::operators[Id]->getIntProperty(index);
    }

    void CoreOperator::SetIntProperty(int index, int value)
    {
        SetDirty(true);
        VerkstanCore::operators[Id]->setIntProperty(index, value); 
    }

    float CoreOperator::GetFloatProperty(int index)
    {
        return VerkstanCore::operators[Id]->getFloatProperty(index);
    }

    void CoreOperator::SetFloatProperty(int index, float value)
    {
        SetDirty(true);
        VerkstanCore::operators[Id]->setFloatProperty(index, value); 
    }

    String^ CoreOperator::GetStringProperty(int index)
    {   
        return gcnew String(VerkstanCore::operators[Id]->getStringProperty(index));   
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

        VerkstanCore::operators[Id]->setStringProperty(index, ch); 
    }

    void CoreOperator::flushInputConnections()
    {
        for (int i = 0; i < VerkstanCore::operators[Id]->numberOfInputs; i++)
            VerkstanCore::operators[Id]->inputs[i] = -1;

        for (int i = 0; i < inputConnections->Count; i++)
        {
            Operator^ ob = inputConnections[i];
            bool accepted = false;
            int j = 0;
            for (j; j < inputs->Count; j++)
            {
                if (inputs[j]->Type == ob->Type
                    && VerkstanCore::operators[Id]->inputs[j] == -1)
                {
                    VerkstanCore::operators[Id]->inputs[j] = ob->Id;
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
                    if (VerkstanCore::operators[Id]->inputs[j] == -1)
                    {
                        VerkstanCore::operators[Id]->inputs[j] = ob->Id;
                        accepted = true;
                        break;
                    }
                }
            }
        }

        VerkstanCore::operators[Id]->numberOfInputs= inputConnections->Count;
        SetDirty(true);
    }

    void CoreOperator::flushOutputConnections()
    {
        for (int i = 0; i < VerkstanCore::operators[Id]->numberOfOutputs; i++)
            VerkstanCore::operators[Id]->outputs[i] = -1;

        for (int i = 0; i < outputConnections->Count; i++)
            VerkstanCore::operators[Id]->outputs[i] = outputConnections[i]->Id;
       
        VerkstanCore::operators[Id]->numberOfOutputs = outputConnections->Count;
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
                && VerkstanCore::operators[Id]->inputs[i] == -1)
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
                if (VerkstanCore::operators[Id]->inputs[i] == -1)
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

        operatorBinding->ConnectOutWith(this);
    }

    void CoreOperator::ConnectOutWith(Operator^ operatorBinding)
    {
        outputConnections->Add(operatorBinding);
        
        flushOutputConnections();

        operatorBinding->ConnectInWith(this);
    }

    void CoreOperator::DisconnectInFrom(Operator^ operatorBinding)
    {
        inputConnections->Remove(operatorBinding);
        flushInputConnections();
    }

    void CoreOperator::DisconnectOutFrom(Operator^ operatorBinding)
    {
        outputConnections->Remove(operatorBinding);
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
        bool result = inputs->Count == VerkstanCore::operators[Id]->numberOfInputs;

        for (int i = 0; i < inputConnections->Count; i++)
            result &= inputConnections[i]->IsProcessable();

        return result;
    }

    VerkstanCore::Operator* CoreOperator::getOperator()
    {
        return VerkstanCore::operators[Id];
    }
}