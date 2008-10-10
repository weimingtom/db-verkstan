#pragma once

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "OperatorBinding.hpp"

namespace VerkstanBindings 
{
	public ref class CoreBinding
	{
    public:
        static void Boot(void* windowPtr);
        static void Shutdown();
        static void Render();
        static void Resize();
        static property OperatorBinding^ ViewedOperatorBinding
        {
            OperatorBinding^ get();
            void set(OperatorBinding^ viewedOperatorBinding);
        }
        static property int ClearColor
        {
            int get();
            void set(int clearColor);
        }
    private:
        static void Reset();
        static OperatorBinding^ viewedOperatorBinding;
        static bool resetDevice = false;
        static int clearColor;
	};
}
