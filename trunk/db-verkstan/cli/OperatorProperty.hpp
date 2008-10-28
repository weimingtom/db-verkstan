#pragma once

#include "cli/Constants.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan 
{ 
    public ref class OperatorProperty
    {
    public:
        OperatorProperty(int index, 
                         String^ name, 
                         Constants::OperatorPropertyTypes type);
        OperatorProperty(int index, 
                         String^ name, 
                         Constants::OperatorPropertyTypes type,
                         List<String^>^ enumValues);
        property String^ Name;
        property Constants::OperatorPropertyTypes Type;
        property int Index;
        property List<String^>^ EnumValues;
    };
}