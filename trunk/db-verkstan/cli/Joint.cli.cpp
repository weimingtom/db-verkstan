#include "cli/Operator.hpp"

#include "cli/Joint.hpp"

namespace Verkstan
{   
    Joint::Joint()
    {
        receivers = gcnew List<Operator^>();
        senderListeners = gcnew List<Operator^>();
    }

    void Joint::DisconnectSender(Operator^ sender)
    {
        this->sender = nullptr;
        
        if (sender != nullptr)
        {
            for (int i = 0; i < receivers->Count; i++)
            {
                sender->JointReceiverDisconnected(this, receivers[i]);

                 for (int j = 0; j < senderListeners->Count; j++)
                    senderListeners[j]->JointReceiverDisconnected(this, receivers[i]);
            }
        }
        for (int i = 0; i < receivers->Count; i++)
            receivers[i]->JointSenderDisconnected(this, sender);
    }

    void Joint::ConnectSender(Operator^ sender)
    {
        this->sender = sender;
        if (sender != nullptr)
        {
            for (int i = 0; i < receivers->Count; i++)
            {
                sender->JointReceiverConnected(this, receivers[i]);

                for (int j = 0; j < senderListeners->Count; j++)
                    senderListeners[j]->JointReceiverConnected(this, receivers[i]);
            }
        }
        for (int i = 0; i < receivers->Count; i++)
            receivers[i]->JointSenderConnected(this, sender);
    }

    void Joint::ConnectReceiver(Operator^ op)
    {
        receivers->Add(op);
        if (sender != nullptr)
            sender->JointReceiverConnected(this, op);

        for (int i = 0; i < senderListeners->Count; i++)
            senderListeners[i]->JointReceiverConnected(this, op);

        op->JointSenderConnected(this, sender);
    }
    
    void Joint::DisconnectReceiver(Operator^ op)
    {
        receivers->Remove(op);
        if (sender != nullptr)
            sender->JointReceiverDisconnected(this, op);

        for (int i = 0; i < senderListeners->Count; i++)
            senderListeners[i]->JointReceiverDisconnected(this, op);

        op->JointSenderDisconnected(this, nullptr);
    }

    void Joint::DisconnectAllReceivers()
    {
        List<Operator^>^ receiversCopy = gcnew List<Operator^>(receivers);

        for (int i = 0; i < receiversCopy->Count; i++)
            DisconnectReceiver(receiversCopy[i]);
    }

    Operator^ Joint::Sender::get()
    {
        return sender;
    }

    List<Operator^>^ Joint::Receivers::get()
    {
        return receivers;
    }

    void Joint::AddSenderListener(Operator^ op)
    {
        senderListeners->Add(op);
    }

    void Joint::RemoveSenderListener(Operator^ op)
    {
        senderListeners->Remove(op);
    }
}