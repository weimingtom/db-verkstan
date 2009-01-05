extern "C"
{
    int __cdecl _ftol2(float f)
    {
        volatile int result;
        __asm fistp result;
        return result;
    }

    int __cdecl _ftol2_sse(float f)
    {
        volatile int result;
        __asm fistp result;
        return result;
    }
}

#include "core/core.hpp"
#include "core/globals.hpp"
#include "core/loader.hpp"
#include "core/metronome.hpp"
#include "synth.h"

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    if (msg == WM_KEYDOWN && VK_ESCAPE == wParam)
    {
        PostQuitMessage(0);
        return FALSE;
    }
   
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE instance, 
                   HINSTANCE previousInstance, 
                   LPSTR commandLne, 
                   int showCommand)
{
    WNDCLASSEX windowClass;
    
    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = windowProcedure;
    windowClass.hInstance = instance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    windowClass.lpszClassName = "db";
    RegisterClassEx(&windowClass);
 
    globalWindow = CreateWindow("db",
                                "db - alpha",
                                WS_VISIBLE,
                                20, 
                                0, 
                                640, 
                                480,
                                NULL, 
                                NULL, 
                                instance, 
                                NULL);

    globalDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
    D3DDISPLAYMODE displayMode;
    globalDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

    D3DPRESENT_PARAMETERS d3dPresentParameters;
    ZeroMemory(&d3dPresentParameters, sizeof(d3dPresentParameters));
    d3dPresentParameters.Windowed = TRUE;
    d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dPresentParameters.hDeviceWindow = globalWindow;
    d3dPresentParameters.EnableAutoDepthStencil = TRUE;
    d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
    d3dPresentParameters.BackBufferCount= 1; 
    d3dPresentParameters.BackBufferFormat = displayMode.Format;
    d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    globalDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
                                 D3DDEVTYPE_HAL,
                                 globalWindow,
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                 &d3dPresentParameters,
                                 &globalDirect3DDevice);
    globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    globalDirect3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128));
    globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); 

    globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    globalDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

    D3DXCreateMatrixStack(0, &globalWorldMatrixStack);

    Synth* synth = new Synth(globalWindow);

    loadGraphics();
    startMetronome();

    while (true)
    {
        int tick = getTick();

        if (operators[0]->ticks < tick)
            break;

        MSG msg;
        if (PeekMessage(&msg, globalWindow, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
      
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {  
            operators[0]->cascadeProcess();
            D3DLIGHT9 d3dLight;
            ZeroMemory(&d3dLight, sizeof(d3dLight));
            d3dLight.Type = D3DLIGHT_DIRECTIONAL;
          
            d3dLight.Diffuse.r = 1.0f;
            d3dLight.Diffuse.g = 1.0f;
            d3dLight.Diffuse.b = 1.0f;
            d3dLight.Diffuse.a = 1.0f;

            D3DVECTOR position;
            position.x = -1.0f;
            position.y = -1.0f;
            position.z = -1.0f;
            d3dLight.Position = position;

            D3DVECTOR direction;
            direction.x = 1.0f;
            direction.y = 0.0f;
            direction.z = 0.0f;
            d3dLight.Direction = direction;

            globalDirect3DDevice->SetLight(0, &d3dLight); 
            globalDirect3DDevice->LightEnable(0, TRUE);

            operators[0]->preRender(tick);

            globalWorldMatrixStack->LoadIdentity();
            globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
            
            globalDirect3DDevice->BeginScene();
            operators[0]->render(tick);
            globalDirect3DDevice->EndScene();

            globalDirect3DDevice->Present(NULL, NULL, NULL, NULL);
        }
    }

    delete synth;
    globalDirect3DDevice->Release();
    globalDirect3D->Release();
    ExitProcess(0);

    return 0;
}
