#pragma once

namespace Verkstan
{
    ref class Camera;
    ref class OperatorRenderOptions;
    ref class OperatorBinding;

    public ref class OperatorRenderer abstract
    {
    public:
        virtual void render(OperatorBinding^ operatorBinding, 
                            Camera^ camera, 
                            OperatorRenderOptions^ options) = 0;
    };
}