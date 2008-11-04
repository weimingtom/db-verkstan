#pragma once

#include "cli/CoreOperator.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref class Channel;

    public ref class SceneOperator: public CoreOperator
	{
    public:
        SceneOperator(String^ typeName,
                      int operatorId,
                      Constants::OperatorTypes type,
                      List<OperatorInput^>^ inputs);
        void AddChannel(Channel^ channel);
        void RemoveChannel(int index);
        void RemoveChannel(Channel^ channel);
        property List<Channel^>^ Channels
        {
            List<Channel^>^ get();
        }
        property int Beats
        {
            int get();
        }
        void UpdateRealClips();

    private:
        List<Channel^>^ channels;
	};
}