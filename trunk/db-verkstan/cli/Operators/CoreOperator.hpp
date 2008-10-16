#pragma once

#include "cli/Operator.hpp"
#include "cli/Joint.hpp"

namespace Verkstan
{
    public ref class CoreOperator: public Operator
	{
    public:
        CoreOperator(String^ name,
                            int operatorId,
                            Constants::OperatorTypes type,
                            List<OperatorProperty^>^ properties,
                            List<OperatorInput^>^ inputs);
        virtual ~CoreOperator();

        virtual unsigned char GetByteProperty(int index) override;
        virtual void SetByteProperty(int index, unsigned char value) override;
        virtual int GetIntProperty(int index) override;
        virtual void SetIntProperty(int index, int value) override;
        virtual float GetFloatProperty(int index) override;
        virtual void SetFloatProperty(int index, float value) override;
        virtual String^ GetStringProperty(int index) override;
        virtual void SetStringProperty(int index, String ^value) override;
        
        virtual bool IsProcessable() override;

        virtual Joint^ GetPrimaryJoint() override;
        virtual void ConnectWithJointAsReceiver(Joint^ joint) override;
        virtual void ConnectWithJointAsSender(Joint^ joint) override;
        virtual void DisconnectFromAllJoints() override;
        virtual void DisconnectFromJointAsReceiver(Joint^ joint) override;
        virtual void DisconnectFromJointAsSender(Joint^ joint) override;
        virtual void JointSenderChanged(Operator^ op) override;
        virtual void JointReceiverAdded(Operator^ op) override;
        virtual void JointReceiverRemoved(Operator^ op) override;

        /*
        virtual void ConnectInWith(Operator^ op) override;
        virtual void ConnectOutWith(Operator^ op) override;
        virtual void Disconnect() override;
        virtual void DisconnectInFrom(Operator^ op) override;
        virtual void DisconnectOutFrom(Operator^ op) override;
        virtual void UpdateRealInputConnections() override;
        virtual void UpdateRealOutputConnections() override;
        virtual void UpdateRealConnections() override;
        */

        virtual Core::Operator* getOperator() override;

    private:
        void UpdateInputConnections();
        void UpdateOutputConnections();
        Joint^ primaryJoint;
        List<Joint^>^ inputJoints;
        List<Joint^>^ outputJoints;
        List<OperatorInput^>^ inputs;
        bool processable;
	};
}