#include "core/operators/materialoperator.hpp"

void MaterialOperator::render()
{
    Operator* meshOperator = getInput(0);
    Operator* textureOperator = getInput(1);

    System::Console::WriteLine("Input 1 = " + inputs[1]);

    ZeroMemory(&d3d9Material, sizeof(d3d9Material));
    d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 1.0f;
    d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 1.0f;
    d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 1.0f;
    globalDirect3DDevice->SetTexture(0, textureOperator->texture->getD3D9Texture());
    globalDirect3DDevice->SetMaterial(&d3d9Material);
    globalDirect3DDevice->SetFVF(meshOperator->mesh->d3d9Mesh->GetFVF());   
    meshOperator->mesh->d3d9Mesh->DrawSubset(0);
    globalDirect3DDevice->SetTexture(0, 0);	
}

void MaterialOperator::process()
{
   
}
