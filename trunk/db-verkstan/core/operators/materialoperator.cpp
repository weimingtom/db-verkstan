#include "core/operators/materialoperator.hpp"

void MaterialOperator::render(int tick)
{
    Operator* textureOperator = getInput(1);
    if (textureOperator != 0)
        globalDirect3DDevice->SetTexture(0, textureOperator->texture->getD3D9Texture());
    globalDirect3DDevice->SetMaterial(&d3d9Material);
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

    globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, getByteProperty(3));

    globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); 

    getInput(0)->mesh->render();
    globalDirect3DDevice->SetTexture(0, 0);	
}

void MaterialOperator::process()
{
    ZeroMemory(&d3d9Material, sizeof(d3d9Material));
    d3d9Material.Diffuse = getColorProperty(0);
    d3d9Material.Specular = getColorProperty(1);
    d3d9Material.Ambient = getColorProperty(2);   
}
