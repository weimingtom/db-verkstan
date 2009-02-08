#pragma once

#include "Constants.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan 
{ 
    public ref class OperatorBindingProperty
    {
    public:
        OperatorBindingProperty(int index, 
                             String^ name, 
                             Constants::OperatorPropertyTypes type);
        OperatorBindingProperty(int index, 
                             String^ name, 
                             Constants::OperatorPropertyTypes type,
                             List<String^>^ enumValues);
        property String^ Name;
        property Constants::OperatorPropertyTypes Type;
        property int Index;
        property List<String^>^ EnumValues;
    };
}