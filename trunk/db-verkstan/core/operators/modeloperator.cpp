#include "core/operators/modeloperator.hpp"

void ModelOperator::render(int tick)
{
    unsigned char cullMode = getByteProperty(0);
    if (cullMode == 0)
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    else if (cullMode == 1)
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    else if (cullMode == 2)
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    else if (cullMode == 3)
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_FORCE_DWORD);

    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
    getInput(0)->mesh->render();
}

void ModelOperator::process()
{
    
}
