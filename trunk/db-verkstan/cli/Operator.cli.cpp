#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/Operator.hpp"

namespace Verkstan
{
    OperatorProperty::OperatorProperty(int index, 
                                       String^ name, 
                                       Constants::OperatorPropertyTypes type)
    {
        Name = name;
        Type = type;
        Index = index;
    }

    OperatorInput::OperatorInput(int index,
                                 Constants::OperatorTypes type,
                                 bool infinite)
    {
        Index = index;
        Type = type;
        Infinite = infinite;
    }

    Operator::Operator(String^ name,
                       int operatorId,
                       Constants::OperatorTypes type,
                       Constants::OperatorTypes internalType,
                       List<OperatorProperty^>^ properties)
    {
        this->name = name;
        DisplayName = name;
        this->id = operatorId;
        this->type = type;
        this->internalType = internalType;
        this->properties = properties;
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

    String^ Operator::Name::get() 
    {
        return name;
    }

    Constants::OperatorTypes Operator::Type::get() 
    {
        return type;
    }

    Constants::OperatorTypes Operator::InternalType::get() 
    {
        return internalType;
    }

    int Operator::GetColorProperty(int index)
    {
         return GetIntProperty(index);
    }

    void Operator::SetColorProperty(int index, int value)
    {
        SetIntProperty(index, value);
    }

    String^ Operator::GetTextProperty(int index)
    {   
        return GetStringProperty(index);   
    }

    void Operator::SetTextProperty(int index, String^ value)
    {
        SetStringProperty(index, value);
    }
}