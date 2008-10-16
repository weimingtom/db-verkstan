#include "core/operators/rectangleoperator.hpp"

void RectangleOperator::render()
{

}

void RectangleOperator::process()
{    
    if (texture == 0)
        texture = new Texture();

    getInput(0)->texture->copy(texture);

    int color = getIntProperty(0);
    unsigned char x = getByteProperty(1);
    unsigned char y = getByteProperty(2);
    unsigned char width = getByteProperty(3);
    unsigned char height = getByteProperty(4);

    texture->fillRectangle(x, y, width, height, color);
}
