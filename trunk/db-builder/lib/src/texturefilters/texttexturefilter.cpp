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
    LPDIRECT3DTEXTURE9 renderTargetTexture;
    D3DXCreateTexture(Builder::device, 
                      256, 
                      256, 
                      D3DX_DEFAULT,
                      D3DUSAGE_RENDERTARGET,
                      D3DFMT_A8R8G8B8,
                      D3DPOOL_DEFAULT,
                      &renderTargetTexture);

    LPD3DXFONT d3d9Font;
    D3DXCreateFontA(Builder::device,
                   height, 
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

    LPDIRECT3DSURFACE9 renderTargetSurface;
    LPDIRECT3DSURFACE9 backbuffer;
    renderTargetTexture->GetSurfaceLevel(0, &renderTargetSurface);
    Builder::device->GetRenderTarget(0, &backbuffer);
    Builder::device->SetRenderTarget(0, renderTargetSurface);
    
    Texture* newTexture;
    
    if (!inPlace)
    {
        newTexture = new Texture();
    }
    else
    {
        newTexture = texture;    
    }

    if (texture != 0)
	{
        D3DXLoadSurfaceFromSurface(renderTargetSurface, 
                               NULL, 
                               NULL, 
                               newTexture->d3d9Surface, 
                               NULL, 
                               NULL, 
                               D3DX_FILTER_NONE,
                               0);
	}
	else
	{
		Builder::device->Clear(0,
                           NULL,
                           D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                           D3DCOLOR_XRGB(0,0,0),
                           1.0f,
                           0);
	}

    Builder::device->BeginScene();
    RECT rect;
    rect.left = x;
    rect.right= 256;
    rect.top = 0;
    rect.bottom = 256;
    d3d9Font->DrawTextA(NULL, text, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 0));
    Builder::device->EndScene();

    Builder::device->SetRenderTarget(0, backbuffer);
    backbuffer->Release();
    d3d9Font->Release();
    
    Builder::device->GetRenderTargetData(renderTargetSurface, newTexture->d3d9Surface);
    renderTargetSurface->Release();
    renderTargetTexture->Release();
    newTexture->setDirty();

    return newTexture;
}