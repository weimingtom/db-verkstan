#pragma once

#include "cli/Operator.hpp"

namespace Verkstan
{
    ref class Joint;

    public ref class CoreOperator: public Operator
	{
    public:
        CoreOperator(String^ name,
                     String^ typeName,
                     int operatorId,
                     Constants::OperatorTypes type,
                     OperatorProperties^ properties,
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
        virtual Vector^ GetVectorProperty(int index)override;
        virtual void SetVectorProperty(int index, Vector^ vector) override;
        virtual Color^ GetColorProperty(int index) override;
        virtual void SetColorProperty(int index, Color^ color) override;

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
        void UpdateInputConnections();
        void UpdateOutputConnections();

        Joint^ primaryJoint;
        List<Joint^>^ inputJoints;
        List<Joint^>^ outputJoints;
        List<OperatorInput^>^ inputs;
        bool processable;
        bool warningPresent;
	};
}