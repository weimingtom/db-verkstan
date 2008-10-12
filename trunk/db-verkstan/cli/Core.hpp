#pragma once

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "cli/Operator.hpp"

namespace Verkstan 
{
	public ref class Core
	{
    public:
        static void Boot(void* windowPtr);
        static void Shutdown();
        static void Render();
        static void Resize();
        static property Operator^ ViewedOperator
        {
            Operator^ get();
            void set(Operator^ viewedOperator);
        }
        static property int ClearColor
        {
            int get();
            void set(int clearColor);
        }
    private:
        static void Reset();
        static Operator^ viewedOperator;
        static bool resetDevice = false;
        static int clearColor;
	};
}
