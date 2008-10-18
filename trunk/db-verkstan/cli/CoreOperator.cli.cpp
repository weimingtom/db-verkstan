#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/CoreOperator.hpp"
#include "cli/Joint.hpp"
#include "cli/Joints.hpp"

namespace Verkstan
{
    CoreOperator::CoreOperator(String^ name,
                                 int operatorId,
                                 Constants::OperatorTypes type,
                                 List<OperatorProperty^>^ properties,
                                 List<OperatorInput^>^ inputs)
                             : Operator(name, 
                                        operatorId, 
                                        type, 
                                        Constants::OperatorTypes::Core,
                                        properties)
    {
        this->warningPresent = false;
        this->inputs = inputs;

        inputJoints = gcnew List<Joint^>();
        outputJoints = gcnew List<Joint^>();
        primaryJoint = gcnew Joint();
        primaryJoint->ConnectSender(this);
        Joints::Add(primaryJoint);
        outputJoints->Add(primaryJoint);
    }

    CoreOperator::~CoreOperator()
    {
        Joints::Remove(primaryJoint);
        delete Core::operators[Id];
        Core::operators[Id] = 0;
    }

    unsigned char CoreOperator::GetByteProperty(int index)
    {
        return getOperator()->getByteProperty(index);
    }

    void CoreOperator::SetByteProperty(int index, unsigned char value)
    {
        getOperator()->setByteProperty(index, value); 
        getOperator()->setDirty(true);
    }

    int CoreOperator::GetIntProperty(int index)
    {
         return getOperator()->getIntProperty(index);
    }

    void CoreOperator::SetIntProperty(int index, int value)
    {
        getOperator()->setIntProperty(index, value); 
        getOperator()->setDirty(true);
    }

    float CoreOperator::GetFloatProperty(int index)
    {
        return getOperator()->getFloatProperty(index);
    }

    void CoreOperator::SetFloatProperty(int index, float value)
    {
        getOperator()->setFloatProperty(index, value); 
        getOperator()->setDirty(true);
    }

    String^ CoreOperator::GetStringProperty(int index)
    {   
        return gcnew String(getOperator()->getStringProperty(index));   
    }

    void CoreOperator::SetStringProperty(int index, String^ string)
    {
        // Pin memory so GC can't move it while native function is called
        pin_ptr<const wchar_t> wch = PtrToStringChars(string);
     
        // Conversion to char* :
        // Can just convert wchar_t* to char* using one of the 
        // conversion functions such as: 
        // WideCharToMultiByte()
        // wcstombs_s()
        // ... etc
        size_t convertedChars = 0;
        size_t sizeInBytes = ((string->Length + 1) * 2);
        errno_t err = 0;
        char *ch = (char*)malloc(sizeInBytes);

        err = wcstombs_s(&convertedChars, 
                         ch, 
                         sizeInBytes,
                         wch, 
                         sizeInBytes);

        getOperator()->setStringProperty(index, ch);
        getOperator()->setDirty(true);
    }

    bool CoreOperator::IsProcessable()
    {
        bool result = processable;

        for (int i = 0; i < inputJoints->Count; i++)
        {
            Operator^ op = inputJoints[i]->Sender;
            if (op != nullptr)
                result &= op->IsProcessable();
        }

        return result;
    }

    bool CoreOperator::IsWarningPresent()
    {
        return warningPresent;
    }

    Core::Operator* CoreOperator::getOperator()
    {
        return Core::operators[Id];
    }

    Joint^ CoreOperator::GetPrimaryJoint()
    {
        return primaryJoint;
    }

    void CoreOperator::JointReceiverConnected(Joint^ joint, Operator^ op)
    {
        if (op == this && joint != primaryJoint && !outputJoints->Contains(joint))
            outputJoints->Add(joint);

        UpdateOutputConnections();
        op->getOperator()->setDirty(true);
    }

    void CoreOperator::JointReceiverDisconnected(Joint^ joint, Operator^ op)
    {
        if (op == this && joint != primaryJoint && outputJoints->Contains(joint))
            outputJoints->Remove(joint);

        UpdateOutputConnections();
    }

    void CoreOperator::JointSenderConnected(Joint^ joint, Operator^ op)
    {     
        if (!inputJoints->Contains(joint))
            inputJoints->Add(joint);

        UpdateInputConnections();
        getOperator()->setDirty(true);
    }

