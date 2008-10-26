#pragma once

#include "cli/CoreOperatorProxy.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref class Clip;
    public ref class SceneOperator: public CoreOperatorProxy
	{
    public:
        SceneOperator(Operator^ sceneOperator);
        void AddClip(Clip^ clip);
        void RemoveClip(Clip^ clip);

    private:
        List<Clip^>^ clips;
        void UpdateClips();
	};
}