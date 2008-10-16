#include "cli/Operator.hpp"

#include "cli/Joint.hpp"

namespace Verkstan
{   
    Joint::Joint()
    {
        Receivers = gcnew List<Operator^>();
    }

    Operator^ Joint::Sender::get()
    {
        return sender;
    }

    void Joint::Sender::set(Operator^ sender)
    {
        this->sender = sender;
        if (sender != nullptr)
            for (int i = 0; i < Receivers->Count; i++)
                sender->JointReceiverAdded(Receivers[i]);
        for (int i = 0; i < Receivers->Count; i++)
            Receivers[i]->JointSenderChanged(sender);
    }

    void Joint::AddReceiver(Operator^ op)
    {
        Receivers->Add(op);
        if (sender != nullptr)
            sender->JointReceiverAdded(op);
        op->JointSenderChanged(sender);
    }
    
    void Joint::RemoveReceiver(Operator^ op)
    {
        Receivers->Remove(op);
        if (sender != nullptr)
            sender->JointReceiverRemoved(op);
        op->JointSenderChanged(sender);
    }
}