#pragma once

struct WindowInfo
{
	IDirect3D9* direct3D;
	HWND window;
	LPDIRECT3DDEVICE9 device;
	int width, height;
};

WindowInfo createD3DWindow(int width, int height, bool windowed);