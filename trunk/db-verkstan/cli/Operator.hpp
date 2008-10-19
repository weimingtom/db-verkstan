#pragma once

#include "cli/VerkstanCore.hpp"

#include "cli/Constants.hpp"
#include "cli/Joint.hpp"
#include "cli/OperatorProperties.hpp"

namespace Verkstan 
{
    public ref class OperatorInput
    {
    public:
        OperatorInput(int index,
                             Constants::OperatorTypes type,
                             bool infinite,
                             bool optional);
        property bool Infinite;
        property bool Optional;
        property Constants::OperatorTypes Type;
        property int Index;
    };

	public ref class Operator abstract 
	{
    public:
        Operator(String^ name,
                        int operatorId,
                        Constants::OperatorTypes type,
                        Constants::OperatorTypes internalType,
                        OperatorProperties^ properties);
        virtual ~Operator();

        String^ DisplayName;
        property Constants::OperatorTypes Type { Constants::OperatorTypes get(); }
        property Constants::OperatorTypes InternalType { Constants::OperatorTypes get(); }
        property int Id { int get(); }
        property String^ Name { String^ get(); }
        property OperatorProperties^ Properties 
        { 
            OperatorProperties^ get(); 
        }

        virtual Joint^ GetPrimaryJoint() = 0;
        virtual void ConnectWithJointAsReceiver(Joint^ joint) = 0;
        virtual void ConnectWithJointAsSender(Joint^ joint) = 0;
        virtual void DisconnectFromAllJoints() = 0;
        
        virtual void JointSenderConnected(Joint^ joint, Operator^ op) = 0;  
        virtual void JointSenderDisconnected(Joint^ joint, Operator^ op) = 0;  
        virtual void JointReceiverConnected(Joint^ joint, Operator^ op) = 0;
        virtual void JointReceiverDisconnected(Joint^ joint, Operator^ op) = 0;

        virtual unsigned char GetByteProperty(int index) = 0;
        virtual void SetByteProperty(int index, unsigned char value) = 0;
        virtual int GetIntProperty(int index) = 0;
        virtual void SetIntProperty(int index, int value) = 0;
        virtual float GetFloatProperty(int index) = 0;
        virtual void SetFloatProperty(int index, float value) = 0;
        virtual String^ GetStringProperty(int index) = 0;
        virtual void SetStringProperty(int index, String^ value) = 0;
        
        virtual bool IsProcessable() = 0;
        virtual bool IsWarningPresent() = 0;

        virtual Core::Operator* getOperator() = 0;

    protected:
        int id;
        Constants::OperatorTypes type;

    private:
        Constants::OperatorTypes internalType;
        String^ name;
        OperatorProperties^ properties;
	};
}