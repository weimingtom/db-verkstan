#pragma once

#include <d3d9.h>
#include <d3dx9.h>

/**
 * Helper class that wraps a D3D9 texture.
 */
class Texture
{
public:
    Texture();
    ~Texture();
    void lock();
    void unlock();
    DWORD getPixel(int x, int y);
    DWORD getPixel(float x, float y);
    void putPixel(int x, int y, DWORD c);
    void fillRectangle(int x, 
                       int y,
                       int width,
                       int height,
                       DWORD c);
    Texture* clone();
    void copy(Texture* texture);
    LPDIRECT3DTEXTURE9 getD3D9Texture();
    LPDIRECT3DSURFACE9 d3d9Surface;
    bool d3d9TextureDirty;
    D3DLOCKED_RECT d3d9LockedRect; 
    LPDIRECT3DTEXTURE9 d3d9Texture;
};