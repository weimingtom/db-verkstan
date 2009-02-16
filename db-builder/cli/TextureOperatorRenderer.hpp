#pragma once

#include "OperatorRenderer.hpp"

namespace Verkstan
{
    struct TextureOperatorRendererTextureVertex
    {
        float x, y, z;
        DWORD color;
        float u, v;
    };

    public ref class TextureOperatorRenderer: public OperatorRenderer
    {
    public:
        TextureOperatorRenderer() {};
        virtual  void render(OperatorBinding^ operatorBinding,
                             Camera^ camera, 
                             OperatorRenderOptions^ options) override;
    };
}