#include "OperatorBinding.hpp"
#include "MeshOperatorRenderer.hpp"
#include "OperatorRenderOptions.hpp"
#include "Camera.hpp"

namespace Verkstan
{
    void MeshOperatorRenderer::render(OperatorBinding^ operatorBinding,
                                      Camera^ camera, 
                                      OperatorRenderOptions^ options)
    {
        InternalOperator* coreOp = operatorBinding->getOperator();

        if (coreOp->mesh == 0)
            return;

        Builder::device->Clear(0, 
                               NULL, 
                               D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                               options->ClearColor, 
                               1.0f, 
                               0);

        D3DXMATRIX identity;
        D3DXMatrixIdentity(&identity);
        Builder::device->SetTransform(D3DTS_WORLD, &identity);

        camera->ApplyUserTransformations();

        if (options->MeshShaded)
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
        
        Builder::device->BeginScene();

        Mesh* mesh = coreOp->mesh;

        if (!options->MeshShaded)
        {
            Builder::device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
            mesh->renderWireframe();
            Builder::device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);     
            Builder::device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
            Builder::device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
            
            for (int f = 0; f < mesh->getNumFaces(); f++)
            {
                if (mesh->faceSelected(f))
                {
                    MeshOperatorRendererMeshVertex selectedFaceToDraw[4];
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
                        Builder::device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 
                                                         1, 
                                                         &selectedFaceToDraw, 
                                                         sizeof(MeshOperatorRendererMeshVertex));
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
                        Builder::device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 
                                                         2, 
                                                         &selectedFaceToDraw, 
                                                         sizeof(MeshOperatorRendererMeshVertex));
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
}