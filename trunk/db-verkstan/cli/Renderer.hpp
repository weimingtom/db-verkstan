#pragma once

#include <d3d9.h>

struct VertexWithTexture
{
    float x, y, z;
    DWORD color;
    float u, v;
};

namespace Verkstan
{
    ref class Camera;
    ref class CoreOperator;
    
    public ref class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        int ClearColor;
            
        void RenderOperator(CoreOperator^ op);
        void MouseDown(int button, int x, int y);
        void MouseMove(int x, int y);
        void MouseUp(int button, int x, int y);
        void ResetCamera();

    private:
        void RenderTextureOperator(CoreOperator^ op);
        void RenderStoreOperator(CoreOperator^ op);
        void RenderLoadOperator(CoreOperator^ op);
        void RenderMeshOperator(CoreOperator^ op);
        void RenderModelOperator(CoreOperator^ op);
        void RenderDemoSceneRendererOperator(CoreOperator^ op);
        void RenderUnknownOperator(CoreOperator^ op);

        Camera^ camera;
    };
}