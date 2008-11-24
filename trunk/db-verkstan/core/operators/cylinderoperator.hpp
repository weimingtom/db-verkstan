#pragma once

#include "core/operator.hpp"

class CylinderOperator: public Operator
{
public:
    void process();
    void render(int tick);
};