#pragma once

#include "renderable.hpp"
#include "mesh.hpp"
#include "texture.hpp"

enum Filters
{
    BlurTextureFilter,
    PixelsTextureFilter
};

class TextureFilters
{
public:
    static Texture* pixels(Texture* texture, D3DXCOLOR color1, D3DXCOLOR color2, int count, int seed, bool inPlace = false);
    static Texture* blur(Texture* texture, int passes, int width, int amplify, int mode = 3);
};

class MeshFilters
{
public:
};

class RenderableFilters
{
public:
};