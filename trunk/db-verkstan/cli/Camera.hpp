#pragma once

using namespace System;

namespace Verkstan
{
    public ref class Camera
    {
    public:
        Camera();
        void Reset();
        void ApplyTransformations();
        void MouseDown(int button, int x, int y);
        void MouseMove(int x, int y);
        void MouseUp(int button, int x, int y);
    private:
        float zoom;
        float xRotation;
        float yRotation;
        bool mouseDrag;
        int lastMouseX;
        int lastMouseY;
        bool leftMouseButtonHeld;
        bool rightMouseButtonHeld;
    };
}