#pragma once

#include "BuilderLib.hpp"
#include "Constants.hpp"

#using <mscorlib.dll>

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref struct Color;
    ref struct Vector;
    ref class OperatorBindingProperty;
    ref class OperatorBindingInput;
    ref class OperatorRenderer;
    
	public ref class OperatorBinding 
	{
    public:
        property Constants::OperatorTypes Type { Constants::OperatorTypes get(); }
        property String^ Name { String^ get(); }
        property unsigned short Id { unsigned short get(); }
        property unsigned char FilterType { unsigned char get(); }
        property short NumberOfConstantInputs { short get(); }
        property List<OperatorBindingProperty^>^ Properties { List<OperatorBindingProperty^>^ get(); }
        property List<OperatorBindingInput^>^ Inputs { List<OperatorBindingInput^>^ get(); }
        property OperatorRenderer^ Renderer { OperatorRenderer^ get(); }

        OperatorBinding(unsigned char filterType, 
                        String^ name,
                        unsigned short operatorId,
                        Constants::OperatorTypes type,
                        OperatorRenderer^ renderer);
        virtual ~OperatorBinding();

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
        
        InternalOperator* getOperator();

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
        unsigned char filterType;
        String^ name;
        unsigned short id;
        //short numberOfConstantInputs;
        Constants::OperatorTypes type;
        List<OperatorBindingProperty^>^ properties;
        List<OperatorBindingInput^>^ inputs;
        OperatorRenderer^ renderer;
	};
}