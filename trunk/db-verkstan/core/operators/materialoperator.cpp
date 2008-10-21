#include "core/operators/materialoperator.hpp"

void MaterialOperator::render()
{
    Operator* meshOperator = getInput(0);
    Operator* textureOperator = getInput(1);

    ZeroMemory(&d3d9Material, sizeof(d3d9Material));
    d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 1.0f;
    d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 1.0f;
    d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 1.0f;
    d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 1.0f;
    globalDirect3DDevice->SetTexture(0, textureOperator->texture->getD3D9Texture());
    globalDirect3DDevice->SetMaterial(&d3d9Material);

    Mesh* mesh = meshOperator->mesh;
    globalWorldMatrixStack->Push();
    globalWorldMatrixStack->Scale(mesh->scale.x,
                                  mesh->scale.y,
                                  mesh->scale.z);
    globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(1.0f, 0.0f, 0.0f),
                                       mesh->rotation.x);
    globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 1.0f, 0.0f),
                                       mesh->rotation.y);
    globalWorldMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 0.0f, 1.0f),
                                       mesh->rotation.z);
    globalWorldMatrixStack->Translate(mesh->translation.x,
                                      mesh->translation.y,
                                      mesh->translation.z); 
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
    mesh->d3d9Mesh->DrawSubset(0);
    globalWorldMatrixStack->Pop();

    globalDirect3DDevice->SetTexture(0, 0);	
}

void MaterialOperator::process()
{
   
}
