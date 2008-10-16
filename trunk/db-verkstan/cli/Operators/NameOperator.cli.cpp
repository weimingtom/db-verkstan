#include "cli/Operators/NameOperator.hpp"

#include "cli/Internal/NameAndReferenceOperatorManager.hpp"

namespace Verkstan
{
    NameOperator::NameOperator(List<OperatorProperty^>^ properties)
        : Operator("Name", 
                   -1, 
                   Constants::OperatorTypes::Name,
                   Constants::OperatorTypes::Name,
                   properties)
    {
        NameAndReferenceOperatorManager::AddNameOperator(this);
        dirty = true;

        inputConnections = gcnew List<Operator^>();
    }

    NameOperator::~NameOperator()
    {
        Disconnect();
        NameAndReferenceOperatorManager::RemoveNameOperator(this);
    }
     
    void NameOperator::CascadeProcess()
    {
        if (inputConnections->Count > 0)
            inputConnections[0]->CascadeProcess();
    }

    void NameOperator::Process()
    {
        dirty = false;
    }

    void NameOperator::SetDirty(bool dirty)
    {
        /*
        this->dirty = dirty;

        if (dirty && input != nullptr)
            NameAndReferenceOperatorManager::NameOperatorDirty(this);

        for (int i = 0; i < outputConnections->Count; i++)
            outputConnections[i]->SetDirty(dirty);
        */
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
        }
    }

    void NameOperator::ConnectInWith(Operator^ op)
    {
        inputConnections->Add(op);
    }

    void NameOperator::ConnectOutWith(Operator^ op)
    {

    }

    void NameOperator::Disconnect()
    {
        for (int i = 0; i < inputConnections->Count; i++)
        {
            Operator^ op = inputConnections[i];
            op->DisconnectOutFrom(this);
            op->UpdateRealOutputConnections();
        }
        inputConnections->Clear();

        id = -1;
        type = Constants::OperatorTypes::Name;
    }

    bool NameOperator::IsProcessable()
    {
        return inputConnections->Count > 0 && inputConnections[0]->IsProcessable();
    }

    void NameOperator::DisconnectInFrom(Operator^ op)
    {
        inputConnections->Remove(op);
    }

    void NameOperator::DisconnectOutFrom(Operator^ op)
    {

    }

    void NameOperator::UpdateRealInputConnections()
    {
        List<ReferenceOperator^>^ referenceOperators = NameAndReferenceOperatorManager::FindReferenceOperators(DisplayName);
        for (int i = 0; i < referenceOperators->Count; i++)
            referenceOperators[i]->FindReferenceAndUpdateConnections();
    }

    void NameOperator::UpdateRealOutputConnections()
    {

    }

    void NameOperator::UpdateRealConnections()
    {

    }

    Core::Operator* NameOperator::getOperator()
    {
        if (inputConnections->Count > 0)
            return inputConnections[0]->getOperator();
        return 0;
    }

    int NameOperator::getOperatorId()
    {
        if (inputConnections->Count > 0)
            return inputConnections[0]->Id;
        return -1;
    }

    Operator^ NameOperator::getInput()
    {
         if (inputConnections->Count > 0)
             return inputConnections[0];
         return nullptr;
    }
}