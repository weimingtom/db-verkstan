#include "cli/OperatorInput.hpp"

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
}