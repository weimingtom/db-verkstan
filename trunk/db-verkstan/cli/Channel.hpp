#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref class Clip;
    ref class SceneOperator;

    public ref class Channel
    {
    public:
        Channel(SceneOperator^ owner);
        property int Number
        {
            int get();
            void set(int number);
        }
        void AddClip(Clip^ clip);
        void RemoveClip(Clip^ clip);
        property List<Clip^>^ Clips
        {
            List<Clip^>^ get();
        }

    private:
        int number;
        List<Clip^>^ clips;
        SceneOperator^ owner;
    };
}