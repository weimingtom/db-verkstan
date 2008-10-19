#include "core/operators/flatoperator.hpp"

void FlatOperator::render()
{

}

void FlatOperator::process()
{
    if (texture == 0)
        texture = new Texture();

    unsigned char r = getByteProperty(0);
    unsigned char g = getByteProperty(1);
    unsigned char b = getByteProperty(2);
    texture->fillRectangle(0, 0, 256, 256, D3DCOLOR_XRGB(r, g, b));
}
