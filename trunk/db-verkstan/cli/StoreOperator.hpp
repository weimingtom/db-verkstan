#pragma once

#include "cli/Operator.hpp"

namespace Verkstan
{
    ref class Joint;

    public ref class StoreOperator: public Operator
	{
    public:
        StoreOperator(List<OperatorProperty^>^ properties);
        virtual ~StoreOperator();

        virtual unsigned char GetByteProperty(int index) override;
        virtual void SetByteProperty(int index, unsigned char value) override;
        virtual int GetIntProperty(int index) override;
        virtual void SetIntProperty(int index, int value) override;
        virtual float GetFloatProperty(int index) override;
        virtual void SetFloatProperty(int index, float value) override;
        virtual String^ GetStringProperty(int index) override;
        virtual void SetStringProperty(int index, String ^value) override;
        
        virtual bool IsProcessable() override;
        virtual bool IsWarningPresent() override;

        virtual Joint^ GetPrimaryJoint() override;
        virtual void ConnectWithJointAsReceiver(Joint^ joint) override;
        virtual void ConnectWithJointAsSender(Joint^ joint) override;
        virtual void DisconnectFromAllJoints() override;
      
        virtual void JointSenderConnected(Joint^ joint, Operator^ op) override;
        virtual void JointSenderDisconnected(Joint^ joint, Operator^ op) override;
        virtual void JointReceiverConnected(Joint^ joint, Operator^ op) override;
        virtual void JointReceiverDisconnected(Joint^ joint, Operator^ op) override;

        virtual Core::Operator* getOperator() override;

    private:
        Joint^ primaryJoint;
	};
}