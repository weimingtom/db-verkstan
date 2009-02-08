#pragma once

struct TextureVertex
{
    float x, y, z;
    DWORD color;
    float u, v;
};

struct MeshVertex
{
    float x, y, z;
    DWORD color;
};

namespace Verkstan
{
    ref class Camera;
    ref class OperatorBinding;
    
    public ref class Renderer
    {
    public:
        Renderer();
        ~Renderer();
 
        bool TextureTiling;
        bool TextureFiltering;
        bool MeshSolid;
        bool ModelLightning;

        int ClearColor;
        int WindowWidth;
        int WindowHeight;
        
        void RenderOperator(OperatorBinding^ op);
        void MouseDown(int button, int x, int y);
        void MouseMove(int x, int y);
        void MouseUp(int button, int x, int y);
        void ResetCamera();

    private:
        void RenderTextureOperator(OperatorBinding^ op);
        void RenderMeshOperator(OperatorBinding^ op);
        void RenderModelOperator(OperatorBinding^ op);
        void RenderUnknownOperator(OperatorBinding^ op);

        Camera^ camera;
    };
}