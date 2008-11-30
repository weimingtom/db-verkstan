#pragma once

#include "core/operator.hpp"

class RenderToTextureOperator: public Operator
{
public:
    RenderToTextureOperator();
    ~RenderToTextureOperator();
    void preRender(int tick);
    void process();
    void deviceLost();
    LPDIRECT3DSURFACE9 d3d9RenderTargetSurface;
    LPDIRECT3DTEXTURE9 d3d9RenderTargetTexture;
    LPD3DXRENDERTOSURFACE d3d9RenderToSurface;
};