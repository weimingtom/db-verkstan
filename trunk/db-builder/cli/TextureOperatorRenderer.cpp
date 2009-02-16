#include "OperatorBinding.hpp"
#include "TextureOperatorRenderer.hpp"
#include "OperatorRenderOptions.hpp"
#include "Camera.hpp"

namespace Verkstan
{
    void TextureOperatorRenderer::render(OperatorBinding^ operatorBinding,
                                         Camera^ camera, 
                                         OperatorRenderOptions^ options)
    {
        InternalOperator* coreOp = operatorBinding->getOperator();

        if (coreOp->texture == 0)
            return;

        int textureWidth = coreOp->texture->width;
        int textureHeight = coreOp->texture->height;
        float textureRatioWidthHeight = textureWidth / (float)textureHeight;
        float textureRatioHeightWidth = textureHeight / (float)textureWidth;

        if (textureWidth > camera->WindowWidth && textureHeight > camera->WindowHeight)
        {
            if (textureWidth > textureHeight)
            {
                textureWidth = camera->WindowWidth;
                textureHeight = (int)(textureWidth * textureRatioHeightWidth);
            }
            else
            {
                textureHeight = camera->WindowHeight;
                textureWidth = (int)(textureHeight * textureRatioWidthHeight);
            }
        }
        else if (textureWidth > camera->WindowWidth)
        {
            textureWidth = camera->WindowWidth;
            textureHeight = (int)(textureWidth * textureRatioHeightWidth);
        }
        else if (textureHeight > camera->WindowHeight)
        {
            textureHeight = camera->WindowHeight;
            textureWidth = (int)(textureHeight * textureRatioWidthHeight);
        }

        float x, y, width, height, u1, u2, v1, v2;

        if (options->TextureTiling)
        {
            x = 0.0f;
            y = 0.0f;
            width = 1.0f;
            height = 1.0f;

            float texturesOnX = camera->WindowWidth / (float)textureWidth;
            float texturesOnY = camera->WindowHeight / (float)textureHeight;
            
            // We add 0.5f to center the texture. Why? Because if the
            // the texture width is the same as the window width
            // texturesOnX becomes 0.5f, and in that case we want
            // u1 = 0.0f and u2 = 1.0f.
            u1 = -texturesOnX / 2.0f + 0.5f;
            u2 =  texturesOnX / 2.0f + 0.5f;
            v1 = -texturesOnY / 2.0f + 0.5f;
            v2 =  texturesOnY / 2.0f + 0.5f;

            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
        }
        else
        {
            x = (camera->WindowWidth / 2 - textureWidth / 2) / (float)camera->WindowWidth;
            y = (camera->WindowHeight / 2 - textureHeight / 2) / (float)camera->WindowHeight;
            width = textureWidth / (float)camera->WindowWidth;
            height = textureHeight / (float)camera->WindowHeight;
            u1 = 0.0f;
            u2 = 1.0f;
            v1 = 0.0f;
            v2 = 1.0f;

            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
            Builder::device->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_BORDER);
        }

        if (options->TextureFiltering)
        {
            Builder::device->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	        Builder::device->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	        Builder::device->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
        }
        else
        {
            Builder::device->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	        Builder::device->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_NONE);
	        Builder::device->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        }

        TextureOperatorRendererTextureVertex quad[4];
        quad[0].x = x; 
        quad[0].y = y; 
        quad[0].z = 0.0f;
        quad[0].u = u1; 
        quad[0].v = v1; 
        quad[0].color = 0xffffffff;
        
        quad[1].x = x + width; 
        quad[1].y = y; 
        quad[1].z = 0.0f;
        quad[1].u = u2; 
        quad[1].v = v1; 
        quad[1].color = 0xffffffff;

        quad[2].x = x + width; 
        quad[2].y = y + height; 
        quad[2].z = 0.0f;
        quad[2].u = u2;
        quad[2].v = v2; 
        quad[2].color = 0xffffffff;

        quad[3].x = x; 
        quad[3].y = y + height; 
        quad[3].z = 0.0f;
        quad[3].u = u1; 
        quad[3].v = v2; 
        quad[3].color = 0xffffffff;

        D3DXMATRIX identityMatrix;
        D3DXMATRIX projectionMatrix;
        D3DXMatrixIdentity(&identityMatrix);
        D3DXMatrixOrthoOffCenterLH(&projectionMatrix, 
                                   0.0f, 
                                   1.0f, 
                                   1.0f, 
                                   0.0f, 
                                   -1.0f, 
                                   1.0f);
        Builder::device->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
        Builder::device->SetTransform(D3DTS_VIEW, &identityMatrix);
        Builder::device->SetTransform(D3DTS_WORLD, &identityMatrix);
        Builder::device->SetRenderState(D3DRS_LIGHTING, FALSE);
        Builder::device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        Builder::device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        Builder::device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);     
        Builder::device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
        Builder::device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
        Builder::device->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);

        Builder::device->Clear(0, 
                               NULL, 
                               D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                               options->ClearColor, 
                               1.0f, 
                               0);

        Builder::device->BeginScene();
        Builder::device->SetTexture(0, coreOp->texture->getD3D9Texture());		
        Builder::device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);
        Builder::device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &quad, sizeof(TextureOperatorRendererTextureVertex));
        Builder::device->SetTexture(0, 0);		
        Builder::device->EndScene();
    }   
}