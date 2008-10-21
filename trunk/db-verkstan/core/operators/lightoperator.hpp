#pragma once

#include "core/operator.hpp"

class LightOperator: public Operator
{
public:
    void process();
    void render();
    D3DLIGHT9 d3dLight;
};