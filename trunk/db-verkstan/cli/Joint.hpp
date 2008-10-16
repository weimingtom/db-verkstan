#pragma once

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref class Operator;

    public ref class Joint
    {
    public:
        String^ Name;
        property Operator^ Sender
        {
            Operator^ get();
            void set(Operator^ sender);
        }

        List<Operator^>^ Receivers;

        Joint();

        void AddReceiver(Operator^ op);
        void RemoveReceiver(Operator^ op);
    private:
        Operator^ sender;
    };
}