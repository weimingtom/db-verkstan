#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/Operator.hpp"

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
                       int operatorId,
                       Constants::OperatorTypes type,
                       OperatorProperties^ properties)
    {
        this->name = name;
        DisplayName = name;
        this->id = operatorId;
        this->type = type;
        this->properties = properties;
    }

    Operator::~Operator()
    {

    }

    int Operator::Id::get()
    {
        return id;
    }

    OperatorProperties^ Operator::Properties::get() 
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
}