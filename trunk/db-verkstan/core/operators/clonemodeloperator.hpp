#pragma once

#include "core/operator.hpp"

class CloneModelOperator: public Operator
{
public:
    void process();
    void render();
    D3DXMATRIX matrix;
    int clones;
};