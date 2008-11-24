#pragma once

#include "core/operator.hpp"

class SphereOperator: public Operator
{
public:
    void process();
    void render(int tick);
};