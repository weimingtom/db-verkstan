#include "flatoperator.hpp"

void FlatOperator::process()
{
    if (texture == 0)
        texture = new Texture();

    int color = getIntProperty(0);
    texture->fillRectangle(0, 0, 256, 256, color);
}
