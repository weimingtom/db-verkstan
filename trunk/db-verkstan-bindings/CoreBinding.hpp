#pragma once

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "OperatorBinding.hpp"

namespace VerkstanBindings 
{
    struct VertexWithTexture
    {
        float x, y, z;
        DWORD color;
        float u, v;
    };

	public ref class CoreBinding
	{
    public:
        static void Boot(void* windowPtr);
        static void Shutdown();
        static void Render();
        static void Resize();
        static void SetPreview(OperatorBinding^ previewOperator);
    private:
        static void Reset();
        static void RenderTexture();
        static OperatorBinding^ previewOperator;
        static bool resetDevice = false;
	};
}
