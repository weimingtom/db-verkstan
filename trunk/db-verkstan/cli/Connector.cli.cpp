#include "cli/Connector.hpp"

namespace Verkstan
{
    void Connector::Connect(Operator^ sender, Operator^ receiver)
    {
        receiver->ConnectWithJointAsReceiver(sender->GetPrimaryJoint());
    }

    void Connector::Disconnect(Operator^ op)
    {
        op->DisconnectFromAllJoints();
    }
}