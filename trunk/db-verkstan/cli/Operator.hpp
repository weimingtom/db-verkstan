#pragma once

#include "cli/Core.hpp"
#include "cli/Constants.hpp"

#using <mscorlib.dll>

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref struct Color;
    ref struct Vector;
    ref class OperatorProperty;
    ref class OperatorInput;

	public ref class CoreOperator 
	{
    public:
        property Constants::OperatorTypes Type { Constants::OperatorTypes get(); }
        property String^ Name { String^ get(); }
        property int Id { int get(); }
        property List<OperatorProperty^>^ Properties { List<OperatorProperty^>^ get(); }
        property List<OperatorInput^>^ Inputs { List<OperatorInput^>^ get(); }

        CoreOperator(String^ name,
                     int operatorId,
                     Constants::OperatorTypes type);
        virtual ~CoreOperator();

        unsigned char GetByteProperty(int index);
        void SetByteProperty(int index, unsigned char value);
        int GetIntProperty(int index);
        void SetIntProperty(int index, int value);
        float GetFloatProperty(int index);
        void SetFloatProperty(int index, float value);
        String^ GetStringProperty(int index);
        void SetStringProperty(int index, String^ value);
        Vector^ GetVectorProperty(int index);
        void SetVectorProperty(int index, Vector^ vector);
        Color^ GetColorProperty(int index);
        void SetColorProperty(int index, Color^ color);
        int GetPropertyChannel(int index, int valueIndex);
        void SetPropertyChannel(int index, int valueIndex, int channel);
        float GetPropertyAmplify(int index,  int valueIndex);
        void SetPropertyAmplify(int index, int valueIndex, float amplify);
        
        Core::Operator* getOperator();

        void AddProperty(String^ name, Constants::OperatorPropertyTypes type);
        void AddEnumProperty(String^ name, List<String^>^ values);
        void AddInput(Constants::OperatorTypes type, bool infinite, bool optional);

        int GetNumberOfRequiredInputs();
        void ClearInputConnections();
        void ClearOutputConnections();
        int GetInputConnectionId(int index);
        int GetOutputConnectionId(int index);
        void SetInputConnectionId(int index, int id);
        void SetOutputConnectionId(int index, int id);
        int GetMaxInputConnections();
        int GetMaxOutputConnections();
        int GetNumberOfInputConnections();
        int GetNumberOfOutputConnections();
        void SetNumberOfInputConnections(int number);
        void SetNumberOfOutputConnections(int number);
        void SetDirty(bool dirty);
        bool IsDirty();

    private:
        String^ name;
        int id;
        Constants::OperatorTypes type;
        List<OperatorProperty^>^ properties;
        List<OperatorInput^>^ inputs;
	};
}