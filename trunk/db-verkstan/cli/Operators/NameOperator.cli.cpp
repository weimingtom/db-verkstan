#include "cli/Operators/NameOperator.hpp"

#include "cli/Internal/NameAndReferenceOperatorManager.hpp"

namespace Verkstan
{
    NameOperator::NameOperator(List<OperatorProperty^>^ properties)
        : Operator("Name", -1, Constants::OperatorTypes::Name, properties)
    {
        NameAndReferenceOperatorManager::AddNameOperator(this);
        dirty = true;
    }

    NameOperator::~NameOperator()
    {
        Disconnect();
        NameAndReferenceOperatorManager::RemoveNameOperator(this);
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
        dirty = false;
    }

    void NameOperator::SetDirty(bool dirty)
    {
        if (dirty && input != nullptr)
            NameAndReferenceOperatorManager::NameOperatorDirty(this);
    }

    bool NameOperator::IsDirty()
    {
        return dirty;
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
        if (index == 0)
            return gcnew String(DisplayName);
        else
            return gcnew String("");
    }

    void NameOperator::SetStringProperty(int index, String^ value)
    {
        if (index == 0)
        {
            DisplayName = value;
            NameAndReferenceOperatorManager::RefreshReferenceOperators();
        }
    }

    void NameOperator::ConnectInWith(Operator^ op)
    {
        if (input == nullptr 
            && op->Type != Constants::OperatorTypes::Name
            && op->Type != Constants::OperatorTypes::Reference)
        {
            input = op;
            op->ConnectOutWith(this); 
            NameAndReferenceOperatorManager::RefreshReferenceOperators();
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

        NameAndReferenceOperatorManager::RefreshReferenceOperators();
    }

    bool NameOperator::IsProcessable()
    {
        return input != nullptr && input->IsProcessable();
    }

    void NameOperator::DisconnectInFrom(Operator^ op)
    {
        if (input == op)
            input = nullptr;

         NameAndReferenceOperatorManager::RefreshReferenceOperators();
    }

    void NameOperator::DisconnectIns()
    {
    }

    void NameOperator::DisconnectOutFrom(Operator^ op)
    {

    }

    Core::Operator* NameOperator::getOperator()
    {
        return 0;
    }
}