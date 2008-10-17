#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/StoreOperator.hpp"
#include "cli/Joint.hpp"
#include "cli/Joints.hpp"

namespace Verkstan
{
    StoreOperator::StoreOperator(List<OperatorProperty^>^ properties)
                             : Operator("Store", 
                                        -1, 
                                        Constants::OperatorTypes::Store, 
                                        Constants::OperatorTypes::Store,
                                        properties)
    {
        primaryJoint = gcnew Joint();
        Joints::Add(primaryJoint);
    }

    StoreOperator::~StoreOperator()
    {
        Joints::Remove(primaryJoint);
    }

    unsigned char StoreOperator::GetByteProperty(int index)
    {
        return 0;
    }

    void StoreOperator::SetByteProperty(int index, unsigned char value)
    {

    }

    int StoreOperator::GetIntProperty(int index)
    {
         return 0;
    }

    void StoreOperator::SetIntProperty(int index, int value)
    {

    }

    float StoreOperator::GetFloatProperty(int index)
    {
        return 0.0f;
    }

    void StoreOperator::SetFloatProperty(int index, float value)
    {

    }

    String^ StoreOperator::GetStringProperty(int index)
    {   
        if (index == 0)
            return primaryJoint->Name;

        return gcnew String("");   
    }

    void StoreOperator::SetStringProperty(int index, String^ string)
    {
        if (index == 0)
            primaryJoint->Name = string;
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