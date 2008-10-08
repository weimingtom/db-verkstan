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

    OperatorBinding::OperatorBinding(String^ name,
                                     int operatorId,
                                     Constants::OperatorTypes type,
                                     List<OperatorBindingProperty^>^ properties,
                                     List<Constants::OperatorTypes>^ inConnectionTypes)
    {
        this->name = name;
        this->id = operatorId;
        this->properties = properties;
        this->inConnectionTypes = inConnectionTypes;
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

    void OperatorBinding::ConnectInWith(OperatorBinding^ operatorBinding)
    {
        /*
        bool connectionAccepted = false;
        for (int i = 0; i < inConnectionTypes->Count; i++)
        {
            if (inConnectionTypes[i] == operatorBinding->Type
                operators[id]->inConnections[i] == -1)
            {
                operators[id]->inConnections[i] = operatorBinding->id;
                connectionAccepted = true;
                break;
            }
        }

        if (!connectionAccepted)
            return;

        operators[id]->numberOfInConnections++;
        */
    }

    void OperatorBinding::ConnectOutWith(OperatorBinding^ operatorBinding)
    {
        /*
        bool connectionAccepted = fasle;
        for (int i = 0; i < operatorBinding->InConnectionTypes->Count; i++)
        {
            if (type == operatorBinding->InConnectionTypes[i]
            {
                connectionAccepted = true;
                break;
            }
        }

        if (!connectionAccepted)
            return;

        operators[i]->outConnections[operators[id]->numberOfOutConnections] = operatorBinding->Id;
        operators[id]->numberOfOutConnections++;
        */
    }

    void OperatorBinding::DisconnectOutFrom(OperatorBinding^ operatorBinding)
    {
        /*
        int id = operatorBinding->Id;

        for (int i = 0; i < operators[id]->numberOfOutConnections; i++)
        {
            if (id == operators[id]->outConnections[i])
            {
                operators[id]->outConnections[i] = -1;
            }
        }
*/

    }

    bool OperatorBinding::IsProcessable()
    {
      // return inConnectionTypes->Count == operators[id]->numberOfInConnections;
        return false;
    }

    List<Constants::OperatorTypes>^ OperatorBinding::InConnectionTypes::get() 
    { 
        return inConnectionTypes;
    }

    List<int>^ OperatorBinding::InConnectionIds::get()
    { 
        List<int>^ result = gcnew List<int>();
      //  for (int i = 0; i < operators[id]->numberOfInConnections; i++)
       //     result->Add(operators[id]->inConnections[i]);
        return result;
    }

    List<int>^ OperatorBinding::OutConnectionIds::get()
    { 
         List<int>^ result = gcnew List<int>();
        // for (int i = 0; i < operators[id]->numberOfOutConnections; i++)
        //    result->Add(operators[id]->outConnections[i]);
        return result;
    }
}