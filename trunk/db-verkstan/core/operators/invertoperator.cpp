#include "core/operators/invertoperator.hpp"

void InvertOperator::process()
{
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);
    texture->lock();
    input->texture->lock();

    DWORD* destPixels = (DWORD*)texture->d3d9LockedRect.pBits;
    DWORD* srcPixels = (DWORD*)input->texture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
             destPixels[x + y * pitch] = (~srcPixels[x + y * pitch]) | 0xff000000;
        }
    }

    input->texture->unlock();
    texture->unlock();
}
