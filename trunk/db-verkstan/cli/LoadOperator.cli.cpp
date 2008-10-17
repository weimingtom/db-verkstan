#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/LoadOperator.hpp"
#include "cli/Joint.hpp"
#include "cli/Joints.hpp"

namespace Verkstan
{
    LoadOperator::LoadOperator(List<OperatorProperty^>^ properties)
                             : Operator("Load", 
                                        -1, 
                                        Constants::OperatorTypes::Load, 
                                        Constants::OperatorTypes::Load,
                                        properties)
    {
        receivers = gcnew List<Operator^>();
        loadJoint = gcnew Joint();
        Joints::Add(loadJoint); 
        primaryJoint = loadJoint;
    }

    LoadOperator::~LoadOperator()
    {
        Joints::Remove(loadJoint);  
    }

    unsigned char LoadOperator::GetByteProperty(int index)
    {
        return 0;
    }

    void LoadOperator::SetByteProperty(int index, unsigned char value)
    {

    }

    int LoadOperator::GetIntProperty(int index)
    {
         return 0;
    }

    void LoadOperator::SetIntProperty(int index, int value)
    {

    }

    float LoadOperator::GetFloatProperty(int index)
    {
        return 0.0f;
    }

    void LoadOperator::SetFloatProperty(int index, float value)
    {

    }

    String^ LoadOperator::GetStringProperty(int index)
    {   
        if (index == 0)
            return primaryJoint->Name;
        return gcnew String("");   
    }

    void LoadOperator::SetStringProperty(int index, String^ string)
    {
        if (index == 0)
        {
            Joint^ joint = Joints::Find(string);
            UpdatePrimaryJoint(joint);

            if (joint != nullptr)
                DisplayName = "<"+joint->Name+">";
            else
                DisplayName = Name;
        }
    }

    bool LoadOperator::IsProcessable()
    {
        return primaryJoint->Sender != nullptr && primaryJoint->Sender->IsProcessable();
    }

    bool LoadOperator::IsWarningPresent()
    {
        return false;
    }

    Core::Operator* LoadOperator::getOperator()
    {
        if (primaryJoint->Sender != nullptr)
            return primaryJoint->Sender->getOperator();
        return 0;
    }

    Joint^ LoadOperator::GetPrimaryJoint()
    {
        return primaryJoint;
    }

    void LoadOperator::JointReceiverConnected(Joint^ joint, Operator^ op)
    {
       
    }

    void LoadOperator::JointReceiverDisconnected(Joint^ joint, Operator^ op)
    {
        if (joint == primaryJoint)
            receivers->Remove(op);
    }

    void LoadOperator::JointSenderConnected(Joint^ joint, Operator^ op)
    {     
    
    }

    void LoadOperator::JointSenderDisconnected(Joint^ joint, Operator^ op)
    {  
      
    }

    void LoadOperator::DisconnectFromAllJoints()
    {
        List<Operator^>^ receiversCopy = gcnew List<Operator^>(receivers);
        for (int i = 0; i < receiversCopy->Count; i++)
            primaryJoint->DisconnectReceiver(receiversCopy[i]);
    }

    void LoadOperator::ConnectWithJointAsReceiver(Joint^ joint)
    {
      
    }

    void LoadOperator::ConnectWithJointAsSender(Joint^ joint)
    {
      
    }

    void LoadOperator::AddReceiver(Operator^ op)
    {
        receivers->Add(op);
    }

    void LoadOperator::UpdatePrimaryJoint(Joint^ primary)
    {
        if (primary == nullptr)
            primary = loadJoint;
            
        if (primaryJoint != nullptr 
            && primary != primaryJoint)
        {
           primaryJoint->RemoveSenderListener(this);

           for (int i = 0; i < receivers->Count; i++)
           {
                primaryJoint->DisconnectReceiver(receivers[i]); 
                receivers[i]->ConnectWithJointAsReceiver(primary);
           }

           primary->AddSenderListener(this);
        }

        primaryJoint = primary;
    }
}