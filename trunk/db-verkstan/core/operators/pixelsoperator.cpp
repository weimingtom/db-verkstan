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

    int color1 = getIntProperty(0);
    int color2 = getIntProperty(1);
    int count = getIntProperty(2);
    int seed = getIntProperty(3);

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
