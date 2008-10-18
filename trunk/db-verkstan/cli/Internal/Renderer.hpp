#pragma once

#include "cli/Operator.hpp"

struct VertexWithTexture
{
    float x, y, z;
    DWORD color;
    float u, v;
};

namespace Verkstan
{
    public ref class Renderer
    {
    public:
        static void RenderOperator(Operator^ op);

    private:
        static void RenderTextureOperator(Operator^ op);
        static void RenderStoreOperator(Operator^ op);
        static void RenderLoadOperator(Operator^ op);
        static void RenderMeshOperator(Operator^ op);
        static void RenderUnknownOperator(Operator^ op);
    };
}