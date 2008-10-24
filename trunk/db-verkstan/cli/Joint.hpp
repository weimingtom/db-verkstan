#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref class Operator;

    public ref class Joint
    {
    public:
        String^ Name;
        Joint();

        property Operator^ Sender
        {
            Operator^ get();
        }

        property List<Operator^>^ Receivers
        {
            List<Operator^>^ get();
        }

        void ConnectSender(Operator^ op);
        void DisconnectSender(Operator^ op);
        void ConnectReceiver(Operator^ op);
        void DisconnectReceiver(Operator^ op);
        void DisconnectAllReceivers();

        void AddListener(Operator^ op);
        void RemoveListener(Operator^ op);

    private:
        Operator^ sender;
        List<Operator^>^ receivers;
        List<Operator^>^ listeners;
    };
}