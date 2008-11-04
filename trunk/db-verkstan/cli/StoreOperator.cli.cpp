#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/StoreOperator.hpp"
#include "cli/internal/Joint.hpp"
#include "cli/internal/Joints.hpp"

namespace Verkstan
{
    StoreOperator::StoreOperator()
                             : Operator("Store", 
                                        -1, 
                                        Constants::OperatorTypes::Store)
    {
        primaryJoint = gcnew Joint();
        Joints::Add(primaryJoint);
    }

    StoreOperator::~StoreOperator()
    {
        Joints::Remove(primaryJoint);
    }

    void StoreOperator::Name::set(String^ name)
    {
        Operator::Name::set(name);
        primaryJoint->Name = name;

        if (name == nullptr || name == "")
            displayName = TypeName;
        else
            displayName = name;
    }

    bool StoreOperator::IsProcessable()
    {
        return primaryJoint->Sender != nullptr && primaryJoint->Sender->IsProcessable();
    }

    bool StoreOperator::IsWarningPresent()
    {
        return false;
    }

    Core::Operator* StoreOperator::getOperator()
    {
        if (primaryJoint->Sender != nullptr)
            return primaryJoint->Sender->getOperator();
        return 0;
    }

    Joint^ StoreOperator::GetPrimaryJoint()
    {
        return primaryJoint;
    }

    void StoreOperator::JointReceiverConnected(Joint^ joint, Operator^ op)
    {
       
    }

    void StoreOperator::JointReceiverDisconnected(Joint^ joint, Operator^ op)
    {
      
    }

    void StoreOperator::JointSenderConnected(Joint^ joint, Operator^ op)
    {     
    
    }

    void StoreOperator::JointSenderDisconnected(Joint^ joint, Operator^ op)
    {  
      
    }

    void StoreOperator::DisconnectFromAllJoints()
    {
        primaryJoint->DisconnectSender(primaryJoint->Sender);
    }

    void StoreOperator::ConnectWithJointAsReceiver(Joint^ joint)
    {
      
    }

    void StoreOperator::ConnectWithJointAsSender(Joint^ joint)
    {
      
    }
}