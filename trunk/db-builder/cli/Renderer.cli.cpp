#include "BuilderLib.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "OperatorBinding.hpp"
#include "TextureOperatorRenderer.hpp"
#include "OperatorRenderOptions.hpp"

namespace Verkstan
{
    Renderer::Renderer()
    {
        camera = gcnew Camera();
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::RenderOperator(OperatorBinding^ op, OperatorRenderOptions^ options)
    {
        if (op == nullptr)
        {
            Builder::device->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   options->ClearColor, 
                   1.0f, 
                   0);
            return;
        }

        camera->WindowWidth = WindowWidth;
        camera->WindowHeight = WindowHeight;

        InternalOperator* coreOp = op->getOperator();
        coreOp->cascadeProcess();
 
        op->Renderer->render(op, camera, options);
    }

    void Renderer::MouseDown(int button, int x, int y)
    {
        camera->MouseDown(button, x, y);
    }

    void Renderer::MouseMove(int x, int y)
    {
         camera->MouseMove(x, y);
    }

    void Renderer::MouseUp(int button, int x, int y)
    {
         camera->MouseUp(button, x, y);
    }

    void Renderer::ResetCamera()
    {
        camera->Reset();
    }
}