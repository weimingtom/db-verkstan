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

	public ref class OperatorBinding abstract 
	{
    public:
        OperatorBinding(String^ name,
                        int operatorId,
                        Constants::OperatorTypes type,
                        List<OperatorBindingProperty^>^ properties);
        virtual ~OperatorBinding();
        
        virtual unsigned char GetByteProperty(int index) = 0;
        virtual void SetByteProperty(int index, unsigned char byteValue) = 0;
        virtual int GetIntProperty(int index) = 0;
        virtual void SetIntProperty(int index, int intValue) = 0;
        virtual float GetFloatProperty(int index) = 0;
        virtual void SetFloatProperty(int index, float floatValue) = 0;
        virtual String^ GetStringProperty(int index) = 0;
        virtual void SetStringProperty(int index, String ^string) = 0;
        
        property Constants::OperatorTypes Type { Constants::OperatorTypes get(); }
        property int Id { int get(); }
        property String^ Name { String^ get(); }
        property List<OperatorBindingProperty^>^ Properties 
        { 
            List<OperatorBindingProperty^>^ get(); 
        }
        
        virtual void CascadeProcess() = 0;
        virtual void Process() = 0;
        virtual bool IsProcessable() = 0;

        virtual void ConnectInWith(OperatorBinding^ operatorBinding) = 0;
        virtual void ConnectOutWith(OperatorBinding^ operatorBinding) = 0;
        virtual void Disconnect() = 0;
        
        virtual void DisconnectInFrom(OperatorBinding^ operatorBinding) = 0;
        virtual void DisconnectOutFrom(OperatorBinding^ operatorBinding) = 0;      

        virtual void SetDirty(bool dirty) = 0;
        virtual bool IsDirty() = 0;

    private:
        int id;
        Constants::OperatorTypes type;
        String^ name;
        List<OperatorBindingProperty^>^ properties;
	};
}