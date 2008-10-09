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
                                     List<OperatorBindingProperty^>^ properties)
    {
        this->name = name;
        this->id = operatorId;
        this->type = type;
        this->properties = properties;
    }

    OperatorBinding::~OperatorBinding()
    {

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
}