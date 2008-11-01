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

    Operator::Operator(String^ name,
                       String^ typeName,
                       int operatorId,
                       Constants::OperatorTypes type)
    {
        this->Name = name;
        this->typeName = typeName;
        DisplayName = name;
        this->id = operatorId;
        this->type = type;
        this->properties = gcnew List<OperatorProperty^>();
    }

    Operator::~Operator()
    {

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
}