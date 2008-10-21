#pragma once

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

extern HWND globalWindow;
extern LPDIRECT3D9 globalDirect3D;
extern LPDIRECT3DDEVICE9 globalDirect3DDevice;
extern LPD3DXMATRIXSTACK globalProjectionMatrixStack;
extern LPD3DXMATRIXSTACK globalWorldMatrixStack;
extern LPD3DXMATRIXSTACK globalViewMatrixStack;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;