#include "OperatorBindingInput.hpp"

namespace Verkstan
{
    OperatorBindingInput::OperatorBindingInput(int index,
                                         Constants::OperatorTypes type,
                                         bool infinite,
                                         bool optional)
    {
        Index = index;
        Type = type;
        Infinite = infinite;
        Optional = optional;
    }
}