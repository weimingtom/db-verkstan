#pragma once

#include "cli/Constants.hpp"

using namespace System;

namespace Verkstan 
{ 
    public ref class OperatorProperty
    {
    public:
        OperatorProperty(int index, 
                         int coreIndex,
                         String^ name, 
                         Constants::OperatorPropertyTypes type);
        property String^ Name;
        property Constants::OperatorPropertyTypes Type;
        property int Index;
        property int CoreIndex;
    };
}