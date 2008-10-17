#include "cli/Connector.hpp"

#include "cli/LoadOperator.hpp"
#include "cli/StoreOperator.hpp"

namespace Verkstan
{
    void Connector::Connect(Operator^ sender, Operator^ receiver)
    {
        if (sender->GetType() == StoreOperator::typeid)
        {
            return;
        }
        else if (receiver->GetType() == LoadOperator::typeid)
        {
            return;
        }   
        else if (receiver->GetType() == StoreOperator::typeid)
        {
            sender->ConnectWithJointAsSender(receiver->GetPrimaryJoint());
        }
        else if (sender->GetType() == LoadOperator::typeid)
        {
            receiver->ConnectWithJointAsReceiver(sender->GetPrimaryJoint());
            LoadOperator^ loadOp = (LoadOperator^)sender;
            loadOp->AddReceiver(receiver);
        }
        else
        {
            receiver->ConnectWithJointAsReceiver(sender->GetPrimaryJoint());
        }
    }

    void Connector::Disconnect(Operator^ op)
    {
        op->DisconnectFromAllJoints();
    }
}