#include "BuilderLib.hpp"
#include "Renderer.hpp"
#include "Builder.hpp"
#include "Camera.hpp"
#include "OperatorBinding.hpp"

namespace Verkstan
{
    Renderer::Renderer()
    {
        camera = gcnew Camera();
        TextureTiling = false;
        TextureFiltering = false;
        MeshSolid = false;
        ModelLightning = true;
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::RenderOperator(OperatorBinding^ op)
    {
        if (op == nullptr)
        {
            Builder::device->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);
            return;
        }

        camera->WindowWidth = WindowWidth;
        camera->WindowHeight = WindowHeight;

      
        InternalOperator* coreOp = op->getOperator();
        coreOp->cascadeProcess();
 
        switch (op->Type)
        {
        case Constants::OperatorTypes::Mesh:
            RenderMeshOperator(op);
            break;
         case Constants::OperatorTypes::Renderable:
            RenderModelOperator(op);
            break;
        case Constants::OperatorTypes::Texture:
            RenderTextureOperator(op);
            break;
        default:
            RenderUnknownOperator(op);
            break;
        }
    }

    void Renderer::RenderTextureOperator(OperatorBinding^ op)
    {
        InternalOperator* coreOp = op->getOperator();

        if (coreOp->texture == 0)
            return;

        int textureWidth = coreOp->texture->width;
        int textureHeight = coreOp->texture->height;
        float textureRatioWidthHeight = textureWidth / (float)textureHeight;
        float textureRatioHeightWidth = textureHeight / (float)textureWidth;

        if (textureWidth > WindowWidth && textureHeight > WindowHeight)
        {
            if (textureWidth > textureHeight)
            {
                textureWidth = WindowWidth;
                textureHeight = (int)(textureWidth * textureRatioHeightWidth);
            }
            else
            {
                textureHeight = WindowHeight;
                textureWidth = (int)(textureHeight * textureRatioWidthHeight);
            }
        }
        else if (textureWidth > WindowWidth)
        {
            textureWidth = WindowWidth;
            textureHeight = (int)(textureWidth * textureRatioHeightWidth);
        }
        else if (textureHeight > WindowHeight)
        {
            textureHeight = WindowHeight;
            textureWidth = (int)(textureHeight * textureRatioWidthHeight);
        }

        float x, y, width, height, u1, u2, v1, v2;

        if (TextureTiling)
        {
            x = 0.0f;
            y = 0.0f;
            width = 1.0f;
            height = 1.0f;

            float texturesOnX = WindowWidth / (float)textureWidth;
            float texturesOnY = WindowHeight / (float)textureHeight;
            
            // We add 0.5f to center the texture. Why? Because if the
            // the texture width is the same as the window width
            // texturesOnX becomes 0.5f, and in that case we want
            // u1 = 0.0f and u2 = 1.0f.
            u1 = -texturesOnX / 2.0f + 0.5f;
            u2 =  texturesOnX / 2.0f + 0.5f;
            v1 = -texturesOnY / 2.0f + 0.5f;
            v2 =  texturesOnY / 2.0f + 0.5f;

            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
        }
        else
        {
            x = (WindowWidth / 2 - textureWidth / 2) / (float)WindowWidth;
            y = (WindowHeight / 2 - textureHeight / 2) / (float)WindowHeight;
            width = textureWidth / (float)WindowWidth;
            height = textureHeight / (float)WindowHeight;
            u1 = 0.0f;
            u2 = 1.0f;
            v1 = 0.0f;
            v2 = 1.0f;

            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_BORDER);
        }

