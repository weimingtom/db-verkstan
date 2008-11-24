#pragma once

#include "core/operator.hpp"

class AddModelsOperator: public Operator
{
public:
    void process();
    void render(int tick);
};