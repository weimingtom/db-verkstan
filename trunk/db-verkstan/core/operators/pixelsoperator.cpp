#include "core/operators/pixelsoperator.hpp"

void PixelsOperator::render()
{

}

void PixelsOperator::process()
{
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);

    if (input != 0)
        input->texture->copy(texture);
    else
        texture->fillRectangle(0, 0, 256, 256, 0xff000000);

    unsigned char r1 = getIntProperty(0);
    unsigned char g1 = getIntProperty(1);
    unsigned char b1 = getIntProperty(2);
    unsigned char r2 = getIntProperty(3);
    unsigned char g2 = getIntProperty(4);
    unsigned char b2 = getIntProperty(5);
    int count = getIntProperty(6);
    int seed = getIntProperty(7);
    D3DXCOLOR color1 = D3DXCOLOR(D3DCOLOR_XRGB(r1, g1, b1));
    D3DXCOLOR color2 = D3DXCOLOR(D3DCOLOR_XRGB(r2, g2, b2));
    texture->lock();
    srand(seed);
    DWORD* pixels = (DWORD*)texture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);
    D3DXCOLOR color;
    for (int i = 0; i < count; i++)
    {
        D3DXColorLerp(&color, &color1, &color2, rand() / (float)RAND_MAX);
        pixels[pitch * (rand()%256) + (rand()%256)] = color; 
    }
    texture->unlock();
}
