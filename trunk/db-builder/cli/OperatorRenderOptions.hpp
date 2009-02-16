#pragma once

namespace Verkstan
{
    public ref class OperatorRenderOptions
    {
    public:
        OperatorRenderOptions()
        {
            ClearColor = 0xff505050;
            TextureTiling = false;
            TextureFiltering = false;
            MeshShaded = false;
            ModelLightning = false;
        }

        int ClearColor;
        bool TextureTiling;
        bool TextureFiltering;
        bool MeshShaded;
        bool ModelLightning;
    };
}