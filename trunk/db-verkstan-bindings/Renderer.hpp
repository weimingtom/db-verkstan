#pragma once

#include "Operator.hpp"

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
        static void RenderOperator(Operator^ op);

    private:
        static void RenderTextureOperator(Operator^ op);
        static void RenderNameOperator(Operator^ op);
        static void RenderUnknownOperator(Operator^ op);
    };
}