        if (TextureFiltering)
        {
            Builder::device->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	        Builder::device->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	        Builder::device->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
        }
        else
        {
            Builder::device->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	        Builder::device->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_NONE);
	        Builder::device->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        }

        TextureVertex quad[4];
        quad[0].x = x; 
        quad[0].y = y; 
        quad[0].z = 0.0f;
        quad[0].u = u1; 
        quad[0].v = v1; 
        quad[0].color = 0xffffffff;
        
        quad[1].x = x + width; 
        quad[1].y = y; 
        quad[1].z = 0.0f;
        quad[1].u = u2; 
        quad[1].v = v1; 
        quad[1].color = 0xffffffff;

        quad[2].x = x + width; 
        quad[2].y = y + height; 
        quad[2].z = 0.0f;
        quad[2].u = u2;
        quad[2].v = v2; 
        quad[2].color = 0xffffffff;

        quad[3].x = x; 
        quad[3].y = y + height; 
        quad[3].z = 0.0f;
        quad[3].u = u1; 
        quad[3].v = v2; 
        quad[3].color = 0xffffffff;

        D3DXMATRIX identityMatrix;
        D3DXMATRIX projectionMatrix;
        D3DXMatrixIdentity(&identityMatrix);
        D3DXMatrixOrthoOffCenterLH(&projectionMatrix, 
                                   0.0f, 
                                   1.0f, 
                                   1.0f, 
                                   0.0f, 
                                   -1.0f, 
                                   1.0f);
        Builder::device->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
        Builder::device->SetTransform(D3DTS_VIEW, &identityMatrix);
        Builder::device->SetTransform(D3DTS_WORLD, &identityMatrix);
        Builder::device->SetRenderState(D3DRS_LIGHTING, FALSE);
        Builder::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        Builder::device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        Builder::device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);     
        Builder::device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
        Builder::device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
        Builder::device->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);

        Builder::device->Clear(0, 
                               NULL, 
                               D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                               ClearColor, 
                               1.0f, 
                               0);

        Builder::device->BeginScene();
        Builder::device->SetTexture(0, coreOp->texture->getD3D9Texture());		
        Builder::device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);
        Builder::device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &quad, sizeof(TextureVertex));
        Builder::device->SetTexture(0, 0);		
        Builder::device->EndScene();
    }

    void Renderer::RenderUnknownOperator(OperatorBinding^ op)
    {
        /*
        Builder::device->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);
                   */
    }

    void Renderer::RenderMeshOperator(OperatorBinding^ op)
    {
        InternalOperator* coreOp = op->getOperator();

        if (coreOp->mesh == 0)
            return;

        Builder::device->Clear(0, 
                           NULL, 
                           D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                           ClearColor, 
                           1.0f, 
                           0);

       

        if (MeshSolid)
        {
            Builder::device->SetRenderState(D3DRS_LIGHTING, TRUE);

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

            Builder::device->SetLight(0, &d3dLight); 
            Builder::device->LightEnable(0, TRUE);

            D3DMATERIAL9 d3d9Material;
            ZeroMemory(&d3d9Material, sizeof(d3d9Material));
            d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 0.5f;
            d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 0.5f;
            d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 0.5f;
            d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 0.5f;
            d3d9Material.Specular.r = 1.0f;
            d3d9Material.Specular.g = 1.0f;
            d3d9Material.Specular.b = 1.0f;
            d3d9Material.Specular.a = 1.0f;
            d3d9Material.Power = 0.001f;
            
            Builder::device->SetMaterial(&d3d9Material);

            Builder::device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG); 
	        Builder::device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	        Builder::device->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
            Builder::device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
        }
        else
        {
            Builder::device->SetRenderState(D3DRS_LIGHTING, FALSE);  
        }

        Builder::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

        D3DXMATRIX identity;
        D3DXMatrixIdentity(&identity);
        //globalWorldMatrixStack->LoadIdentity();
        Builder::device->SetTransform(D3DTS_WORLD, &identity);

        camera->ApplyUserTransformations();
        
        Builder::device->BeginScene();

        Mesh* mesh = coreOp->mesh;

        if (!MeshSolid)
        {
            if (!(mesh->indexBuffer && mesh->vertexBuffer))
                mesh->createD3DBuffers();

            Builder::device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

            Mesh::EdgeInfo* edgeInfo = mesh->constructEdgeInfo();

            int indexBytes = edgeInfo->getNumEdges()*2*sizeof(int);

            LPDIRECT3DINDEXBUFFER9 indexBuffer;
            Builder::device->CreateIndexBuffer(indexBytes, 
                                              0, 
                                              D3DFMT_INDEX32, 
                                              D3DPOOL_DEFAULT,  
                                              &indexBuffer, 
                                              NULL);
            
            int *indexBufferData;
            indexBuffer->Lock(0, indexBytes, (void **)(&indexBufferData), 0);
            memcpy(indexBufferData, edgeInfo->edges, indexBytes);
            indexBuffer->Unlock();

            Builder::device->SetFVF(mesh->fvf);
	        Builder::device->SetStreamSource(0, mesh->vertexBuffer, 0, mesh->vertexStride * sizeof(float));
	        Builder::device->SetIndices(indexBuffer);
	        Builder::device->DrawIndexedPrimitive
	        (
		        D3DPT_LINELIST,			     		// Type
		        0,									// BaseVertexIndex
		        0,									// MinIndex
		        edgeInfo->getNumEdges()*2,			// NumVertices
		        0,									// StartIndex
		        edgeInfo->getNumEdges()  			// PrimitiveCount
	        );
           
            delete edgeInfo;
            indexBuffer->Release();

            Builder::device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);     
            Builder::device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
            Builder::device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
            
            for (int f = 0; f < mesh->getNumFaces(); f++)
            {
                if (mesh->faceSelected(f))
                {
                    MeshVertex selectedFaceToDraw[4];
                    int n;
                    int *face = mesh->face(f, n);
                    
                    if (n == 3)
                    {
                        Vec3 pos1 = mesh->pos(face[0]);
                        Vec3 pos2 = mesh->pos(face[1]);
                        Vec3 pos3 = mesh->pos(face[2]);
                        selectedFaceToDraw[0].x = pos1.x;
                        selectedFaceToDraw[0].y = pos1.y;
                        selectedFaceToDraw[0].z = pos1.z;
                        selectedFaceToDraw[0].color = D3DCOLOR_ARGB(128, 255, 0, 0);    
                        selectedFaceToDraw[1].x = pos2.x;
                        selectedFaceToDraw[1].y = pos2.y;
                        selectedFaceToDraw[1].z = pos2.z;
                        selectedFaceToDraw[1].color = D3DCOLOR_ARGB(128, 255, 0, 0);   
                        selectedFaceToDraw[2].x = pos3.x;
                        selectedFaceToDraw[2].y = pos3.y;
                        selectedFaceToDraw[2].z = pos3.z;
                        selectedFaceToDraw[2].color = D3DCOLOR_ARGB(128, 255, 0, 0);
                        Builder::device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
                        Builder::device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &selectedFaceToDraw, sizeof(MeshVertex));
                    }
                    else
                    {
                        Vec3 pos1 = mesh->pos(face[0]);
                        Vec3 pos2 = mesh->pos(face[1]);
                        Vec3 pos3 = mesh->pos(face[2]);
                        Vec3 pos4 = mesh->pos(face[3]);
                        selectedFaceToDraw[0].x = pos1.x;
                        selectedFaceToDraw[0].y = pos1.y;
                        selectedFaceToDraw[0].z = pos1.z;
                        selectedFaceToDraw[0].color = D3DCOLOR_ARGB(128, 255, 0, 0);    
                        selectedFaceToDraw[1].x = pos2.x;
                        selectedFaceToDraw[1].y = pos2.y;
                        selectedFaceToDraw[1].z = pos2.z;
                        selectedFaceToDraw[1].color = D3DCOLOR_ARGB(128, 255, 0, 0);   
                        selectedFaceToDraw[2].x = pos4.x;
                        selectedFaceToDraw[2].y = pos4.y;
                        selectedFaceToDraw[2].z = pos4.z;
                        selectedFaceToDraw[2].color = D3DCOLOR_ARGB(128, 255, 0, 0);
                        selectedFaceToDraw[3].x = pos3.x;
                        selectedFaceToDraw[3].y = pos3.y;
                        selectedFaceToDraw[3].z = pos3.z;
                        selectedFaceToDraw[3].color = D3DCOLOR_ARGB(128, 255, 0, 0);
                        Builder::device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
                        Builder::device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &selectedFaceToDraw, sizeof(MeshVertex));
                    }       
                }
            }
        }
        else
        {
            Builder::device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); 
            Builder::device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
            mesh->render();
        }   
	
        Builder::device->EndScene();
    }

    void Renderer::RenderModelOperator(OperatorBinding^ op)
    {
        /*
        Operator* coreOp = op->getOperator();

        for (int i = 0; i < coreNumberOfLights; i++)
            Builder::device->LightEnable(i, FALSE);

        coreNumberOfLights = 0;

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

        if (ModelLightning)
        {
            Builder::device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); 
            Builder::device->SetRenderState(D3DRS_LIGHTING, TRUE);

            D3DLIGHT9 d3dLight;
            ZeroMemory(&d3dLight, sizeof(d3dLight));
            d3dLight.Type = D3DLIGHT_DIRECTIONAL;
          
            d3dLight.Diffuse.r = 1.0f;
            d3dLight.Diffuse.g = 1.0f;
            d3dLight.Diffuse.b = 1.0f;
            d3dLight.Diffuse.a = 1.0f;

            D3DVECTOR position;
            position.x = 100.0f;
            position.y = 100.0f;
            position.z = -100.0f;
            d3dLight.Position = position;

            D3DVECTOR direction;
            direction.x = 1.0f;
            direction.y = 0.0f;
            direction.z = 0.0f;
            d3dLight.Direction = direction;

            Builder::device->SetLight(0, &d3dLight); 
            Builder::device->LightEnable(0, TRUE);

            D3DMATERIAL9 d3d9Material;
            ZeroMemory(&d3d9Material, sizeof(d3d9Material));
            d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 0.5f;
            d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 0.5f;
            d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 0.5f;
            d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 0.5f;
            d3d9Material.Specular.r = 1.0f;
            d3d9Material.Specular.g = 1.0f;
            d3d9Material.Specular.b = 1.0f;
            d3d9Material.Specular.a = 1.0f;
            d3d9Material.Power = 0.001f;
            
            Builder::device->SetMaterial(&d3d9Material);

            Builder::device->SetRenderState(D3DRS_LIGHTING, TRUE);
            Builder::device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG); 
	        Builder::device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	        Builder::device->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
            Builder::device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
            coreNumberOfLights++;
        }
        else
        {
            Builder::device->SetRenderState(D3DRS_LIGHTING, FALSE);
        }

        Builder::device->Clear(0, 
                                   NULL, 
                                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                   ClearColor, 
                                   1.0f, 
                                   0);

        camera->ApplyUserTransformations();
        
        globalWorldMatrixStack->LoadIdentity();
        Builder::device->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        Builder::device->BeginScene();
        coreOp->render();
        Builder::device->EndScene();
        */
    }

     /*
    void Renderer::RenderDemoSceneRendererOperator(OperatorBinding^ op)
    {
       
        Operator* coreOp = op->getOperator();

        for (int i = 0; i < coreNumberOfLights; i++)
            Builder::device->LightEnable(i, FALSE);

        coreNumberOfLights = 0;

        Builder::device->Clear(0, 
               NULL, 
               D3DCLEAR_TARGET, 
               D3DCOLOR_XRGB(0, 0, 0), 
               1.0f, 
               0);

       
        globalWindowHeight = WindowHeight;
        globalWindowWidth = (int)(WindowHeight / 3.0f * 4.0f);
        D3DVIEWPORT9 viewport;
        viewport.X = WindowWidth / 2 - globalWindowWidth / 2;
        viewport.Y = 0;
        viewport.Width = globalWindowWidth;
        viewport.Height = globalWindowHeight;
        viewport.MinZ   = 0.0f;
        viewport.MaxZ   = 1.0f;
        Builder::device->SetViewport(&viewport);
     

        Builder::device->Clear(0, 
                                     NULL, 
                                     D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                     ClearColor, 
                                     1.0f, 
                                     0);
    */

        /*
        Builder::device->SetRenderState(D3DRS_LIGHTING, TRUE);
        Builder::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        Builder::device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        Builder::device->SetRenderState(D3DRS_ZENABLE, TRUE);
        Builder::device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128));
        Builder::device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); 
	    Builder::device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	    Builder::device->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	    Builder::device->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	    Builder::device->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	    Builder::device->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	    Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	    Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	    Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

	    Builder::device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        Builder::device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        Builder::device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

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

        Builder::device->SetLight(0, &d3dLight); 
        Builder::device->LightEnable(0, TRUE);

        D3DMATERIAL9 d3d9Material;
        ZeroMemory(&d3d9Material, sizeof(d3d9Material));
        d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 0.5f;
        d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 0.5f;
        d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 0.5f;
        d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 0.5f;
        
        Builder::device->SetMaterial(&d3d9Material);
        */

        //coreOp->preRender(tick);

        /*
        camera->ApplyFixedTransformations();
        
        globalWorldMatrixStack->LoadIdentity();
        Builder::device->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        Builder::device->BeginScene();
        coreOp->render();
        Builder::device->EndScene();

        viewport;
        viewport.X = 0;
        viewport.Y = 0;
        viewport.Width = WindowWidth;
        viewport.Height = WindowHeight;
        viewport.MinZ   = 0.0f;
        viewport.MaxZ   = 1.0f;
        Builder::device->SetViewport(&viewport);
        */
    //}

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