#pragma once

namespace Verkstan
{
    ref class Camera;
    ref class OperatorBinding;
    ref class OperatorRenderOptions;

    public ref class Renderer
    {
    public:
        Renderer();
        ~Renderer();
 
        int WindowWidth;
        int WindowHeight;
        
        void RenderOperator(OperatorBinding^ op, OperatorRenderOptions^ options);
        void MouseDown(int button, int x, int y);
        void MouseMove(int x, int y);
        void MouseUp(int button, int x, int y);
        void ResetCamera();

    private:
        Camera^ camera;
    };
}