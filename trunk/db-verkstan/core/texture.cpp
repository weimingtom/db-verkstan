#include "core/texture.hpp"

#include "core/globals.hpp"

Texture::Texture()
:d3d9Texture(0)
{
    globalDirect3DDevice->CreateOffscreenPlainSurface(256,
                                                      256, 
                                                      D3DFMT_A8R8G8B8, 
                                                      D3DPOOL_SYSTEMMEM,
                                                      &d3d9Surface,
                                                      NULL);  
}

Texture::~Texture()
{
    d3d9Surface->Release();
    if (d3d9Texture != 0)
        d3d9Texture->Release();
}

LPDIRECT3DTEXTURE9 Texture::getD3D9Texture()
{
    if (d3d9Texture == 0)
    {
        D3DXCreateTexture(globalDirect3DDevice, 
                          256, 
                          256, 
                          5,
                          D3DPOOL_MANAGED,
                          D3DFMT_A8R8G8B8,
                          D3DPOOL_DEFAULT,
                          &d3d9Texture);
    }

    if (d3d9TextureDirty)
    {
        LPDIRECT3DSURFACE9 d3d9TextureSurface;
        d3d9Texture->GetSurfaceLevel(0, &d3d9TextureSurface);
        globalDirect3DDevice->UpdateSurface(d3d9Surface, 
                                            NULL,
                                            d3d9TextureSurface,
                                            NULL);
        d3d9TextureSurface->Release();
        D3DXFilterTexture(d3d9Texture, NULL, 0, D3DX_DEFAULT);
        d3d9TextureDirty = false;
    }
                                           
    return d3d9Texture;
}

void Texture::lock()
{
    d3d9Surface->LockRect(&d3d9LockedRect, NULL, NULL);
    d3d9TextureDirty = true;
}

void Texture::unlock()
{
    d3d9Surface->UnlockRect();
}

DWORD Texture::getPixel(int x, int y)
{
    DWORD* pixels = (DWORD*)d3d9LockedRect.pBits;
    return pixels[d3d9LockedRect.Pitch / sizeof(DWORD) * y + x];
}

DWORD Texture::getPixel(float x, float y)
{
    // TODO Should use billinear interpolation or something.
    return getPixel((int)x, (int)y);
}

void Texture::putPixel(int x, int y, DWORD c)
{
    DWORD* pixels = (DWORD*)d3d9LockedRect.pBits;
    pixels[d3d9LockedRect.Pitch / sizeof(DWORD) * y + x] = c;
}

void Texture::fillRectangle(int x, 
                            int y,
                            int width,
                            int height,
                            DWORD c)
{
    lock();
    DWORD* pixels = (DWORD*)d3d9LockedRect.pBits;
    int pitch = d3d9LockedRect.Pitch / sizeof(DWORD);
    for (int j = y; j < y + height; j++)
        for (int i = x; i < x + width; i++)
            pixels[pitch * j + i] =  c;
    unlock();
}

Texture* Texture::clone()
{
    Texture* clone = new Texture();
    D3DXLoadSurfaceFromSurface(clone->d3d9Surface, 
                               NULL, 
                               NULL, 
                               d3d9Surface, 
                               NULL, 
                               NULL, 
                               D3DX_FILTER_NONE,
                               0);
    return clone;
}

void Texture::copy(Texture* texture)
{
    D3DXLoadSurfaceFromSurface(texture->d3d9Surface, 
                               NULL, 
                               NULL, 
                               d3d9Surface, 
                               NULL, 
                               NULL, 
                               D3DX_FILTER_NONE,
                               0);
}