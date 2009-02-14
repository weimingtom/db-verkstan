#include "db-util.hpp"
#include <dxerr9.h>
#include "builder.hpp"
#include "filters.hpp"
#include "texture.hpp"

Texture* TextureFilters::text(Texture* textureJIhoiguig, 
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
                      0,
                      D3DUSAGE_RENDERTARGET,
                      D3DFMT_A8R8G8B8,
                      D3DPOOL_DEFAULT,
                      &renderTargetTexture);
    LPD3DXFONT d3d9Font;
    HRESULT result;
    result = D3DXCreateFont(Builder::device,
                   100, 
                   0, 
                   FALSE, 
                   0, 
                   FALSE,
                   DEFAULT_CHARSET, 
                   OUT_DEFAULT_PRECIS, 
                   DEFAULT_QUALITY, 
                   DEFAULT_PITCH | FF_DONTCARE, 
                   "Verdana", 
                   &d3d9Font);

    LPDIRECT3DSURFACE9 renderTargetSurface = 0;
    LPDIRECT3DSURFACE9 backbuffer = 0;
    result = renderTargetTexture->GetSurfaceLevel(0, &renderTargetSurface);
    result = Builder::device->GetRenderTarget(0, &backbuffer);
    result = Builder::device->SetRenderTarget(0, renderTargetSurface);

    RECT rect;
    rect.left = 0;
    rect.right= 255;
    rect.top = 0;
    rect.bottom = 255;
    
    Builder::device->Clear(0,
                           NULL,
                           D3DCLEAR_TARGET,
                           color,
                           1.0f,
                           0);

    result = Builder::device->BeginScene();

    result = d3d9Font->DrawText(NULL, "Olof", 4, &rect, 0, D3DCOLOR_XRGB(0, 0, 0));

    System::Console::WriteLine(gcnew System::String(DXGetErrorString9A(result)));
    // System::Console::WriteLine(gcnew System::String(DXGetErrorDescription9A(result)));
    Builder::device->EndScene();

    result = Builder::device->GetRenderTargetData(renderTargetSurface, newTexture->d3d9Surface);
    result = Builder::device->SetRenderTarget(0, backbuffer);
 
    //result = renderTargetSurface->Release();
    //result = backbuffer->Release();
    //result = renderTargetTexture->Release();   
    //result = d3d9Font->Release();
 
    return newTexture;
}