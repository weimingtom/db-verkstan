#include "core/globals.hpp"

HINSTANCE globalInstance;
HWND globalWindow;
LPDIRECT3D9 globalDirect3D = 0;
LPDIRECT3DDEVICE9 globalDirect3DDevice = 0;
LPD3DXMATRIXSTACK globalProjectionMatrixStack = 0;
LPD3DXMATRIXSTACK globalWorldMatrixStack = 0;
LPD3DXMATRIXSTACK globalViewMatrixStack = 0;
int WINDOW_WIDTH;
int WINDOW_HEIGHT;