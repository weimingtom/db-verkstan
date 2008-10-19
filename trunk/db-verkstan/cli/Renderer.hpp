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
    ref class Operator;
    
    public ref class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        float Zoom;
        float RotationX;
        float RotationY;
        
        void SetViewport(int width, int height);
        void RenderOperator(Operator^ op);
        void MouseDown(int button, int x, int y);
        void MouseMove(int x, int y);
        void MouseUp(int button, int x, int y);

    private:
        void RenderTextureOperator(Operator^ op);
        void RenderStoreOperator(Operator^ op);
        void RenderLoadOperator(Operator^ op);
        void RenderMeshOperator(Operator^ op);
        void RenderUnknownOperator(Operator^ op);

        Camera^ camera;
    };
}