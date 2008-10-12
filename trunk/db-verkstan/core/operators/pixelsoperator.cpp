#include "core/operators/pixelsoperator.hpp"

void PixelsOperator::render()
{

}

void PixelsOperator::process()
{
    if (texture == 0)
        texture = new Texture();

    texture->fillRectangle(0, 0, 256, 256, 0xff000000);

    int color = getIntProperty(0);
    int count = getIntProperty(1);
    int seed = getIntProperty(2);

    texture->lock();
    srand(seed);
    DWORD* pixels = (DWORD*)texture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);
    for (int i = 0; i < count; i++)
        pixels[pitch * (rand()%256) + (rand()%256)] = color; 
    texture->unlock();
}
