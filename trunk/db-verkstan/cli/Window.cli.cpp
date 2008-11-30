#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "cli/Window.cli.hpp"

#include "cli/Constants.hpp"
#include "cli/CoreOperator.hpp"
#include "cli/Renderer.hpp"

namespace Verkstan
{
    Window::Window()
    {
        resetDevice = false;
        renderer = gcnew Renderer();
    }

    void Window::Boot(void* windowPtr)
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

        D3DXCreateMatrixStack(0, &globalWorldMatrixStack);
    }

    void Window::Resize()
    {
        resetDevice = true;
    }

    void Window::Reset()
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
            if (Core::operators[i] != 0)
            {
                Core::operators[i]->deviceLost();
            }
        }

        HRESULT result = globalDirect3DDevice->Reset(&d3dPresentParameters);
        
        if (result == D3DERR_INVALIDCALL)
        {
            throw gcnew Exception("Unable to reset the direct3d device!");
        }

        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        globalDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

        resetDevice = false;
    }

    void Window::Shutdown()
    {
        globalDirect3DDevice->Release();
        globalDirect3D->Release();
        globalWorldMatrixStack->Release();
    }
    
    void Window::Render(int tick)
    {
        if (resetDevice)
        {
            Reset();
        }
        else
        {

            renderer->RenderOperator(viewedOperator, tick);

            HRESULT result = globalDirect3DDevice->Present(NULL, NULL, NULL, NULL);

            if (result == D3DERR_DEVICELOST)
			    resetDevice = true;     
        }
    }

    CoreOperator^ Window::ViewedOperator::get()
    {
        return viewedOperator;
    }

    void Window::ViewedOperator::set(CoreOperator^ op)
    {
        viewedOperator = op;
    }

    int Window::ClearColor::get()
    {
        return renderer->ClearColor;
    }

    void Window::ClearColor::set(int color)
    {
         renderer->ClearColor = color;
    }

    void Window::MouseDown(int button, int x, int y)
    {
        renderer->MouseDown(button, x, y);
    }

    void Window::MouseMove(int x, int y)
    {
        renderer->MouseMove(x, y);
    }

    void Window::MouseUp(int button, int x, int y)
    {
        renderer->MouseUp(button, x, y);
    }

    void Window::ResetCamera()
    {
        renderer->ResetCamera();
    }
}