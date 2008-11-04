#pragma once

#include "cli/Operator.hpp"

namespace Verkstan
{
    ref class Joint;

    public ref class StoreOperator: public Operator
	{
    public:
        StoreOperator();
        virtual ~StoreOperator();

        property String^ Name
        {
            virtual void set(String^ name) override;
        }

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