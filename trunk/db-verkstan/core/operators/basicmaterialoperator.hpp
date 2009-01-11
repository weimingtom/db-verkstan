#pragma once

#include "core/operator.hpp"

class BasicMaterialOperator: public Operator
{
public:
    void process();
    void render(int tick);
    D3DMATERIAL9 d3d9Material;
};