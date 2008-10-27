#include "cli/OperatorProperty.hpp"

namespace Verkstan
{
    OperatorProperty::OperatorProperty(int index,
                                       int coreIndex,
                                       String^ name, 
                                       Constants::OperatorPropertyTypes type)
    {
        Name = name;
        Type = type;
        Index = index;
        CoreIndex = coreIndex;
    }

      OperatorProperty::OperatorProperty(int index,
                                         int coreIndex,
                                         String^ name, 
                                         Constants::OperatorPropertyTypes type,
                                         List<String^>^ enumValues)
    {
        Name = name;
        Type = type;
        Index = index;
        CoreIndex = coreIndex;
        EnumValues = enumValues;
    }
}