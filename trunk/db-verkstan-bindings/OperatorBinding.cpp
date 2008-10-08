#include "core.hpp"
#include "flatoperator.hpp"
#include "pixelsoperator.hpp"
#include "textoperator.hpp"
#include "rotozoomoperator.hpp"

#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "OperatorBinding.hpp"

namespace VerkstanBindings
{
    OperatorBindingProperty::OperatorBindingProperty(int index, 
                                                     String^ name, 
                                                     Constants::OperatorPropertyTypes type)
    {
        Name = name;
        Type = type;
        Index = index;
    }

    OperatorBindingInput::OperatorBindingInput(int index,
                                               Constants::OperatorTypes type,
                                               bool infinite)
    {
        Index = index;
        Type = type;
        Infinite = infinite;
    }

    OperatorBinding::OperatorBinding(String^ name,
                                     int operatorId,
                                     Constants::OperatorTypes type,
                                     List<OperatorBindingProperty^>^ properties,
                                     List<OperatorBindingInput^>^ inputs)
    {
        this->name = name;
        this->id = operatorId;
        this->properties = properties;
        this->inputs = inputs;

        inputConnections = gcnew List<OperatorBinding^>();
        outputConnections = gcnew List<OperatorBinding^>();
    }

    OperatorBinding::~OperatorBinding()
    {
        delete operators[id];
        operators[id] = 0;
    }

    unsigned char OperatorBinding::GetByteProperty(int index)
    {
        return operators[id]->getByteProperty(index);
    }

    void OperatorBinding::SetByteProperty(int index, unsigned char byteValue)
    {
        operators[id]->setByteProperty(index, byteValue); 
    }

    int OperatorBinding::GetIntProperty(int index)
    {
         return operators[id]->getIntProperty(index);
    }

    void OperatorBinding::SetIntProperty(int index, int intValue)
    {
        operators[id]->setIntProperty(index, intValue); 
    }

    float OperatorBinding::GetFloatProperty(int index)
    {
        return operators[id]->getFloatProperty(index);
    }

    void OperatorBinding::SetFloatProperty(int index, float floatValue)
    {
        operators[id]->setFloatProperty(index, floatValue); 
    }

    String^ OperatorBinding::GetStringProperty(int index)
    {   
        return gcnew String(operators[id]->getTextProperty(index));   
    }

    void OperatorBinding::SetStringProperty(int index, String^ string)
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

        operators[id]->setTextProperty(index, ch); 
    }

    int OperatorBinding::Id::get()
    {
        return id;
    }

    List<OperatorBindingProperty^>^ OperatorBinding::Properties::get() 
    {
        return properties;
    }

    String^ OperatorBinding::Name::get() 
    {
        return name;
    }

    Constants::OperatorTypes OperatorBinding::Type::get() 
    {
        return type;
    }

    void OperatorBinding::flushInputConnections()
    {
        for (int i = 0; i < operators[id]->numberOfInConnections; i++)
            operators[id]->inConnections[i] = -1;

        for (int i = 0; i < inputConnections->Count; i++)
        {
            OperatorBinding^ ob = inputConnections[i];
            bool accepted = false;
            int j = 0;
            for (j; j < inputs->Count; j++)
            {
                if (inputs[j]->Type == ob->Type
                    && operators[id]->inConnections[j] == -1)
                {
                    operators[id]->inConnections[j] = ob->id;
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
                    if (operators[id]->inConnections[j] == -1)
                    {
                        operators[id]->inConnections[j] = ob->id;
                        accepted = true;
                        break;
                    }
                }
            }
        }

        operators[id]->numberOfInConnections = inputConnections->Count;
        operators[id]->setDirty(true);
    }

    void OperatorBinding::flushOutputConnections()
    {
        for (int i = 0; i < operators[id]->numberOfOutConnections; i++)
            operators[id]->outConnections[i] = -1;

        for (int i = 0; i < outputConnections->Count; i++)
            operators[id]->outConnections[i] = outputConnections[i]->Id;
       
        operators[id]->numberOfOutConnections = outputConnections->Count;
    }

    void OperatorBinding::ConnectInWith(OperatorBinding^ operatorBinding)
    {
        if (inputs->Count == 0)
            return;

        bool accepted = false;
        int i = 0;
        for (i; i < inputs->Count; i++)
        {
            if (inputs[i]->Type == operatorBinding->Type
                && operators[id]->inConnections[i] == -1)
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
                if (operators[id]->inConnections[i] == -1)
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

    void OperatorBinding::ConnectOutWith(OperatorBinding^ operatorBinding)
    {
        outputConnections->Add(operatorBinding);
        
        flushOutputConnections();

        operatorBinding->ConnectInWith(this);
    }

    void OperatorBinding::DisconnectInFrom(OperatorBinding^ operatorBinding)
    {
        inputConnections->Remove(operatorBinding);
        flushInputConnections();
    }

    void OperatorBinding::DisconnectOutFrom(OperatorBinding^ operatorBinding)
    {
        outputConnections->Remove(operatorBinding);
        flushOutputConnections();
    }

    void OperatorBinding::Disconnect()
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

    bool OperatorBinding::IsProcessable()
    {
        bool result = inputs->Count == operators[id]->numberOfInConnections;

        for (int i = 0; i < inputConnections->Count; i++)
            result &= inputConnections[i]->IsProcessable();

        return result;
    }
}