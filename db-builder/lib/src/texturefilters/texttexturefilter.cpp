#include "db-util.hpp"
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::text(Texture* texture, 
                              D3DXCOLOR color, 
                              int height, 
                              int x,
                              int y,
                              const char *font, 
                              const char *text,
                              bool inPlace)
{
    Texture* newTexture = new Texture();
    LPDIRECT3DTEXTURE9 renderTargetTexture;
    D3DXCreateTexture(Builder::device, 
                      256, 
                      256,
                      1,
                      D3DUSAGE_RENDERTARGET,
                      D3DFMT_A8R8G8B8,
                      D3DPOOL_DEFAULT,
                      &renderTargetTexture);
    LPD3DXFONT d3d9Font;
    D3DXCreateFont(Builder::device,
                   100, 
                   0, 
                   FALSE, 
                   0, 
                   FALSE,
                   DEFAULT_CHARSET, 
                   OUT_DEFAULT_PRECIS, 
                   DEFAULT_QUALITY, 
                   DEFAULT_PITCH | FF_DONTCARE, 
                   font, 
                   &d3d9Font);

    LPDIRECT3DSURFACE9 renderTargetSurface = 0;
    LPDIRECT3DSURFACE9 backbuffer = 0;
    renderTargetTexture->GetSurfaceLevel(0, &renderTargetSurface);
    Builder::device->GetRenderTarget(0, &backbuffer);
    Builder::device->SetRenderTarget(0, renderTargetSurface);

    RECT rect;
    rect.left = 0;
    rect.right= 255;
    rect.top = 0;
    rect.bottom = 255;
    
    Builder::device->Clear(0,
                           NULL,
                           D3DCLEAR_TARGET,
                           D3DCOLOR_XRGB(0, 0, 0),
                           1.0f,
                           0);

    Builder::device->BeginScene();
    d3d9Font->DrawTextA(NULL, text, -1, &rect, 0, color);
    Builder::device->EndScene();

    Builder::device->GetRenderTargetData(renderTargetSurface, newTexture->d3d9Surface);
    Builder::device->SetRenderTarget(0, backbuffer);
 
    renderTargetSurface->Release();
    backbuffer->Release();
    d3d9Font->Release();
    renderTargetTexture->Release();   
 
    return newTexture;
}