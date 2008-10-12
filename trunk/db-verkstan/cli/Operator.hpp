#pragma once

#include "cli/Internal/VerkstanCore.hpp"

#include "cli/Constants.hpp"

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace Verkstan 
{
    public ref class OperatorProperty
    {
    public:
        OperatorProperty(int index, 
                                String^ name, 
                                Constants::OperatorPropertyTypes type);
        property String^ Name;
        property Constants::OperatorPropertyTypes Type;
        property int Index;
    };

    public ref class OperatorInput
    {
    public:
        OperatorInput(int index,
                             Constants::OperatorTypes type,
                             bool infinite);
        property bool Infinite;
        property Constants::OperatorTypes Type;
        property int Index;
    };

	public ref class Operator abstract 
	{
    public:
        Operator(String^ name,
                        int operatorId,
                        Constants::OperatorTypes type,
                        List<OperatorProperty^>^ properties);
        virtual ~Operator();
        
        String^ DisplayName;
        property Constants::OperatorTypes Type { Constants::OperatorTypes get(); }
        property int Id { int get(); }
        property String^ Name { String^ get(); }
        property List<OperatorProperty^>^ Properties 
        { 
            List<OperatorProperty^>^ get(); 
        }

        virtual unsigned char GetByteProperty(int index) = 0;
        virtual void SetByteProperty(int index, unsigned char value) = 0;
        virtual int GetIntProperty(int index) = 0;
        virtual void SetIntProperty(int index, int value) = 0;
        virtual float GetFloatProperty(int index) = 0;
        virtual void SetFloatProperty(int index, float value) = 0;
        virtual String^ GetStringProperty(int index) = 0;
        virtual void SetStringProperty(int index, String^ value) = 0;
     
        int GetColorProperty(int index);
        void SetColorProperty(int index, int value);
        String^ GetTextProperty(int index);
        void SetTextProperty(int index, String^ value);
        
        virtual void CascadeProcess() = 0;
        virtual void Process() = 0;
        virtual bool IsProcessable() = 0;

        virtual void ConnectInWith(Operator^ op) = 0;
        virtual void ConnectOutWith(Operator^ op) = 0;
        virtual void Disconnect() = 0;
        virtual void DisconnectInFrom(Operator^ op) = 0;
        virtual void DisconnectOutFrom(Operator^ op) = 0; 
        virtual void DisconnectIns() = 0;

        virtual void SetDirty(bool dirty) = 0;
        virtual bool IsDirty() = 0;

        virtual Core::Operator* getOperator() = 0;

    private:
        int id;
        Constants::OperatorTypes type;
        String^ name;
        List<OperatorProperty^>^ properties;
	};
}