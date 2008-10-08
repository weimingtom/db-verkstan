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

	public ref class OperatorBinding
	{
    public:
        OperatorBinding(String^ name,
                        int operatorId,
                        Constants::OperatorTypes type,
                        List<OperatorBindingProperty^>^ properties,
                        List<Constants::OperatorTypes>^ inConnectionTypes);
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
        property List<int>^ InConnectionIds 
        { 
           List<int>^ get(); 
        }
        property List<int>^ OutConnectionIds 
        { 
           List<int>^ get(); 
        }
        property List<Constants::OperatorTypes>^ InConnectionTypes 
        { 
            List<Constants::OperatorTypes>^ get(); 
        }
        
        void ConnectInWith(OperatorBinding^ operatorBinding);
        void ConnectOutWith(OperatorBinding^ operatorBinding);
        void DisconnectOutFrom(OperatorBinding^ operatorBinding);
        bool IsProcessable();

    private:
        List<OperatorBindingProperty^>^ properties;
        List<Constants::OperatorTypes>^ inConnectionTypes;
        int id;
        Constants::OperatorTypes type;
        String^ name;
	};
}