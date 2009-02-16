#pragma once

#include "OperatorRenderer.hpp"

namespace Verkstan
{
    struct MeshOperatorRendererMeshVertex
    {
        float x, y, z;
        DWORD color;
    };

    public ref class MeshOperatorRenderer: public OperatorRenderer
    {
    public:
        MeshOperatorRenderer() {};
        virtual void render(OperatorBinding^ operatorBinding,
                            Camera^ camera, 
                            OperatorRenderOptions^ options) override;
    };
}