#pragma once

#include "core/operator.hpp"

class RotozoomOperator: public Operator
{
public:
    void render(int tick);
    void process();
};