    void CoreOperator::JointSenderDisconnected(Joint^ joint, Operator^ op)
    {  
        if (inputJoints->Contains(joint))
            inputJoints->Remove(joint);

        UpdateInputConnections();
        getOperator()->setDirty(true);
    }

    void CoreOperator::DisconnectFromAllJoints()
    {
        List<Joint^>^ inputJointsCopy = gcnew List<Joint^>(inputJoints);
        for (int i = 0; i < inputJointsCopy->Count; i++)
        {
            Joint^ joint = inputJointsCopy[i];
            joint->DisconnectReceiver(this);
        }

        List<Joint^>^ outputJointsCopy = gcnew List<Joint^>(outputJoints);
        for (int i = 0; i < outputJointsCopy->Count; i++)
        {
            Joint^ joint = outputJointsCopy[i];

            if (joint == primaryJoint)
                continue;

            joint->DisconnectSender(this);
        }

        // As this operator owns the primary joint it's this operator's
        // responsibility to disconnect all receivers of the primary joint.
        primaryJoint->DisconnectAllReceivers();

        UpdateInputConnections();
        UpdateOutputConnections();
    }

    void CoreOperator::ConnectWithJointAsReceiver(Joint^ joint)
    {
        inputJoints->Add(joint);    
        joint->ConnectReceiver(this);
    }

    void CoreOperator::ConnectWithJointAsSender(Joint^ joint)
    {
        outputJoints->Add(joint);
        joint->ConnectSender(this);
    }

    void CoreOperator::UpdateInputConnections()
    {
        for (int i = 0; i < getOperator()->numberOfInputs; i++)
            getOperator()->inputs[i] = -1;

        List<Operator^>^ inputOperators = gcnew List<Operator^>();
        for (int i = 0; i < inputJoints->Count; i++)
            if (inputJoints[i]->Sender != nullptr)
                inputOperators->Add(inputJoints[i]->Sender);
            
        int numberOfInputs = 0;

        warningPresent = false;
        for (int i = 0; i < inputOperators->Count && inputs->Count > 0; i++)
        {
            Operator^ op = inputOperators[i];
     
            if (op->Id == -1 || op->Id == Id)
                continue;

            bool accepted = false;
            int j = 0;
            for (j; j < inputs->Count; j++)
            {
                if (inputs[j]->Type == op->Type
                    && getOperator()->inputs[j] == -1)
                {
                    getOperator()->inputs[j] = op->Id;
                    accepted = true;
                    numberOfInputs++;
                    break;
                }
            }

			j--;
			
            if (!accepted 
                && inputs[j]->Infinite
                && inputs[j]->Type == op->Type)
            {
                for (j; j < DB_MAX_OPERATOR_CONNECTIONS; j++)
                {
                    if (getOperator()->inputs[j] == -1)
                    {
                        getOperator()->inputs[j] = op->Id;
                        accepted = true;
                        numberOfInputs++;
                        break;
                    }
                }
            }

            if (!accepted)
                warningPresent = true; 
        }

        getOperator()->numberOfInputs = numberOfInputs;

        int requiredInputs = 0;
        for (int i = 0; i < inputs->Count; i++)
            if (!inputs[i]->Optional)
                requiredInputs++;  
        processable = requiredInputs <= numberOfInputs;
    }

    void CoreOperator::UpdateOutputConnections()
    {
        for (int i = 0; i < getOperator()->numberOfOutputs; i++)
            getOperator()->outputs[i] = -1;

        List<Operator^>^ outputOperators = gcnew List<Operator^>();
        for (int i = 0; i < outputJoints->Count; i++)
            for (int j = 0; j < outputJoints[i]->Receivers->Count; j++)
                outputOperators->Add(outputJoints[i]->Receivers[j]);

        int numberOfOutputs= 0;
        for (int i = 0; i < outputOperators->Count; i++)
        {
            Operator^ op = outputOperators[i];

            if (op->Id == -1)
                continue;

            for (int j = 0; j < DB_MAX_OPERATOR_CONNECTIONS; j++)
            {
                if (getOperator()->outputs[j] == -1)
                {
                    getOperator()->outputs[j] = op->Id;
                    numberOfOutputs++;
                    break;
                }
            }
        }

        getOperator()->numberOfOutputs = numberOfOutputs;
    }
}