#pragma once

#include "OperatorBinding.hpp"

struct VertexWithTexture
{
    float x, y, z;
    DWORD color;
    float u, v;
};

namespace VerkstanBindings
{
    public ref class Renderer
    {
    public:
        static void RenderOperator(OperatorBinding^ op);

    private:
        static void RenderTextureOperator(OperatorBinding^ op);
        static void RenderNameOperator(OperatorBinding^ op);
        static void RenderUnknownOperator(OperatorBinding^ op);
    };
}