#include "NameOperatorBinding.hpp"

namespace VerkstanBindings
{
    NameOperatorBinding::NameOperatorBinding(List<OperatorBindingProperty^>^ properties)
        : OperatorBinding("Name", -1, Constants::OperatorTypes::Name, properties)
    {

    }

    NameOperatorBinding::~NameOperatorBinding()
    {

    }

    OperatorBinding^ NameOperatorBinding::Input::get()
    {
        return input;
    }
     
    void NameOperatorBinding::CascadeProcess()
    {
        if (input != nullptr)
            input->CascadeProcess();
    }

    void NameOperatorBinding::Process()
    {

    }

    void NameOperatorBinding::SetDirty(bool dirty)
    {

    }

    bool NameOperatorBinding::IsDirty()
    {
        return false;
    }

    unsigned char NameOperatorBinding::GetByteProperty(int index)
    {
        return 0;
    }

    void NameOperatorBinding::SetByteProperty(int index, unsigned char value)
    {

    }

    int NameOperatorBinding::GetIntProperty(int index)
    {
        return 0;
    }

    void NameOperatorBinding::SetIntProperty(int index, int value)
    {

    }

    float NameOperatorBinding::GetFloatProperty(int index)
    {
        return 0;
    }

    void NameOperatorBinding::SetFloatProperty(int index, float value)
    {
        
    }

    String^ NameOperatorBinding::GetStringProperty(int index)
    {
        return gcnew String("");
    }

    void NameOperatorBinding::SetStringProperty(int index, String^ value)
    {

    }

    void NameOperatorBinding::ConnectInWith(OperatorBinding^ operatorBinding)
    {
        if (input == nullptr 
            && operatorBinding->Type != Constants::OperatorTypes::Name
            && operatorBinding->Type != Constants::OperatorTypes::Reference)
        {
            input = operatorBinding;
            operatorBinding->ConnectOutWith(this);
        }
    }

    void NameOperatorBinding::ConnectOutWith(OperatorBinding^ operatorBinding)
    {

    }

    void NameOperatorBinding::Disconnect()
    {
        if (input != nullptr)
            input->DisconnectOutFrom(this);

        input = nullptr;
    }

    bool NameOperatorBinding::IsProcessable()
    {
        return input != nullptr && input->IsProcessable();
    }

    void NameOperatorBinding::DisconnectInFrom(OperatorBinding^ operatorBinding)
    {
        if (input == operatorBinding)
            input = nullptr;
    }

    void NameOperatorBinding::DisconnectOutFrom(OperatorBinding^ operatorBinding)
    {

    }

    Operator* NameOperatorBinding::getOperator()
    {
        return 0;
    }
}