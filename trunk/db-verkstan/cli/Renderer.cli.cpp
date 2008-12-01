#include "cli/Renderer.hpp"

#include "cli/Camera.hpp"
#include "cli/CoreOperator.hpp"

namespace Verkstan
{
    Renderer::Renderer()
    {
        camera = gcnew Camera();
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::RenderOperator(CoreOperator^ op, int tick)
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

        op->getOperator()->cascadeProcess();

        switch (op->Type)
        {
        case Constants::OperatorTypes::Mesh:
            RenderMeshOperator(op, tick);
            break;
         case Constants::OperatorTypes::Model:
            RenderModelOperator(op, tick);
            break;
        case Constants::OperatorTypes::Texture:
            RenderTextureOperator(op, tick);
            break;
        case Constants::OperatorTypes::Scene:
        case Constants::OperatorTypes::Renderer:
            RenderDemoSceneRendererOperator(op, tick);
            break;
        default:
            RenderUnknownOperator(op, tick);
            break;
        }
    }

    void Renderer::RenderTextureOperator(CoreOperator^ op, int tick)
    {
        Core::Operator* coreOp = op->getOperator();
        
        // Reset all channel values as we don't want any animation
        // to pollute the view.
        for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
        {
            if (coreOp->properties[i].channelValue1 != 0.0f)
            {
                coreOp->properties[i].channelValue1 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue2 != 0.0f)
            {
                coreOp->properties[i].channelValue2 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue3 != 0.0f)
            {
                coreOp->properties[i].channelValue3 = 0.0f;
                coreOp->setDirty(true);
            } 
        }

        globalDirect3DDevice->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);

               globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128));
        globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); 
	    globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	    globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

	    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

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
     
        coreOp->preRender(tick);

        if (coreOp->texture == 0)
            return;

        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

        globalWorldMatrixStack->LoadIdentity();
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        camera->ApplyUserTransformations();

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

    void Renderer::RenderUnknownOperator(CoreOperator^ op, int tick)
    {
        globalDirect3DDevice->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);
    }

    void Renderer::RenderMeshOperator(CoreOperator^ op, int tick)
    {
        Core::Operator* coreOp = op->getOperator();

        // Reset all channel values as we don't want any animation
        // to pollute the view.
        for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
        {
            if (coreOp->properties[i].channelValue1 != 0.0f)
            {
                coreOp->properties[i].channelValue1 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue2 != 0.0f)
            {
                coreOp->properties[i].channelValue2 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue3 != 0.0f)
            {
                coreOp->properties[i].channelValue3 = 0.0f;
                coreOp->setDirty(true);
            } 
        }

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
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        camera->ApplyUserTransformations();
        
        globalDirect3DDevice->BeginScene();

		coreOp->mesh->render();
	
        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderModelOperator(CoreOperator^ op, int tick)
    {
        Core::Operator* coreOp = op->getOperator();

        // Reset all channel values as we don't want any animation
        // to pollute the view.
        for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
        {
            if (coreOp->properties[i].channelValue1 != 0.0f)
            {
                coreOp->properties[i].channelValue1 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue2 != 0.0f)
            {
                coreOp->properties[i].channelValue2 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue3 != 0.0f)
            {
                coreOp->properties[i].channelValue3 = 0.0f;
                coreOp->setDirty(true);
            } 
        }

        coreOp->preRender(tick);

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

		globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

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

        camera->ApplyUserTransformations();
        
        globalWorldMatrixStack->LoadIdentity();
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        globalDirect3DDevice->BeginScene();
        coreOp->render(tick);
        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderDemoSceneRendererOperator(CoreOperator^ op, int tick)
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
     
        globalDirect3DDevice->Clear(0, 
                                     NULL, 
                                     D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                     ClearColor, 
                                     1.0f, 
                                     0);

        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128));
        globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); 
	    globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	    globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

	    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

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

        coreOp->preRender(tick);

        camera->ApplyFixedTransformations();
        
        globalWorldMatrixStack->LoadIdentity();
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        globalDirect3DDevice->BeginScene();
        coreOp->render(tick);
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