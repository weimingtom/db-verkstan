#include "NameOperator.hpp"

namespace VerkstanBindings
{
    NameOperator::NameOperator(List<OperatorProperty^>^ properties)
        : Operator("Name", -1, Constants::OperatorTypes::Name, properties)
    {

    }

    NameOperator::~NameOperator()
    {

    }

    Operator^ NameOperator::Input::get()
    {
        return input;
    }
     
    void NameOperator::CascadeProcess()
    {
        if (input != nullptr)
            input->CascadeProcess();
    }

    void NameOperator::Process()
    {

    }

    void NameOperator::SetDirty(bool dirty)
    {

    }

    bool NameOperator::IsDirty()
    {
        return false;
    }

    unsigned char NameOperator::GetByteProperty(int index)
    {
        return 0;
    }

    void NameOperator::SetByteProperty(int index, unsigned char value)
    {

    }

    int NameOperator::GetIntProperty(int index)
    {
        return 0;
    }

    void NameOperator::SetIntProperty(int index, int value)
    {

    }

    float NameOperator::GetFloatProperty(int index)
    {
        return 0;
    }

    void NameOperator::SetFloatProperty(int index, float value)
    {
        
    }

    String^ NameOperator::GetStringProperty(int index)
    {
        return gcnew String("");
    }

    void NameOperator::SetStringProperty(int index, String^ value)
    {

    }

    void NameOperator::ConnectInWith(Operator^ op)
    {
        if (input == nullptr 
            && op->Type != Constants::OperatorTypes::Name
            && op->Type != Constants::OperatorTypes::Reference)
        {
            input = op;
            op->ConnectOutWith(this);
        }
    }

    void NameOperator::ConnectOutWith(Operator^ op)
    {

    }

    void NameOperator::Disconnect()
    {
        if (input != nullptr)
            input->DisconnectOutFrom(this);

        input = nullptr;
    }

    bool NameOperator::IsProcessable()
    {
        return input != nullptr && input->IsProcessable();
    }

    void NameOperator::DisconnectInFrom(Operator^ op)
    {
        if (input == op)
            input = nullptr;
    }

    void NameOperator::DisconnectOutFrom(Operator^ op)
    {

    }

    VerkstanCore::Operator* NameOperator::getOperator()
    {
        return 0;
    }
}