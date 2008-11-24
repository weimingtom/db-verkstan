#pragma once

#include "core/operator.hpp"

class ModelOperator: public Operator
{
public:
    void process();
    void render(int tick);
};