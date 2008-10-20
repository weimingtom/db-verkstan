#include "cli/Renderer.hpp"

#include "cli/Camera.hpp"
#include "cli/Operator.hpp"

namespace Verkstan
{
    Renderer::Renderer()
    {
        camera = gcnew Camera();
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::SetViewport(int width, int height)
    {
        
    }

    void Renderer::RenderOperator(Operator^ op)
    {
        if (!op->IsProcessable())
            return;

        op->getOperator()->cascadeProcess();

        switch (op->Type)
        {
        case Constants::OperatorTypes::Mesh:
            RenderMeshOperator(op);
            break;
         case Constants::OperatorTypes::Model:
            RenderModelOperator(op);
            break;
        case Constants::OperatorTypes::Texture:
            RenderTextureOperator(op);
            break;
        case Constants::OperatorTypes::Store:
            RenderStoreOperator(op);
            break;
         case Constants::OperatorTypes::Load:
            RenderLoadOperator(op);
            break;
        default:
            RenderUnknownOperator(op);
            break;
        }
    }

    void Renderer::RenderStoreOperator(Operator^ op)
    {
        if (op->GetPrimaryJoint()->Sender != nullptr)
            RenderOperator(op->GetPrimaryJoint()->Sender);
    }

    void Renderer::RenderLoadOperator(Operator^ op)
    {
        if (op->GetPrimaryJoint()->Sender != nullptr)
            RenderOperator(op->GetPrimaryJoint()->Sender);
    }

    void Renderer::RenderTextureOperator(Operator^ op)
    {
        Core::Operator* coreOp = op->getOperator();

        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

        D3DXMATRIX world;
        D3DXMatrixTranslation(&world, 0.0f,0.0f,0.0f);
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, &world);

        camera->ApplyTransformations();

          /*
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
         */

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

    void Renderer::RenderUnknownOperator(Operator^ op)
    {

    }

    void Renderer::RenderMeshOperator(Operator^ op)
    {
        Core::Operator* coreOp = op->getOperator();

        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        if (coreOp->mesh != 0)
        {
            D3DXMATRIX scale;
            D3DXMatrixScaling(&scale, 
                              coreOp->mesh->scale.x,
                              coreOp->mesh->scale.y,
                              coreOp->mesh->scale.z);   
            D3DXMATRIX rotationX;
            D3DXMatrixRotationX(&rotationX, coreOp->mesh->rotation.x);
            D3DXMATRIX rotationY;
            D3DXMatrixRotationY(&rotationY, coreOp->mesh->rotation.y);
            D3DXMATRIX rotationZ;
            D3DXMatrixRotationZ(&rotationZ, coreOp->mesh->rotation.z);
            D3DXMATRIX translation;
            D3DXMatrixTranslation(&translation, 
                                  coreOp->mesh->translation.x, 
                                  coreOp->mesh->translation.y, 
                                  coreOp->mesh->translation.z);     
            D3DXMATRIX world = scale * rotationX * rotationY * rotationZ * translation;
            globalDirect3DDevice->SetTransform(D3DTS_WORLD, &world);
        }

        camera->ApplyTransformations();

        globalDirect3DDevice->BeginScene();

        if (coreOp->mesh != 0)
            coreOp->mesh->d3d9Mesh->DrawSubset(0);

        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderModelOperator(Operator^ op)
    {
        Core::Operator* coreOp = op->getOperator();

        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
        globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); 
	    globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	    globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
        /*
	    globalDirect3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
        globalDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);*/

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_MIRROR);

	    globalDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        globalDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
        globalDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

        D3DXMATRIX world;
        D3DXMatrixTranslation(&world, 0.0f,0.0f,0.0f);
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, &world);

        camera->ApplyTransformations();

        globalDirect3DDevice->BeginScene();

        coreOp->cascadeRender();

        globalDirect3DDevice->EndScene();
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
}