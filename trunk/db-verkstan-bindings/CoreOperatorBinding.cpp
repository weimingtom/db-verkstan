#include "core.hpp"

#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "CoreOperatorBinding.hpp"

namespace VerkstanBindings
{
    CoreOperatorBinding::CoreOperatorBinding(String^ name,
                                             int operatorId,
                                             Constants::OperatorTypes type,
                                             List<OperatorBindingProperty^>^ properties,
                                             List<OperatorBindingInput^>^ inputs)
                                             : OperatorBinding(name, operatorId, type, properties)
    {
        this->dirty = true;
        this->inputs = inputs;

        inputConnections = gcnew List<OperatorBinding^>();
        outputConnections = gcnew List<OperatorBinding^>();
    }

    CoreOperatorBinding::~CoreOperatorBinding()
    {
        delete operators[Id];
        operators[Id] = 0;
    }

    void CoreOperatorBinding::CascadeProcess()
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

    void CoreOperatorBinding::Process()
    {
        operators[Id]->process();
    }

    void CoreOperatorBinding::SetDirty(bool dirty)
    {
        this->dirty = dirty;

        for (int i = 0; i < outputConnections->Count; i++)
            outputConnections[i]->SetDirty(dirty);
    }

    bool CoreOperatorBinding::IsDirty()
    {
        return dirty;
    }

    unsigned char CoreOperatorBinding::GetByteProperty(int index)
    {
        return operators[Id]->getByteProperty(index);
    }

    void CoreOperatorBinding::SetByteProperty(int index, unsigned char value)
    {
        SetDirty(true);
        operators[Id]->setByteProperty(index, value); 
    }

    int CoreOperatorBinding::GetIntProperty(int index)
    {
         return operators[Id]->getIntProperty(index);
    }

    void CoreOperatorBinding::SetIntProperty(int index, int value)
    {
        SetDirty(true);
        operators[Id]->setIntProperty(index, value); 
    }

    float CoreOperatorBinding::GetFloatProperty(int index)
    {
        return operators[Id]->getFloatProperty(index);
    }

    void CoreOperatorBinding::SetFloatProperty(int index, float value)
    {
        SetDirty(true);
        operators[Id]->setFloatProperty(index, value); 
    }

    String^ CoreOperatorBinding::GetStringProperty(int index)
    {   
        return gcnew String(operators[Id]->getStringProperty(index));   
    }

    void CoreOperatorBinding::SetStringProperty(int index, String^ string)
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

        operators[Id]->setStringProperty(index, ch); 
    }

    void CoreOperatorBinding::flushInputConnections()
    {
        for (int i = 0; i < operators[Id]->numberOfInputs; i++)
            operators[Id]->inputs[i] = -1;

        for (int i = 0; i < inputConnections->Count; i++)
        {
            OperatorBinding^ ob = inputConnections[i];
            bool accepted = false;
            int j = 0;
            for (j; j < inputs->Count; j++)
            {
                if (inputs[j]->Type == ob->Type
                    && operators[Id]->inputs[j] == -1)
                {
                    operators[Id]->inputs[j] = ob->Id;
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
                    if (operators[Id]->inputs[j] == -1)
                    {
                        operators[Id]->inputs[j] = ob->Id;
                        accepted = true;
                        break;
                    }
                }
            }
        }

        operators[Id]->numberOfInputs= inputConnections->Count;
        SetDirty(true);
    }

    void CoreOperatorBinding::flushOutputConnections()
    {
        for (int i = 0; i < operators[Id]->numberOfOutputs; i++)
            operators[Id]->outputs[i] = -1;

        for (int i = 0; i < outputConnections->Count; i++)
            operators[Id]->outputs[i] = outputConnections[i]->Id;
       
        operators[Id]->numberOfOutputs = outputConnections->Count;
    }

    void CoreOperatorBinding::ConnectInWith(OperatorBinding^ operatorBinding)
    {
        if (inputs->Count == 0)
            return;

        bool accepted = false;
        int i = 0;
        for (i; i < inputs->Count; i++)
        {
            if (inputs[i]->Type == operatorBinding->Type
                && operators[Id]->inputs[i] == -1)
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
                if (operators[Id]->inputs[i] == -1)
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

    void CoreOperatorBinding::ConnectOutWith(OperatorBinding^ operatorBinding)
    {
        outputConnections->Add(operatorBinding);
        
        flushOutputConnections();

        operatorBinding->ConnectInWith(this);
    }

    void CoreOperatorBinding::DisconnectInFrom(OperatorBinding^ operatorBinding)
    {
        inputConnections->Remove(operatorBinding);
        flushInputConnections();
    }

    void CoreOperatorBinding::DisconnectOutFrom(OperatorBinding^ operatorBinding)
    {
        outputConnections->Remove(operatorBinding);
        flushOutputConnections();
    }

    void CoreOperatorBinding::Disconnect()
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

    bool CoreOperatorBinding::IsProcessable()
    {
        bool result = inputs->Count == operators[Id]->numberOfInputs;

        for (int i = 0; i < inputConnections->Count; i++)
            result &= inputConnections[i]->IsProcessable();

        return result;
    }

    Operator* CoreOperatorBinding::getOperator()
    {
        return operators[Id];
    }
}