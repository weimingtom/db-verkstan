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
        virtual void SetByteProperty(int index, unsigned char byteValue) override;
        virtual int GetIntProperty(int index) override;
        virtual void SetIntProperty(int index, int intValue) override;
        virtual float GetFloatProperty(int index) override;
        virtual void SetFloatProperty(int index, float floatValue) override;
        virtual String^ GetStringProperty(int index) override;
        virtual void SetStringProperty(int index, String ^string) override;
        
        virtual void CascadeProcess() override;

        virtual void ConnectInWith(OperatorBinding^ operatorBinding) override;
        virtual void ConnectOutWith(OperatorBinding^ operatorBinding) override;
        virtual void Disconnect() override;
        virtual bool IsProcessable() override;
        virtual void DisconnectInFrom(OperatorBinding^ operatorBinding) override;
        virtual void DisconnectOutFrom(OperatorBinding^ operatorBinding) override;

    private:
        void flushInputConnections();
        void flushOutputConnections();

        List<OperatorBindingInput^>^ inputs;
        List<OperatorBinding^>^ inputConnections;
        List<OperatorBinding^>^ outputConnections;
	};
}