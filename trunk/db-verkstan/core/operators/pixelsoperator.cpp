#include "core/operators/pixelsoperator.hpp"

void PixelsOperator::process()
{
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);

    if (input != 0)
        input->texture->copy(texture);
    else
        texture->fillRectangle(0, 0, 256, 256, 0xff000000);

    D3DXCOLOR color1 = getColorProperty(0);
    D3DXCOLOR color2 = getColorProperty(1);
    int count = getIntProperty(2);
    int seed = getIntProperty(3);

    texture->lock();
    //srand(seed);
    DWORD* pixels = (DWORD*)texture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);
    D3DXCOLOR color;
    for (int i = 0; i < count; i++)
    {
        D3DXColorLerp(&color, &color1, &color2, frand());
      //  pixels[pitch * (rand()%256) + (rand()%256)] = color; 
    }
    texture->unlock();
}
