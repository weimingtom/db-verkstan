#include "OperatorBinding.hpp"
#include "OperatorBindingProperty.hpp"

namespace Verkstan
{
    OperatorBindingProperty::OperatorBindingProperty(int index,
                                               String^ name, 
                                               Constants::OperatorPropertyTypes type)
    {
        Name = name;
        Type = type;
        Index = index;
    }

      
    OperatorBindingProperty::OperatorBindingProperty(int index,
                                               String^ name, 
                                               Constants::OperatorPropertyTypes type,
                                               List<String^>^ enumValues)
    {
        Name = name;
        Type = type;
        Index = index;
        EnumValues = enumValues;
    }
}