#include "core.hpp"
#include "globals.hpp"

#include "CoreBinding.hpp"

#include "Constants.hpp"

namespace VerkstanBindings
{
    void CoreBinding::Boot(void* windowPtr)
    {
        globalWindow = (HWND)windowPtr;
        RECT rect;
        GetWindowRect(globalWindow, &rect);
        WINDOW_WIDTH = rect.right - rect.left;
        WINDOW_HEIGHT = rect.bottom - rect.top;

        globalDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
        D3DDISPLAYMODE displayMode;
        globalDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
        D3DPRESENT_PARAMETERS d3dPresentParameters;
        ZeroMemory(&d3dPresentParameters, sizeof(d3dPresentParameters));
        d3dPresentParameters.Windowed = TRUE;
        d3dPresentParameters.hDeviceWindow = globalWindow;
        d3dPresentParameters.BackBufferFormat = displayMode.Format;
        d3dPresentParameters.EnableAutoDepthStencil = TRUE;
        d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
        d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        d3dPresentParameters.BackBufferWidth  = WINDOW_WIDTH;
		d3dPresentParameters.BackBufferHeight = WINDOW_HEIGHT;
        d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dPresentParameters.BackBufferCount= 1;

        globalDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
                                     D3DDEVTYPE_HAL,
                                     globalWindow,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                     &d3dPresentParameters,
                                     &globalDirect3DDevice);

        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
    }

    void CoreBinding::Resize()
    {
        resetDevice = true;
    }

    void CoreBinding::Reset()
    {
        RECT rect;
        GetWindowRect(globalWindow, &rect);
        WINDOW_WIDTH = rect.right - rect.left;
        WINDOW_HEIGHT = rect.bottom - rect.top;
        D3DDISPLAYMODE displayMode;
        globalDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

        D3DPRESENT_PARAMETERS d3dPresentParameters;
        ZeroMemory(&d3dPresentParameters, sizeof(d3dPresentParameters));
        d3dPresentParameters.Windowed = TRUE;
        d3dPresentParameters.hDeviceWindow = globalWindow;
        d3dPresentParameters.BackBufferFormat = displayMode.Format;
        d3dPresentParameters.EnableAutoDepthStencil = TRUE;
        d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
        d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        d3dPresentParameters.BackBufferWidth  = WINDOW_WIDTH;
	    d3dPresentParameters.BackBufferHeight = WINDOW_HEIGHT;
        d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dPresentParameters.BackBufferCount= 1;
        
        for (int i = 0; i < DB_MAX_OPERATORS; i++)
        {
            if (operators[i] != 0)
            {
                operators[i]->deviceLost();
            }
        }

        HRESULT result = globalDirect3DDevice->Reset(&d3dPresentParameters);
        
        if (result == D3DERR_INVALIDCALL)
        {
            MessageBoxA(NULL, 
                        "blabal",
                       "ERROR", 
                       MB_OK | MB_ICONEXCLAMATION );
        }

        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

        resetDevice = false;
    }

    void CoreBinding::Shutdown()
    {
        globalDirect3DDevice->Release();
        globalDirect3D->Release();
    }
    
    void CoreBinding::Render()
    {
        if (resetDevice)
        {
            CoreBinding::Reset();
        }
        else
        {
            globalDirect3DDevice->Clear(0, 
                                       NULL, 
                                       D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                       clearColor, 
                                       1.0f, 
                                       0);
            
            if (viewedOperatorBinding != nullptr)
            {
                viewedOperatorBinding->CascadeProcess();

                if (viewedOperatorBinding->Type == Constants::OperatorTypes::Texture)
                    RenderTexture();
            }

            HRESULT result = globalDirect3DDevice->Present(NULL, NULL, NULL, NULL);

            if (result == D3DERR_DEVICELOST)
			    resetDevice = true;     
        }
    }

    void CoreBinding::RenderTexture()
    {
        Operator* op = operators[viewedOperatorBinding->Id];

        D3DXMATRIX projection;
        D3DXMatrixPerspectiveFovLH(&projection, 
                                   D3DXToRadian(45.0f), 
                                   WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
                                   1.0f, 
                                   100.0f);
        globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &projection);

        D3DXMATRIX world;
        D3DXMATRIX view;
        D3DXMatrixTranslation(&world, 0.0f,0.0f,0.0f);
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, &world);
       
        D3DXMatrixLookAtLH(&view,
                           &D3DXVECTOR3(0.0f, 0.0f, -2.5f),
                           &D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                           &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
        globalDirect3DDevice->SetTransform(D3DTS_VIEW, &view);

        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

        globalDirect3DDevice->BeginScene();

        VertexWithTexture vertices[]=
        {
           { -1.0f, -1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 1.0f },
           { -1.0f,  1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f },
           {  1.0f, -1.0f, 0.0f, 0xFFFFFFFF, 1.0f, 1.0f },
           {  1.0f,  1.0f, 0.0f, 0xFFFFFFFF, 1.0f, 0.0f },
        };

        if (op->texture != 0)
            globalDirect3DDevice->SetTexture(0, op->texture->getD3D9Texture());		
        globalDirect3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);
        globalDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
                                              2,
                                              &vertices, 
                                              sizeof(VertexWithTexture));
        globalDirect3DDevice->SetTexture(0, 0);	
        globalDirect3DDevice->EndScene();
    }

    OperatorBinding^ CoreBinding::ViewedOperatorBinding::get()
    {
        return viewedOperatorBinding;
    }

    void CoreBinding::ViewedOperatorBinding::set(OperatorBinding^ viewedOperatorBinding)
    {
        CoreBinding::viewedOperatorBinding = viewedOperatorBinding;
    }

    int CoreBinding::ClearColor::get()
    {
        return clearColor;
    }

    void CoreBinding::ClearColor::set(int clearColor)
    {
        CoreBinding::clearColor = clearColor;
    }
}