#include "core/operators/rectangleoperator.hpp"

void RectangleOperator::render()
{

}

void RectangleOperator::process()
{    
    if (texture == 0)
        texture = new Texture();

    getInput(0)->texture->copy(texture);

    unsigned char r = getByteProperty(0);
    unsigned char g = getByteProperty(1);
    unsigned char b = getByteProperty(2);
    unsigned char x = getByteProperty(3);
    unsigned char y = getByteProperty(4);
    unsigned char width = getByteProperty(5);
    unsigned char height = getByteProperty(6);

    texture->fillRectangle(x, y, width, height, D3DCOLOR_XRGB(r, g, b));
}
