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
        operators[Id]->cascadeProcess();
    }

    unsigned char CoreOperatorBinding::GetByteProperty(int index)
    {
        return operators[Id]->getByteProperty(index);
    }

    void CoreOperatorBinding::SetByteProperty(int index, unsigned char byteValue)
    {
        operators[Id]->setByteProperty(index, byteValue); 
    }

    int CoreOperatorBinding::GetIntProperty(int index)
    {
         return operators[Id]->getIntProperty(index);
    }

    void CoreOperatorBinding::SetIntProperty(int index, int intValue)
    {
        operators[Id]->setIntProperty(index, intValue); 
    }

    float CoreOperatorBinding::GetFloatProperty(int index)
    {
        return operators[Id]->getFloatProperty(index);
    }

    void CoreOperatorBinding::SetFloatProperty(int index, float floatValue)
    {
        operators[Id]->setFloatProperty(index, floatValue); 
    }

    String^ CoreOperatorBinding::GetStringProperty(int index)
    {   
        return gcnew String(operators[Id]->getTextProperty(index));   
    }

    void CoreOperatorBinding::SetStringProperty(int index, String^ string)
    {
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

        operators[Id]->setTextProperty(index, ch); 
    }

    void CoreOperatorBinding::flushInputConnections()
    {
        for (int i = 0; i < operators[Id]->numberOfInConnections; i++)
            operators[Id]->inConnections[i] = -1;

        for (int i = 0; i < inputConnections->Count; i++)
        {
            OperatorBinding^ ob = inputConnections[i];
            bool accepted = false;
            int j = 0;
            for (j; j < inputs->Count; j++)
            {
                if (inputs[j]->Type == ob->Type
                    && operators[Id]->inConnections[j] == -1)
                {
                    operators[Id]->inConnections[j] = ob->Id;
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
                    if (operators[Id]->inConnections[j] == -1)
                    {
                        operators[Id]->inConnections[j] = ob->Id;
                        accepted = true;
                        break;
                    }
                }
            }
        }

        operators[Id]->numberOfInConnections = inputConnections->Count;
        operators[Id]->setDirty(true);
    }

    void CoreOperatorBinding::flushOutputConnections()
    {
        for (int i = 0; i < operators[Id]->numberOfOutConnections; i++)
            operators[Id]->outConnections[i] = -1;

        for (int i = 0; i < outputConnections->Count; i++)
            operators[Id]->outConnections[i] = outputConnections[i]->Id;
       
        operators[Id]->numberOfOutConnections = outputConnections->Count;
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
                && operators[Id]->inConnections[i] == -1)
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
                if (operators[Id]->inConnections[i] == -1)
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
        bool result = inputs->Count == operators[Id]->numberOfInConnections;

        for (int i = 0; i < inputConnections->Count; i++)
            result &= inputConnections[i]->IsProcessable();

        return result;
    }
}