#include <d3d9.h>
#include <d3dx9.h>

#include "cli/Camera.hpp"
#include "cli/VerkstanCore.hpp"

namespace Verkstan
{
    Camera::Camera()
    {
        mouseDrag = false;
        leftMouseButtonHeld = false;
        rightMouseButtonHeld = false;
    }

    void Camera::Reset()
    {
        xRotation = 0.0f;
        yRotation = 0.0f;
        zoom = 0.0f;
    }

    void Camera::ApplyTransformations()
    {
        D3DXMATRIX projection;
        D3DXMatrixPerspectiveFovLH(&projection, 
                                   D3DXToRadian(45.0f), 
                                   WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
                                   0.1f, 
                                   100.0f);
        globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &projection);

        D3DXMATRIX translation;
        D3DXMatrixTranslation(&translation, 0.0f, 0.0f, zoom);
        D3DXMATRIX rotationX;
        D3DXMatrixRotationX(&rotationX, xRotation);
        D3DXMATRIX rotationY;
        D3DXMatrixRotationY(&rotationY, yRotation);
        D3DXMATRIX lookat;
        D3DXMatrixLookAtLH(&lookat,
                           &D3DXVECTOR3(0.0f, 0.0f, -3.0f),
                           &D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                           &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
        D3DXMATRIX view = rotationX * rotationY * translation * lookat;
        globalDirect3DDevice->SetTransform(D3DTS_VIEW, &view);

        //globalWorldMatrixStack->Translate(0.0f, 0.0f, zoom);
        /*
       
        D3DXMATRIX world;
        globalDirect3DDevice->GetTransform(D3DTS_WORLD, &world);
        world *= rotationX * rotationY * translation;
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, &world);
        */
    }

    void Camera::MouseDown(int button, int x, int y)
    {
        mouseDrag = true;
        lastMouseX = x;
        lastMouseY = y;

        if (button == 1)
            leftMouseButtonHeld = true;
        else if (button == 3)
            rightMouseButtonHeld = true;
    }

    void Camera::MouseMove(int x, int y)
    {
        if (leftMouseButtonHeld && rightMouseButtonHeld)
        {
             int delta = lastMouseY - y;
             zoom += delta / 100.0f;
        }
        else if (leftMouseButtonHeld)
        {
            if (mouseDrag)
            {
                int deltaX = lastMouseX - x;
                yRotation += deltaX / 100.0f;
                int deltaY = lastMouseY - y;
                xRotation += deltaY / 100.0f;
            }
        }

        lastMouseX = x;
        lastMouseY = y;
    }

    void Camera::MouseUp(int button, int x, int y)
    {
        mouseDrag = false;
        leftMouseButtonHeld = false;
        rightMouseButtonHeld = false;
    }
}