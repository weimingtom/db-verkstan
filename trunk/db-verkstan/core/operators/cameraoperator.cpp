#include "core/operators/cameraoperator.hpp"

void CameraOperator::render()
{
    globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

    D3DXCOLOR color = getColorProperty(3);
    globalDirect3DDevice->Clear(0, 
                           NULL, 
                           D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                           color, 
                           1.0f, 
                           0);

    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render();
}

void CameraOperator::process()
{
    float angle = getFloatProperty(0);
    int ratioWidth = getIntProperty(1);
    int ratioHeight = getIntProperty(2);
    D3DXVECTOR3 translationVector = getVectorProperty(4);
    D3DXVECTOR3 lookAtVector = getVectorProperty(5);
    float rotation = getFloatProperty(6);

    D3DXMatrixPerspectiveFovLH(&projectionMatrix, 
                               angle, 
                               ratioWidth / (float)ratioHeight, 
                               0.1f, 
                               100.0f);

    D3DXMATRIX lookAtMatrix;
    D3DXMatrixLookAtLH(&lookAtMatrix,
                       &translationVector,
                       &lookAtVector,
                       &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationZ(&rotationMatrix, rotation);
    viewMatrix = lookAtMatrix * rotationMatrix;
}
