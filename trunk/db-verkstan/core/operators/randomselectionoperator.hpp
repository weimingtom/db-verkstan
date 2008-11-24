#pragma once

#include "core/operator.hpp"

class RandomSelectionOperator: public Operator
{
public:
    void process();
    void render(int tick);
};