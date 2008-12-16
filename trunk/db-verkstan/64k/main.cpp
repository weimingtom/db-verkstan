#pragma comment (linker, "/MERGE:.rdate=.data")
#pragma comment (linker, "/MERGE:.text=.data") 

#include "core/core.hpp"
#include "synth.h"
#define OPERATOR_HEADERS 1
#include "core/operators.hpp"
#undef OPERATOR_HEADERS
#include "core/globals.hpp"

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

    Synth* synth = new Synth(globalWindow);
#include "data.hpp"
#include "core/loader.hpp"

    float s = sinf(-2.0f);

    if (s == 0.0f)
        return 0;

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

    delete synth;
    globalDirect3DDevice->Release();
    globalDirect3D->Release();
    UnregisterClass("db", GetModuleHandle(NULL));

    return 0;
}

int WINAPI WinMainCRTStartup(void)
{
    //  static unsigned short ctrl = 0x177F;
    //__asm fldcw ctrl; 

    
    STARTUPINFO				StartupInfo={sizeof(STARTUPINFO),0};
 
    int				        mainret;
    char				*lpszCommandLine = GetCommandLine();
    
      
    // skip past program name (first token in command line).
    if( *lpszCommandLine == '"' )  // check for and handle quoted program name
    {
        // scan, and skip over, subsequent characters until  another
        // double-quote or a null is encountered
        while( *lpszCommandLine && (*lpszCommandLine != '"') )
            lpszCommandLine++;

        // if we stopped on a double-quote (usual case), skip over it.
        if( *lpszCommandLine == '"' )
            lpszCommandLine++;
    }
    
    else    
    {
        // first token wasn't a quote
        while ( *lpszCommandLine > ' ' )
            lpszCommandLine++;
    }

    // skip past any white space preceeding the second token.
    while ( *lpszCommandLine && (*lpszCommandLine <= ' ') )
        lpszCommandLine++;

    
    GetStartupInfo(&StartupInfo);
 
    mainret = WinMain( GetModuleHandle(NULL),
                       NULL,
                       lpszCommandLine,
                       StartupInfo.dwFlags & STARTF_USESHOWWINDOW
                            ? StartupInfo.wShowWindow : SW_SHOWDEFAULT );

    ExitProcess(mainret);
    
    return mainret;
}
