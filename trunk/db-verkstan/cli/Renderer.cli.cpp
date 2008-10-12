#include "cli/Renderer.hpp"

#include "cli/Operators/NameOperator.hpp"

namespace Verkstan
{
    void Renderer::RenderOperator(Operator^ op)
    {
        switch (op->Type)
        {
        case Constants::OperatorTypes::Texture:
            RenderTextureOperator(op);
            break;
        case Constants::OperatorTypes::Name:
            RenderNameOperator(op);
            break;
        default:
            RenderUnknownOperator(op);
            break;
        }
    }

    void Renderer::RenderTextureOperator(Operator^ op)
    {
        VerkstanCore::Operator* coreOp = op->getOperator();

        D3DXMATRIX projection;
        D3DXMatrixPerspectiveFovLH(&projection, 
                                   D3DXToRadian(45.0f), 
                                   WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
                                   1.0f, 
                                   100.0f);
        globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &projection);

        D3DXMATRIX world;
        D3DXMATRIX view;
        D3DXMatrixTranslation(&world, 0.0f,0.0f,0.0f);
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, &world);
       
        D3DXMatrixLookAtLH(&view,
                           &D3DXVECTOR3(0.0f, 0.0f, -2.5f),
                           &D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                           &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
        globalDirect3DDevice->SetTransform(D3DTS_VIEW, &view);

        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

        globalDirect3DDevice->BeginScene();

        VertexWithTexture vertices[]=
        {
           { -1.0f, -1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 1.0f },
           { -1.0f,  1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f },
           {  1.0f, -1.0f, 0.0f, 0xFFFFFFFF, 1.0f, 1.0f },
           {  1.0f,  1.0f, 0.0f, 0xFFFFFFFF, 1.0f, 0.0f },
        };

        if (coreOp->texture != 0)
            globalDirect3DDevice->SetTexture(0, coreOp->texture->getD3D9Texture());		
        globalDirect3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);
        globalDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
                                              2,
                                              &vertices, 
                                              sizeof(VertexWithTexture));
        globalDirect3DDevice->SetTexture(0, 0);	
        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderNameOperator(Operator^ op)
    {
        NameOperator^ nameOp = (NameOperator^)op;

        if (nameOp->Input != nullptr)
            RenderOperator(nameOp->Input);
    }

    void Renderer::RenderUnknownOperator(Operator^ op)
    {

    }
}