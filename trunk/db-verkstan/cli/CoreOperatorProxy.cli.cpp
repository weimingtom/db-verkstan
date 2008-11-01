#include "cli/CoreOperatorProxy.hpp"


namespace Verkstan
{
    CoreOperatorProxy::CoreOperatorProxy(Operator^ coreOperator)
        : Operator(coreOperator->Name,
                   coreOperator->TypeName,
                   coreOperator->Id,
                   coreOperator->Type)
    {
        this->coreOperator = coreOperator;
    }

    CoreOperatorProxy::~CoreOperatorProxy()
    {

    }

    unsigned char CoreOperatorProxy::GetByteProperty(int index)
    {
        return coreOperator->GetByteProperty(index);
    }

    void CoreOperatorProxy::SetByteProperty(int index, unsigned char value)
    {
        coreOperator->SetByteProperty(index, value);
    }

    int CoreOperatorProxy::GetIntProperty(int index)
    {
         return coreOperator->GetIntProperty(index);
    }

    void CoreOperatorProxy::SetIntProperty(int index, int value)
    {
        coreOperator->SetIntProperty(index, value);
    }

    float CoreOperatorProxy::GetFloatProperty(int index) 
    {
        return coreOperator->GetFloatProperty(index);
    }

    void CoreOperatorProxy::SetFloatProperty(int index, float value)
    {
        coreOperator->SetFloatProperty(index, value);
    }

    String^ CoreOperatorProxy::GetStringProperty(int index)
    {
        return coreOperator->GetStringProperty(index);
    }

    void CoreOperatorProxy::SetStringProperty(int index, String ^value)
    {
        coreOperator->SetStringProperty(index, value);
    }

    Vector^ CoreOperatorProxy::GetVectorProperty(int index)
    {
        return coreOperator->GetVectorProperty(index);
    }

    void CoreOperatorProxy::SetVectorProperty(int index, Vector^ vector)
    {
        coreOperator->SetVectorProperty(index, vector);
    }

    Color^ CoreOperatorProxy::GetColorProperty(int index)
    {
        return coreOperator->GetColorProperty(index);
    }

    void CoreOperatorProxy::SetColorProperty(int index, Color^ color)
    {
        coreOperator->SetColorProperty(index, color);
    }

    bool CoreOperatorProxy::IsProcessable()
    {
        return coreOperator->IsProcessable();
    }

    bool CoreOperatorProxy::IsWarningPresent()
    {
        return coreOperator->IsWarningPresent();
    }

    Joint^ CoreOperatorProxy::GetPrimaryJoint()
    {
        return coreOperator->GetPrimaryJoint();
    }

    void CoreOperatorProxy::ConnectWithJointAsReceiver(Joint^ joint)
    {
        return coreOperator->ConnectWithJointAsReceiver(joint);
    }

    void CoreOperatorProxy::ConnectWithJointAsSender(Joint^ joint)
    {
        return coreOperator->ConnectWithJointAsSender(joint);
    }

    void CoreOperatorProxy::DisconnectFromAllJoints()
    {
        coreOperator->DisconnectFromAllJoints();
    }

    void CoreOperatorProxy::JointSenderConnected(Joint^ joint, Operator^ op)
    {   
        coreOperator->JointSenderConnected(joint, op);
    }

    void CoreOperatorProxy::JointSenderDisconnected(Joint^ joint, Operator^ op)
    {
        coreOperator->JointSenderDisconnected(joint, op);
    }

    void CoreOperatorProxy::JointReceiverConnected(Joint^ joint, Operator^ op)
    {
        coreOperator->JointReceiverConnected(joint, op);
    }

    void CoreOperatorProxy::JointReceiverDisconnected(Joint^ joint, Operator^ op)
    {
        coreOperator->JointReceiverDisconnected(joint, op);
    }

    Core::Operator* CoreOperatorProxy::getOperator()
    {
        return coreOperator->getOperator();
    }
}