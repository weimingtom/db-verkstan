#pragma once

#include "cli/CoreOperatorProxy.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref class Channel;

    public ref class SceneOperator: public CoreOperatorProxy
	{
    public:
        SceneOperator(Operator^ sceneOperator);
        void AddChannel(Channel^ channel);
        void RemoveChannel(int index);
        void RemoveChannel(Channel^ channel);
        property List<Channel^>^ Channels
        {
            List<Channel^>^ get();
        }
        void UpdateRealClips();

    private:
        List<Channel^>^ channels;
	};
}