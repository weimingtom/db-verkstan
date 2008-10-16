#include <stdio.h> 
#include <stdlib.h>
#include <vcclr.h>

#include "cli/Operators/CoreOperator.hpp"
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
        this->processable = inputs->Count == 0;
        this->inputs = inputs;

        inputJoints = gcnew List<Joint^>();
        outputJoints = gcnew List<Joint^>();
        primaryJoint = gcnew Joint();
        primaryJoint->Sender = this;
        Joints::Add(primaryJoint);
        outputJoints->Add(primaryJoint);
    }

    CoreOperator::~CoreOperator()
    {
        Joints::Remove(primaryJoint);
        /*
        Disconnect();
        */
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

    Core::Operator* CoreOperator::getOperator()
    {
        return Core::operators[Id];
    }

    Joint^ CoreOperator::GetPrimaryJoint()
    {
        return primaryJoint;
    }

    void CoreOperator::DisconnectFromJointAsReceiver(Joint^ joint)
    {
        inputJoints->Remove(joint);
        joint->RemoveReceiver(this);
    }

    void CoreOperator::DisconnectFromJointAsSender(Joint^ joint)
    {
        outputJoints->Remove(joint);
        joint->Sender = nullptr;
    }

    void CoreOperator::JointReceiverAdded(Operator^ op)
    {
        UpdateOutputConnections();
        op->getOperator()->setDirty(true);
    }

    void CoreOperator::JointReceiverRemoved(Operator^ op)
    {
        UpdateOutputConnections();
    }

    void CoreOperator::JointSenderChanged(Operator^ op)
    {     
        UpdateInputConnections();
    }

    void CoreOperator::DisconnectFromAllJoints()
    {
        for (int i = 0; i < inputJoints->Count; i++)
        {
            Joint^ joint = inputJoints[i];
            joint->RemoveReceiver(this);
        }

        inputJoints->Clear();

        for (int i = 0; i < outputJoints->Count; i++)
        {
            Joint^ joint = outputJoints[i];

            if (joint == primaryJoint)
                continue;

            joint->Sender = nullptr;
        }

        outputJoints->Clear();
        outputJoints->Add(primaryJoint);

        // As this operator owns the primary joint it's this operator's
        // responsibility to tell all receivers of the primary joint to
        // disconnect.
        for (int i = 0; i < primaryJoint->Receivers->Count; i++)
        {
            Operator^ op = primaryJoint->Receivers[i];
            op->DisconnectFromJointAsReceiver(primaryJoint);
        }

        UpdateInputConnections();
        UpdateOutputConnections();
    }

    void CoreOperator::ConnectWithJointAsReceiver(Joint^ joint)
    {
        inputJoints->Add(joint);    
        joint->AddReceiver(this);
    }

    void CoreOperator::ConnectWithJointAsSender(Joint^ joint)
    {
        outputJoints->Add(joint);
        joint->Sender = this;
    }

    void CoreOperator::UpdateInputConnections()
    {
        for (int i = 0; i < getOperator()->numberOfInputs; i++)
            getOperator()->inputs[i] = -1;

        List<Operator^>^ inputOperators = gcnew List<Operator^>();
        for (int i = 0; i < inputJoints->Count; i++)
            inputOperators->Add(inputJoints[i]->Sender);
            
        int numberOfInputs = 0;

        for (int i = 0; i < inputOperators->Count; i++)
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
        }

        getOperator()->numberOfInputs = numberOfInputs;
        processable = inputs->Count == numberOfInputs;
    }

    void CoreOperator::UpdateOutputConnections()
    {
        System::Console::WriteLine("Updating outputs");
        for (int i = 0; i < getOperator()->numberOfOutputs; i++)
            getOperator()->outputs[i] = -1;

        System::Console::WriteLine("output joints =  " + outputJoints->Count);


        List<Operator^>^ outputOperators = gcnew List<Operator^>();
        for (int i = 0; i < outputJoints->Count; i++)
            for (int j = 0; j < outputJoints[i]->Receivers->Count; j++)
                outputOperators->Add(outputJoints[i]->Receivers[j]);

        System::Console::WriteLine("outputs =  " + outputOperators->Count);

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