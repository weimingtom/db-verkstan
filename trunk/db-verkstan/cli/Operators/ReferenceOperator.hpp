#pragma once

#include "cli/Operator.hpp"
#include "cli/Operators/NameOperator.hpp"

using namespace System;

namespace Verkstan
{
    public ref class ReferenceOperator: public Operator
    {
    public:
        ReferenceOperator(List<OperatorProperty^>^ properties);
        virtual ~ReferenceOperator();
        
        property Operator^ Reference
        {
            Operator^ get();
        }

        void RefreshReference();
        void NameOperatorDirty(NameOperator^ nameOperator);

        virtual unsigned char GetByteProperty(int index) override;
        virtual void SetByteProperty(int index, unsigned char value) override;
        virtual int GetIntProperty(int index) override;
        virtual void SetIntProperty(int index, int value) override;
        virtual float GetFloatProperty(int index) override;
        virtual void SetFloatProperty(int index, float value) override;
        virtual String^ GetStringProperty(int index) override;
        virtual void SetStringProperty(int index, String ^string) override;

        virtual void CascadeProcess() override;
        virtual void Process() override;
        
        virtual void SetDirty(bool dirty) override;
        virtual bool IsDirty() override;

        virtual void ConnectInWith(Operator^ op) override;
        virtual void ConnectOutWith(Operator^ op) override;
        virtual void Disconnect() override;
        virtual bool IsProcessable() override;
        virtual void DisconnectInFrom(Operator^ op) override;
        virtual void DisconnectOutFrom(Operator^ op) override;
        virtual void DisconnectIns() override;
        
        virtual Core::Operator* getOperator() override;

    private:
        Operator^ reference;
        NameOperator^ nameReference;
        List<Operator^>^ outputConnections;
    };
}