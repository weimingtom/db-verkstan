#include "core/operators/modeloperator.hpp"

void ModelOperator::render()
{
    Operator* input = getInput(0);
    Mesh* mesh = input->mesh;
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
}

void ModelOperator::process()
{
    
}
