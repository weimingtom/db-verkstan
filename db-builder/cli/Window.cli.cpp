#include "db-util.hpp"
#include "BuilderLib.hpp"
#include "Window.cli.hpp"
#include "Builder.hpp"
#include "Constants.hpp"
#include "OperatorBinding.hpp"
#include "OperatorRenderOptions.hpp"
#include "Renderer.hpp"

namespace Verkstan
{
	Window::Window() :
		window(0)
    {
        window = 0;
        direct3d = 0;
        resetDevice = false;
        renderer = gcnew Renderer();
        renderOptions = gcnew OperatorRenderOptions();
    }

    void Window::Boot(void* windowPtr)
    {
        window = (HWND)windowPtr;
        RECT rect;
        GetWindowRect(window, &rect);
        renderer->WindowWidth = rect.right - rect.left;
        renderer->WindowHeight = rect.bottom - rect.top;

        direct3d = Direct3DCreate9(D3D_SDK_VERSION);
        D3DDISPLAYMODE displayMode;
        direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
        D3DPRESENT_PARAMETERS d3dPresentParameters;
        ZeroMemory(&d3dPresentParameters, sizeof(d3dPresentParameters));
        d3dPresentParameters.Windowed = TRUE;
        d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dPresentParameters.hDeviceWindow = window;
        d3dPresentParameters.EnableAutoDepthStencil = TRUE;
        d3dPresentParameters.BackBufferFormat = displayMode.Format;
        d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
        d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        d3dPresentParameters.BackBufferCount = 1;

        direct3d->CreateDevice(D3DADAPTER_DEFAULT,
                               D3DDEVTYPE_HAL,
                               window,
                               D3DCREATE_HARDWARE_VERTEXPROCESSING,
                               &d3dPresentParameters,
                               &Builder::device);

        /*
        Builder::device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        Builder::device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        Builder::device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        Builder::device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        Builder::device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        */

        //D3DXCreateMatrixStack(0, &globalWorldMatrixStack);

        for (int i = 0; i < DB_MAX_OPERATORS; i++)
            InternalOperator::operators[i] = 0;
    }

    void Window::Resize()
    {
        resetDevice = true;
    }

    void Window::Reset()
    {
        RECT rect;
        GetWindowRect(window, &rect);
        renderer->WindowWidth = rect.right - rect.left;
        renderer->WindowHeight = rect.bottom - rect.top;
        D3DDISPLAYMODE displayMode;
        direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

        D3DPRESENT_PARAMETERS d3dPresentParameters;
        ZeroMemory(&d3dPresentParameters, sizeof(d3dPresentParameters));
        d3dPresentParameters.Windowed = TRUE;
        d3dPresentParameters.hDeviceWindow = window;
        d3dPresentParameters.BackBufferFormat = displayMode.Format;
        d3dPresentParameters.EnableAutoDepthStencil = TRUE;
        d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
        d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        d3dPresentParameters.BackBufferWidth  = renderer->WindowWidth;
        d3dPresentParameters.BackBufferHeight = renderer->WindowHeight;
        d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dPresentParameters.BackBufferCount= 1;

        for (int i = 0; i < DB_MAX_OPERATORS; i++)
        {
            if (InternalOperator::operators[i] != 0)
            {
                InternalOperator::operators[i]->deviceLost();
            }
        }

        HRESULT result = Builder::device->Reset(&d3dPresentParameters);
        
        if (result == D3DERR_INVALIDCALL)
        {
            throw gcnew Exception("Unable to reset the direct3d device!");
        }

        /*
        Builder::device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        Builder::device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        Builder::device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        Builder::device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        Builder::device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);*/

        resetDevice = false;
    }

    void Window::Shutdown()
    {
        Builder::device->Release();
        direct3d->Release();
       // globalWorldMatrixStack->Release();
    }
    
    void Window::Render()
    {
        if (resetDevice)
        {
            Reset();
        }
        else
        {
            renderer->RenderOperator(viewedOperator, renderOptions);

            HRESULT result = Builder::device->Present(NULL, NULL, NULL, NULL);

            if (result == D3DERR_DEVICELOST)
			    resetDevice = true;     
        }
    }

    OperatorBinding^ Window::ViewedOperator::get()
    {
        return viewedOperator;
    }

    void Window::ViewedOperator::set(OperatorBinding^ op)
    {
        viewedOperator = op;
    }

    OperatorRenderOptions^ Window::RenderOptions::get()
    {
        return renderOptions;
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