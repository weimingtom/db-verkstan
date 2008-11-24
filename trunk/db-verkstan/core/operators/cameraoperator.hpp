#pragma once

#include "core/operator.hpp"

class CameraOperator: public Operator
{
public:
    void process();
    void render(int tick);
    D3DXMATRIX projectionMatrix;
    D3DXMATRIX viewMatrix;
};