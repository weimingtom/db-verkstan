#pragma once

#include "cli/internal/VerkstanCore.hpp"

#include "cli/Color.hpp"
#include "cli/Constants.hpp"
#include "cli/internal/Joint.hpp"
#include "cli/Vector.hpp"

#using <mscorlib.dll>

namespace Verkstan 
{
    ref class OperatorProperty;

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
        Operator(String^ typeName,
                 int operatorId,
                 Constants::OperatorTypes type);
        virtual ~Operator();

        property String^ Name
        {
            String^ get();
            virtual void set(String^ name);
        }

        property String^ DisplayName
        {
            String^ get();
        }

        property Constants::OperatorTypes Type { Constants::OperatorTypes get(); }
        property int Id { int get(); }
        property String^ TypeName { String^ get(); }
        property List<OperatorProperty^>^ Properties 
        { 
            List<OperatorProperty^>^ get(); 
        }

        virtual Joint^ GetPrimaryJoint() = 0;
        virtual void ConnectWithJointAsReceiver(Joint^ joint) = 0;
        virtual void ConnectWithJointAsSender(Joint^ joint) = 0;
        virtual void DisconnectFromAllJoints() = 0;
        
        virtual void JointSenderConnected(Joint^ joint, Operator^ op) = 0;  
        virtual void JointSenderDisconnected(Joint^ joint, Operator^ op) = 0;  
        virtual void JointReceiverConnected(Joint^ joint, Operator^ op) = 0;
        virtual void JointReceiverDisconnected(Joint^ joint, Operator^ op) = 0;

        virtual unsigned char GetByteProperty(int index);
        virtual void SetByteProperty(int index, unsigned char value);
        virtual int GetIntProperty(int index);
        virtual void SetIntProperty(int index, int value);
        virtual float GetFloatProperty(int index);
        virtual void SetFloatProperty(int index, float value);
        virtual String^ GetStringProperty(int index);
        virtual void SetStringProperty(int index, String^ value);
        virtual Vector^ GetVectorProperty(int index);
        virtual void SetVectorProperty(int index, Vector^ vector);
        virtual Color^ GetColorProperty(int index);
        virtual void SetColorProperty(int index, Color^ color);

        virtual bool IsProcessable() = 0;
        virtual bool IsWarningPresent() = 0;

        virtual Core::Operator* getOperator() = 0;

        void AddProperty(String^ name, Constants::OperatorPropertyTypes type);
        void AddEnumProperty(String^ name, List<String^>^ values);

    protected:
        int id;
        Constants::OperatorTypes type;
        String^ displayName;

    private:
        String^ name;
        String^ typeName;
        List<OperatorProperty^>^ properties;
	};
}