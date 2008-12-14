#pragma once

#define D3DCOLOR_A(c) (((c)&0xff000000)>>24)
#define D3DCOLOR_R(c) (((c)&0x00ff0000)>>16)
#define D3DCOLOR_G(c) (((c)&0x0000ff00)>>8)
#define D3DCOLOR_B(c) ((c)&0x000000ff)

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