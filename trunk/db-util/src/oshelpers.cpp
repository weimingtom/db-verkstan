#include "db-util.hpp"

WindowInfo createD3DWindow(int width, int height, bool windowed)
{
	WindowInfo windowInfo;

	windowInfo.direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	windowInfo.window = CreateWindowA("static",
		                        0,
		                        WS_POPUP | WS_VISIBLE,
                                0,
                                0,
                                width, 
                                height,
                                0, 
                                0, 
                                0, 
                                0);
    ShowCursor(0);  

	windowInfo.width = width;
	windowInfo.height = height;

	D3DPRESENT_PARAMETERS d3dPresentParameters = 
	{
	    width, height, D3DFMT_A8R8G8B8, 0, D3DMULTISAMPLE_NONE,
	    0, D3DSWAPEFFECT_DISCARD, 0, windowed, true,
	    D3DFMT_D24S8, 0, 0, D3DPRESENT_INTERVAL_IMMEDIATE 
	};

	windowInfo.direct3D->CreateDevice(D3DADAPTER_DEFAULT,
                                      D3DDEVTYPE_HAL,
                                      windowInfo.window,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &d3dPresentParameters,
                                      &windowInfo.device);

	return windowInfo;
}
