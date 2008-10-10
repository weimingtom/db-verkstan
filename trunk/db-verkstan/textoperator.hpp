#pragma once

#include "operator.hpp"

class TextOperator: public Operator
{
public:
    TextOperator();
    ~TextOperator();
    void render();
    void process();
    void deviceLost();
    LPDIRECT3DTEXTURE9 d3d9RenderTargetTexture;
};