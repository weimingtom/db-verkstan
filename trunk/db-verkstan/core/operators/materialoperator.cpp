#include "core/operators/materialoperator.hpp"

void MaterialOperator::render(int tick)
{
    Operator* textureOperator = getInput(1);
    if (textureOperator != 0)
        globalDirect3DDevice->SetTexture(0, textureOperator->texture->getD3D9Texture());
    globalDirect3DDevice->SetMaterial(&d3d9Material);
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
    getInput(0)->mesh->render();
    globalDirect3DDevice->SetTexture(0, 0);	
}

void MaterialOperator::process()
{
    ZeroMemory(&d3d9Material, sizeof(d3d9Material));
    d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 1.0f;
    d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 1.0f;
    d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 1.0f;
    d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 1.0f;
}
