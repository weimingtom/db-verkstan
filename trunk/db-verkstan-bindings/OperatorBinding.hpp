#pragma once

#include "operator.hpp"

#include "Constants.hpp"

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace VerkstanBindings 
{
    public ref class OperatorBindingProperty
    {
    public:
        OperatorBindingProperty(int index, 
                                String^ name, 
                                Constants::OperatorPropertyTypes type);
        property String^ Name;
        property Constants::OperatorPropertyTypes Type;
        property int Index;
    };

    public ref class OperatorBindingInput
    {
    public:
        OperatorBindingInput(int index,
                             Constants::OperatorTypes type,
                             bool infinite);
        property bool Infinite;
        property Constants::OperatorTypes Type;
        property int Index;
    };

	public ref class OperatorBinding
	{
    public:
        OperatorBinding(String^ name,
                        int operatorId,
                        Constants::OperatorTypes type,
                        List<OperatorBindingProperty^>^ properties,
                        List<OperatorBindingInput^>^ inputs);
        ~OperatorBinding();
        
        unsigned char GetByteProperty(int index);
        void SetByteProperty(int index, unsigned char byteValue);
        int GetIntProperty(int index);
        void SetIntProperty(int index, int intValue);
        float GetFloatProperty(int index);
        void SetFloatProperty(int index, float floatValue);
        String^ GetStringProperty(int index);
        void SetStringProperty(int index, String ^string);
        
        property Constants::OperatorTypes Type { Constants::OperatorTypes get(); }
        property int Id { int get(); }
        property String^ Name { String^ get(); }
        property List<OperatorBindingProperty^>^ Properties 
        { 
            List<OperatorBindingProperty^>^ get(); 
        }
        
        void ConnectInWith(OperatorBinding^ operatorBinding);
        void ConnectOutWith(OperatorBinding^ operatorBinding);
        void Disconnect();
        bool IsProcessable();

    protected:
        void DisconnectInFrom(OperatorBinding^ operatorBinding);
        void DisconnectOutFrom(OperatorBinding^ operatorBinding);

    private:
        void flushInputConnections();
        void flushOutputConnections();

        List<OperatorBindingProperty^>^ properties;
        List<OperatorBindingInput^>^ inputs;
        List<OperatorBinding^>^ inputConnections;
        List<OperatorBinding^>^ outputConnections;
        int id;
        Constants::OperatorTypes type;
        String^ name;
	};
}