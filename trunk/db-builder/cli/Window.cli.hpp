#pragma once

namespace Verkstan 
{
    ref class OperatorBinding;
    ref class Renderer;
    
	public ref class Window
	{
    public:
        Window();
        
        property OperatorBinding^ ViewedOperator
        {
            OperatorBinding^ get();
            void set(OperatorBinding^ viewedOperator);
        }
        property int ClearColor
        {
            int get();
            void set(int clearColor);
        }
        property bool TextureTiling
        {
            bool get();
            void set(bool tiling);
        }
        property bool TextureFiltering
        {
            bool get();
            void set(bool filtering);
        }
        property bool MeshSolid
        {
            bool get();
            void set(bool filtering);
        }
        property bool ModelLightning
        {
            bool get();
            void set(bool lightning);
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
	};
}
