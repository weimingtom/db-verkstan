#include "pixelsoperator.hpp"

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
    for (int i = 0; i < count; i++)
        texture->putPixel(rand()%256, rand()%256, color);    
    texture->unlock();
}
