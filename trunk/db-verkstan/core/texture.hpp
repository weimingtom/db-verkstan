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
    void fillRectangle(int x, 
                       int y,
                       int width,
                       int height,
                       DWORD c);
    Texture* clone();
    void copy(Texture* texture);
    LPDIRECT3DTEXTURE9 getD3D9Texture();
    void setDirty();

    LPDIRECT3DSURFACE9 d3d9Surface;
    D3DLOCKED_RECT d3d9LockedRect; 
    LPDIRECT3DTEXTURE9 d3d9Texture;

    // Inline functions
    DWORD getPixel(int x, int y)
    {
        return ((DWORD*)d3d9LockedRect.pBits)[256 * y + x];
    }
    void putPixel(int x, int y, DWORD c)
    {
        ((DWORD*)d3d9LockedRect.pBits)[256 * y + x] = c;
    }
    DWORD getPixelWrap(float x, float y)
    {
        // Fractions
        float xFraction = x >= 0.0f ? (x - (int)x) : 1.0f + (x - (int)x);
        float yFraction = y >= 0.0f ? (y - (int)y) : 1.0f + (y - (int)y);

        int xPixel = x >= 0.0f ? (int)x : (int)x - 1;
		int yPixel = y >= 0.0f ? (int)y : (int)y - 1;

        int r = 0;
        int g = 0;
        int b = 0;

        float weight = (1.0f - xFraction) * (1.0f - yFraction);
        int xCurrent = (xPixel + 2560) % 256;
        int yCurrent = (yPixel + 2560) % 256;
        D3DCOLOR colorCurrent = getPixel(xCurrent, yCurrent);
        r += (int)(D3DCOLOR_R(colorCurrent) * weight);
        g += (int)(D3DCOLOR_G(colorCurrent) * weight);
        b += (int)(D3DCOLOR_B(colorCurrent) * weight);

        weight = xFraction * (1.0f - yFraction);
        xCurrent = (xPixel + 2561) % 256;
        yCurrent = (yPixel + 2560) % 256;
        colorCurrent = getPixel(xCurrent, yCurrent);
        r += (int)(D3DCOLOR_R(colorCurrent) * weight);
        g += (int)(D3DCOLOR_G(colorCurrent) * weight);
        b += (int)(D3DCOLOR_B(colorCurrent) * weight);

        weight = (1.0f - xFraction) * yFraction;
        xCurrent = (xPixel + 2560) % 256;
        yCurrent = (yPixel + 2561) % 256;
        colorCurrent = getPixel(xCurrent, yCurrent);
        r += (int)(D3DCOLOR_R(colorCurrent) * weight);
        g += (int)(D3DCOLOR_G(colorCurrent) * weight);
        b += (int)(D3DCOLOR_B(colorCurrent) * weight);

        weight = xFraction * yFraction;
        xCurrent = (xPixel + 2561) % 256;
        yCurrent = (yPixel + 2561) % 256;
        colorCurrent = getPixel(xCurrent, yCurrent);
        r += (int)(D3DCOLOR_R(colorCurrent) * weight);
        g += (int)(D3DCOLOR_G(colorCurrent) * weight);
        b += (int)(D3DCOLOR_B(colorCurrent) * weight);

        return D3DCOLOR_XRGB(r, g, b);
    }
};