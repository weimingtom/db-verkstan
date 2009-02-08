#pragma once

using namespace System;

#include "Constants.hpp"

namespace Verkstan
{
    public ref class OperatorBindingInput
    {
    public:
        OperatorBindingInput(int index,
                          Constants::OperatorTypes type,
                          bool infinite,
                          bool optional);
        property bool Infinite;
        property bool Optional;
        property Constants::OperatorTypes Type;
        property int Index;
    };
}