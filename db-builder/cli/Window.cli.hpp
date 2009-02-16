#pragma once

namespace Verkstan 
{
    ref class OperatorBinding;
    ref class Renderer;
    ref class OperatorRenderOptions;
    
	public ref class Window
	{
    public:
        Window();
        
        property OperatorBinding^ ViewedOperator
        {
            OperatorBinding^ get();
            void set(OperatorBinding^ viewedOperator);
        }
        property OperatorRenderOptions^ RenderOptions
        {
            OperatorRenderOptions^ get();
        }

        void Boot(void* windowPtr);
        void Shutdown();
        void Render();
        void Resize();
        void MouseDown(int button, int x, int y);
        void MouseMove(int x, int y);
        void MouseUp(int button, int x, int y);
        void ResetCamera();

    private:
        void Reset();
        OperatorBinding^ viewedOperator;
        bool resetDevice;
        Renderer^ renderer;
        LPDIRECT3D9 direct3d;
        HWND window;
        OperatorRenderOptions^ renderOptions;
	};
}
