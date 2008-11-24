#pragma once

#include "core/operator.hpp"

class CloneModelOperator: public Operator
{
public:
    void process();
    void render(int tick);
    D3DXMATRIX matrix;
    int clones;
};