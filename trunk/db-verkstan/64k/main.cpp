#include "core/globals.hpp"
#include <windows.h>

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    if (msg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return FALSE;
    }
    else if (msg == WM_CLOSE)
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
    windowClass.lpszClassName = L"db";
    RegisterClassEx(&windowClass);

    DWORD style = WS_MINIMIZEBOX | WS_BORDER | WS_VISIBLE;// WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
 
    globalWindow = CreateWindow(L"db",
                                L"db - alpha",
                                style,
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

    bool running = true;
    while (running)
    {
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
            globalDirect3DDevice->Clear(0, 
                                        NULL, 
                                        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                        D3DCOLOR_XRGB(0, 0, 0), 
                                        1.0f, 
                                        0);
            globalDirect3DDevice->BeginScene();
            globalDirect3DDevice->EndScene();
            globalDirect3DDevice->Present(NULL, NULL, NULL, NULL);
        }
    }

    globalDirect3DDevice->Release();
    globalDirect3D->Release();
    UnregisterClass(L"db", GetModuleHandle(NULL));
	return 0;
}