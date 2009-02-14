#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::normalMap(Texture* texture, int amplify, bool inPlace)
{
    Texture* newTexture = new Texture();

    D3DXComputeNormalMap(newTexture->getD3D9Texture(),
                         texture->getD3D9Texture(),
                         NULL,
                         0,
                         D3DX_CHANNEL_RED,
                         amplify);
    LPDIRECT3DSURFACE9 surface;
    newTexture->getD3D9Texture()->GetSurfaceLevel(0, &surface);
    D3DXLoadSurfaceFromSurface(newTexture->d3d9Surface, 
                               NULL, 
                               NULL, 
                               surface, 
                               NULL, 
                               NULL, 
                               D3DX_FILTER_NONE,
                               0);
    return newTexture;
}