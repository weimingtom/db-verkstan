#include "cli/Renderer.hpp"

#include "cli/Camera.hpp"
#include "cli/Operator.hpp"
#include "cli/Timer.hpp"

namespace Verkstan
{
    Renderer::Renderer()
    {
        camera = gcnew Camera();
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::RenderOperator(Operator^ op)
    {
        if (op == nullptr)
        {
            globalDirect3DDevice->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);
            return;
        }

        if (!op->IsProcessable())
            return;

        Core::beat = Timer::GetBeat();
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
        case Constants::OperatorTypes::Demo:
        case Constants::OperatorTypes::Scene:
        case Constants::OperatorTypes::Renderer:
            RenderDemoSceneRendererOperator(op);
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

        if (coreOp->texture == 0)
            return;

        globalDirect3DDevice->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);

        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

        globalWorldMatrixStack->LoadIdentity();
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
       
        camera->ApplyTransformations();

        globalDirect3DDevice->BeginScene();

        VertexWithTexture vertices[]=
        {
           { -1.0f, -1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 1.0f },
           { -1.0f,  1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f },
           {  1.0f, -1.0f, 0.0f, 0xFFFFFFFF, 1.0f, 1.0f },
           {  1.0f,  1.0f, 0.0f, 0xFFFFFFFF, 1.0f, 0.0f },
        };

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
        globalDirect3DDevice->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);
    }

    void Renderer::RenderMeshOperator(Operator^ op)
    {
        Core::Operator* coreOp = op->getOperator();

        if (coreOp->mesh == 0)
            return;

        globalDirect3DDevice->Clear(0, 
                           NULL, 
                           D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                           ClearColor, 
                           1.0f, 
                           0);

        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        globalWorldMatrixStack->LoadIdentity();
        globalViewMatrixStack->LoadIdentity();
        globalProjectionMatrixStack->LoadIdentity();

        camera->ApplyTransformations();
        globalWorldMatrixStack->LoadIdentity();            
        globalDirect3DDevice->BeginScene();

        globalWorldMatrixStack->Push();
        globalWorldMatrixStack->Scale(coreOp->mesh->scale.x,
                                      coreOp->mesh->scale.y,
                                      coreOp->mesh->scale.z);
        globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(1.0f, 0.0f, 0.0f),
                                           coreOp->mesh->rotation.x);
        globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 1.0f, 0.0f),
                                           coreOp->mesh->rotation.y);
        globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 0.0f, 1.0f),
                                           coreOp->mesh->rotation.z);
        globalWorldMatrixStack->Translate(coreOp->mesh->translation.x,
                                          coreOp->mesh->translation.y,
                                          coreOp->mesh->translation.z); 
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
        coreOp->mesh->d3d9Mesh->DrawSubset(0);
        globalWorldMatrixStack->Pop();
        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderModelOperator(Operator^ op)
    {
        Core::Operator* coreOp = op->getOperator();

        globalDirect3DDevice->Clear(0, 
                                   NULL, 
                                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                   ClearColor, 
                                   1.0f, 
                                   0);

        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(80, 80, 80));
        globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); 
	    globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	    globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_MIRROR);

	    globalDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        globalDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
        globalDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

        D3DLIGHT9 d3dLight;
        ZeroMemory(&d3dLight, sizeof(d3dLight));
        d3dLight.Type = D3DLIGHT_DIRECTIONAL;
      
        d3dLight.Diffuse.r = 1.0f;
        d3dLight.Diffuse.g = 1.0f;
        d3dLight.Diffuse.b = 1.0f;
        d3dLight.Diffuse.a = 1.0f;

        D3DVECTOR position;
        position.x = -1.0f;
        position.y = -1.0f;
        position.z = -1.0f;
        d3dLight.Position = position;

        D3DVECTOR direction;
        direction.x = 1.0f;
        direction.y = 0.0f;
        direction.z = 0.0f;
        d3dLight.Direction = direction;

        globalDirect3DDevice->SetLight(0, &d3dLight); 
        globalDirect3DDevice->LightEnable(0, TRUE);

        D3DMATERIAL9 d3d9Material;
        ZeroMemory(&d3d9Material, sizeof(d3d9Material));
        d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 0.5f;
        d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 0.5f;
        d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 0.5f;
        d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 0.5f;
        
        globalDirect3DDevice->SetMaterial(&d3d9Material);

        camera->ApplyTransformations();
        globalWorldMatrixStack->LoadIdentity();

        globalDirect3DDevice->BeginScene();
        coreOp->render();
        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderDemoSceneRendererOperator(Operator^ op)
    {
        Core::Operator* coreOp = op->getOperator();

           globalDirect3DDevice->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET, 
                   D3DCOLOR_XRGB(0, 0, 0), 
                   1.0f, 
                   0);

      
        int height = WINDOW_HEIGHT;
        int width = (int)(height / 3.0f * 4.0f);
        D3DVIEWPORT9 viewport;
        viewport.X = WINDOW_WIDTH / 2 - width / 2;
        viewport.Y = 0;
        viewport.Width = width;
        viewport.Height = height;
        viewport.MinZ   = 0.0f;
        viewport.MaxZ   = 1.0f;
        globalDirect3DDevice->SetViewport(&viewport);
     
        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128));
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

        globalWorldMatrixStack->LoadIdentity();

        globalDirect3DDevice->BeginScene();
        coreOp->render();
        globalDirect3DDevice->EndScene();

       
        viewport;
        viewport.X = 0;
        viewport.Y = 0;
        viewport.Width = WINDOW_WIDTH;
        viewport.Height = WINDOW_HEIGHT;
        viewport.MinZ   = 0.0f;
        viewport.MaxZ   = 1.0f;
        globalDirect3DDevice->SetViewport(&viewport);
    
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