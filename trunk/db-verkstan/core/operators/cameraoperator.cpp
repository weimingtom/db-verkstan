#include "core/operators/cameraoperator.hpp"

void CameraOperator::render()
{
    D3DXMATRIX projection;
    D3DXMatrixPerspectiveFovLH(&projection, 
                               getByteProperty(0) / 256.0f * D3DX_PI * 2.0f, 
                               getIntProperty(1) / (float)getIntProperty(2), 
                               0.1f, 
                               100.0f);
    globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &projection);

    
    D3DXMATRIX translation;
    D3DXMatrixTranslation(&translation, 
                          getFloatProperty(6), 
                          getFloatProperty(7), 
                          getFloatProperty(8));
    D3DXMATRIX rotationX;
    D3DXMatrixRotationX(&rotationX, getFloatProperty(9));
    D3DXMATRIX rotationY;
    D3DXMatrixRotationY(&rotationY, getFloatProperty(10));
    D3DXMATRIX rotationZ;
    D3DXMatrixRotationZ(&rotationZ, getFloatProperty(11));
    D3DXMATRIX lookat;
    D3DXMatrixLookAtLH(&lookat,
                       &Vec3(0.0f, 0.0f, -5.0f),
                       &Vec3(0.0f, 0.0f, 0.0f),
                       &Vec3(0.0f, 1.0f, 0.0f));
    D3DXMATRIX view = rotationX * rotationY * rotationZ * translation * lookat;
    globalDirect3DDevice->SetTransform(D3DTS_VIEW, &view);

    unsigned char r = getByteProperty(3);
    unsigned char g = getByteProperty(4);
    unsigned char b = getByteProperty(5);

    globalDirect3DDevice->Clear(0, 
                           NULL, 
                           D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                           D3DCOLOR_XRGB(r, g, b), 
                           1.0f, 
                           0);

    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render();
}

void CameraOperator::process()
{
    
}
