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

void drawProgressBar(float progress)
{
    HDC hdc = GetDC(globalWindow);
    SelectObject(hdc, CreateSolidBrush(0x00000000));
    Rectangle(hdc, 0, 0, 640, 480);

    SelectObject(hdc, CreateSolidBrush(0x00505050));
    Rectangle(hdc, 20, 220, 600, 260);
    SelectObject(hdc, CreateSolidBrush(0x00ffffff));
    Rectangle(hdc, 20, 220, 20 + (int)(580 * progress), 260);
}

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
    d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dPresentParameters.hDeviceWindow = globalWindow;
    d3dPresentParameters.EnableAutoDepthStencil = TRUE;
    d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
    d3dPresentParameters.BackBufferCount = 1; 
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
    globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

    D3DXCreateMatrixStack(0, &globalWorldMatrixStack);

    drawProgressBar(0.0f);
    Synth* synth = new Synth(globalWindow);
    loadGraphics();

    // Do a process before the demo starts. We do it backwards
    // so all operators will have their input ready as the root
    // operator has the lowest index and the top rightmost operator
    // has the highest index.
    for (unsigned short i = 0; i < numberOfOperators; i++)
    {
        operators[numberOfOperators - i - 1]->process();
        drawProgressBar(i / (float)numberOfOperators);
    }

    operators[0]->cascadeProcess();
    drawProgressBar(1.0f);
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
