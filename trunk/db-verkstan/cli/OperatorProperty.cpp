#include "cli/Operator.hpp"

#include "cli/OperatorProperty.hpp"

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

      
    OperatorProperty::OperatorProperty(int index,
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