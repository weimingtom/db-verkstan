#pragma once

#include "core/operator.hpp"

class TransformModelOperator: public Operator
{
public:
    void process();
    void render(int tick);
    D3DXMATRIX matrix;
};