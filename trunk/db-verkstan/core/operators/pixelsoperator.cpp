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
    int color1 = D3DCOLOR_XRGB(r1, g1, b1);
    int color2 = D3DCOLOR_XRGB(r2, g2, b2);
    texture->lock();
    srand(seed);
    DWORD* pixels = (DWORD*)texture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);
    for (int i = 0; i < count; i++)
    {
        int color = rand() % 2 == 0? color1 : color2;
        pixels[pitch * (rand()%256) + (rand()%256)] = color; 
    }
    texture->unlock();
}
