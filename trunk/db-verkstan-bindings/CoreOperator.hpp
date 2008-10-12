#include "Operator.hpp"

namespace VerkstanBindings
{
    public ref class CoreOperator: public Operator
	{
    public:
        CoreOperator(String^ name,
                            int operatorId,
                            Constants::OperatorTypes type,
                            List<OperatorProperty^>^ properties,
                            List<OperatorInput^>^ inputs);
        virtual ~CoreOperator();
        
        virtual unsigned char GetByteProperty(int index) override;
        virtual void SetByteProperty(int index, unsigned char value) override;
        virtual int GetIntProperty(int index) override;
        virtual void SetIntProperty(int index, int value) override;
        virtual float GetFloatProperty(int index) override;
        virtual void SetFloatProperty(int index, float value) override;
        virtual String^ GetStringProperty(int index) override;
        virtual void SetStringProperty(int index, String ^value) override;
        
        virtual void CascadeProcess() override;
        virtual void Process() override;
        
        virtual void SetDirty(bool dirty) override;
        virtual bool IsDirty() override;

        virtual void ConnectInWith(Operator^ operatorBinding) override;
        virtual void ConnectOutWith(Operator^ operatorBinding) override;
        virtual void Disconnect() override;
        virtual bool IsProcessable() override;
        virtual void DisconnectInFrom(Operator^ operatorBinding) override;
        virtual void DisconnectOutFrom(Operator^ operatorBinding) override;

        virtual VerkstanCore::Operator* getOperator() override;

    private:
        void flushInputConnections();
        void flushOutputConnections();

        bool dirty;
        List<OperatorInput^>^ inputs;
        List<Operator^>^ inputConnections;
        List<Operator^>^ outputConnections;
	};
}