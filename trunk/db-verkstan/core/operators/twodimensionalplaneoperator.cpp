#include "core/operators/twodimensionalplaneoperator.hpp"

struct TwoDimensionalVertex
{
    float x, y, z;
    DWORD color;
    float u, v;
};

void TwoDimensionalPlaneOperator::render(int tick)
{    
    for (int i = 1; i < numberOfInputs; i++)
        getInput(i)->render(tick);

    D3DXMATRIX lastViewMatrix;
    D3DXMATRIX lastProjectionMatrix;
    globalDirect3DDevice->GetTransform(D3DTS_VIEW, &lastViewMatrix);
    globalDirect3DDevice->GetTransform(D3DTS_PROJECTION, &lastProjectionMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_VIEW, &identityMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
    DWORD lastLightning;
    globalDirect3DDevice->GetRenderState(D3DRS_LIGHTING, &lastLightning); 
    globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    TwoDimensionalVertex quad[4];
    quad[0].x = 0.0f; 
    quad[0].y = 0.0f; 
    quad[0].z = 0.0f;
    quad[0].u = 0.0f; 
    quad[0].v = 0.0f; 
    quad[0].color = 0xffffffff;
    
    quad[1].x = (float)WINDOW_WIDTH; 
    quad[1].y = 0.0f; 
    quad[1].z = 0.0f;
    quad[1].u = 1.0f; 
    quad[1].v = 0.0f; 
    quad[1].color = 0xffffffff;

    quad[2].x = (float)WINDOW_WIDTH; 
    quad[2].y = (float)WINDOW_HEIGHT; 
    quad[2].z = 0.0f;
    quad[2].u = 1.0f;
    quad[2].v = 1.0f; 
    quad[2].color = 0xffffffff;

    quad[3].x = 0.0f; 
    quad[3].y = (float)WINDOW_HEIGHT; 
    quad[3].z = 0.0f;
    quad[3].u = 0.0f; 
    quad[3].v = 1.0f; 
    quad[3].color = 0xffffffff;

    DWORD oldFVF;
    globalDirect3DDevice->GetFVF(&oldFVF);
    globalDirect3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);
    globalDirect3DDevice->SetTexture(0, getInput(0)->texture->getD3D9Texture());
    globalDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &quad, sizeof(TwoDimensionalVertex));
    globalDirect3DDevice->SetTexture(0, 0);
    globalDirect3DDevice->SetFVF(oldFVF);

    globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &lastProjectionMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_VIEW, &lastViewMatrix);
    globalDirect3DDevice->GetRenderState(D3DRS_LIGHTING, &lastLightning); 
}

void TwoDimensionalPlaneOperator::process()
{
    D3DXMatrixIdentity(&identityMatrix);
    D3DXMatrixOrthoOffCenterLH(&projectionMatrix, 
                               0.0f, 
                               (float)WINDOW_WIDTH, 
                               (float)WINDOW_HEIGHT, 
                               0.0f, 
                               -1.0f, 
                               1.0f);
}
