#pragma once

#include "core/operator.hpp"

class TwoDimensionalPlaneOperator: public Operator
{
public:
    void render(int tick);
    void process();
   
    D3DXMATRIX identityMatrix;
    D3DXMATRIX projectionMatrix;

#ifdef DB_EDITOR
    void deviceLost();
#endif
};