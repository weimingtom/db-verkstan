#include "core/operators/modeloperator.hpp"

void ModelOperator::render()
{
    Operator* input = getInput(0);
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
    input->mesh->d3d9Mesh->DrawSubset(0);
}

void ModelOperator::process()
{
    
}
