#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/Operator.hpp"
#include "cli/OperatorProperty.hpp"

namespace Verkstan
{
    OperatorInput::OperatorInput(int index,
                                 Constants::OperatorTypes type,
                                 bool infinite,
                                 bool optional)
    {
        Index = index;
        Type = type;
        Infinite = infinite;
        Optional = optional;
    }

    Operator::Operator(String^ typeName,
                       int operatorId,
                       Constants::OperatorTypes type)
    {
        this->typeName = typeName;
        this->id = operatorId;
        this->type = type;
        this->properties = gcnew List<OperatorProperty^>();
        this->name = "";
        this->displayName = typeName;
    }

    Operator::~Operator()
    {

    }

    String^ Operator::Name::get()
    {
        return name;
    }

    String^ Operator::DisplayName::get()
    {
        return displayName;
    }

    void Operator::Name::set(String^ name)
    {
        this->name = name;
    }

    int Operator::Id::get()
    {
        return id;
    }

    List<OperatorProperty^>^ Operator::Properties::get() 
    {
        return properties;
    }

    String^ Operator::TypeName::get() 
    {
        return typeName;
    }

    Constants::OperatorTypes Operator::Type::get() 
    {
        return type;
    }

    void Operator::AddProperty(String^ name, Constants::OperatorPropertyTypes type)
    {
        OperatorProperty^ prop = gcnew OperatorProperty(this,
                                                        properties->Count,
                                                        name,
                                                        type);
        properties->Add(prop);
    }

    void Operator::AddEnumProperty(String^ name, List<String^>^ values)
    {
        OperatorProperty^ prop = gcnew OperatorProperty(this,
                                                        properties->Count,
                                                        name,
                                                        Constants::OperatorPropertyTypes::Enum,
                                                        values);
        properties->Add(prop);
    }

    unsigned char Operator::GetByteProperty(int index)
    {
        return 0;
    }

    void Operator::SetByteProperty(int index, unsigned char value)
    {

    }

    int Operator::GetIntProperty(int index)
    {
         return 0;
    }

    void Operator::SetIntProperty(int index, int value)
    {

    }

    float Operator::GetFloatProperty(int index)
    {
        return 0.0f;
    }

    void Operator::SetFloatProperty(int index, float value)
    {

    }

    String^ Operator::GetStringProperty(int index)
    {   
        return gcnew String("");   
    }

    void Operator::SetStringProperty(int index, String^ string)
    {
      
    }

    Vector^ Operator::GetVectorProperty(int index)
    {
        return gcnew Vector();
    }

    void Operator::SetVectorProperty(int index, Vector^ vector)
    {

    }

    Color^ Operator::GetColorProperty(int index)
    {
        return gcnew Color();
    }

    void Operator::SetColorProperty(int index, Color^ color)
    {

    }
}