#pragma once

namespace Verkstan 
{
    ref class Operator;
    ref class Renderer;
    
	public ref class Window
	{
    public:
        Window();
        
        property Operator^ ViewedOperator
        {
            Operator^ get();
            void set(Operator^ viewedOperator);
        }
        property int ClearColor
        {
            int get();
            void set(int clearColor);
        }

        void Boot(void* windowPtr);
        void Shutdown();
        void Render();
        void Resize();
        void MouseDown(int button, int x, int y);
        void MouseMove(int x, int y);
        void MouseUp(int button, int x, int y);

    private:
        void Reset();
        Operator^ viewedOperator;
        bool resetDevice;
        Renderer^ renderer;
	};
}
