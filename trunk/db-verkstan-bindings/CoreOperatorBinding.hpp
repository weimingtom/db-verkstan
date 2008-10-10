#include "OperatorBinding.hpp"

namespace VerkstanBindings
{
    public ref class CoreOperatorBinding: public OperatorBinding
	{
    public:
        CoreOperatorBinding(String^ name,
                            int operatorId,
                            Constants::OperatorTypes type,
                            List<OperatorBindingProperty^>^ properties,
                            List<OperatorBindingInput^>^ inputs);
        virtual ~CoreOperatorBinding();
        
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

        virtual void ConnectInWith(OperatorBinding^ operatorBinding) override;
        virtual void ConnectOutWith(OperatorBinding^ operatorBinding) override;
        virtual void Disconnect() override;
        virtual bool IsProcessable() override;
        virtual void DisconnectInFrom(OperatorBinding^ operatorBinding) override;
        virtual void DisconnectOutFrom(OperatorBinding^ operatorBinding) override;

        virtual Operator* getOperator() override;

    private:
        void flushInputConnections();
        void flushOutputConnections();

        bool dirty;
        List<OperatorBindingInput^>^ inputs;
        List<OperatorBinding^>^ inputConnections;
        List<OperatorBinding^>^ outputConnections;
	};
}