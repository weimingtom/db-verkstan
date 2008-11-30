#pragma once

#include "core/operator.hpp"

class TextOperator: public Operator
{
public:
    TextOperator();
    ~TextOperator();
    void process();
    void deviceLost();
    LPDIRECT3DTEXTURE9 d3d9RenderTargetTexture;
};