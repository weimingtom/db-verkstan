#include "cli/Operators/ReferenceOperator.hpp"

#include "cli/Internal/NameAndReferenceOperatorManager.hpp"

namespace Verkstan
{
    ReferenceOperator::ReferenceOperator(List<OperatorProperty^>^ properties)
        : Operator("Reference", -1, Constants::OperatorTypes::Reference, properties)
    {
        outputConnections = gcnew List<Operator^>();
        NameAndReferenceOperatorManager::AddReferenceOperator(this);
        dirty = false;
    }

    ReferenceOperator::~ReferenceOperator()
    {
        Disconnect();
        NameAndReferenceOperatorManager::RemoveReferenceOperator(this);
    }

    Operator^ ReferenceOperator::Reference::get()
    {
        return reference;
    }
     
    void ReferenceOperator::CascadeProcess()
    {
        if (nameReference != nullptr)
            nameReference->CascadeProcess();
    }

    void ReferenceOperator::Process()
    {
        dirty = false;
    }

    void ReferenceOperator::SetDirty(bool dirty)
    {
        this->dirty = dirty;

        for (int i = 0; i < outputConnections->Count; i++)
            outputConnections[i]->SetDirty(dirty);
    }

    bool ReferenceOperator::IsDirty()
    {
        return dirty;
    }

    unsigned char ReferenceOperator::GetByteProperty(int index)
    {
        return 0;
    }

    void ReferenceOperator::SetByteProperty(int index, unsigned char value)
    {

    }

    int ReferenceOperator::GetIntProperty(int index)
    {
        return 0;
    }

    void ReferenceOperator::SetIntProperty(int index, int value)
    {

    }

    float ReferenceOperator::GetFloatProperty(int index)
    {
        return 0;
    }

    void ReferenceOperator::SetFloatProperty(int index, float value)
    {
        
    }

    String^ ReferenceOperator::GetStringProperty(int index)
    {
        if (index == 0)
            return gcnew String(DisplayName);
        else
            return gcnew String("");
    }

    void ReferenceOperator::SetStringProperty(int index, String^ value)
    {
        if (index == 0)
        {
            DisplayName = value;
            RefreshReference();
        }
    }

    void ReferenceOperator::ConnectOutWith(Operator^ op)
    {
        if (op->Type == Constants::OperatorTypes::Name
            || op->Type == Constants::OperatorTypes::Reference)
            return;
        
        outputConnections->Add(op);

        if (reference != nullptr)
            op->ConnectInWith(reference);
    }

    void ReferenceOperator::ConnectInWith(Operator^ op)
    {

    }

    void ReferenceOperator::Disconnect()
    {  
        if (reference == nullptr)
        {
            outputConnections->Clear();
            return;
        }

        for (int i = 0; i < outputConnections->Count; i++)
            outputConnections[i]->DisconnectInFrom(reference);
         
        outputConnections->Clear();
    }

    bool ReferenceOperator::IsProcessable()
    {
        return nameReference != nullptr && nameReference->IsProcessable();
    }

    void ReferenceOperator::DisconnectInFrom(Operator^ op)
    {
        
    }

    void ReferenceOperator::DisconnectIns()
    {
    }

    void ReferenceOperator::DisconnectOutFrom(Operator^ op)
    {
        if (reference != nullptr)
            op->DisconnectInFrom(reference);

        outputConnections->Remove(op);
    }

    Core::Operator* ReferenceOperator::getOperator()
    {
        return 0;
    }

    void ReferenceOperator::RefreshReference()
    {
        nameReference = NameAndReferenceOperatorManager::FindNameOperator(DisplayName);
        Operator^ newReference = nullptr;

        if (nameReference != nullptr)
            newReference = nameReference->Input;

        System::Console::WriteLine(nameReference + " " + newReference);

        if (newReference == nullptr && reference == nullptr)
        {    
            for (int i = 0; i < outputConnections->Count; i++)
                outputConnections[i]->DisconnectIns();
        }
        else if (newReference == nullptr)
        {
            for (int i = 0; i < outputConnections->Count; i++)
                outputConnections[i]->DisconnectIns();
        }
        else
        {
            for (int i = 0; i < outputConnections->Count; i++)
            {
                outputConnections[i]->DisconnectInFrom(reference);
                outputConnections[i]->ConnectInWith(newReference);
            }
        }

        reference = newReference;
    }

    void ReferenceOperator::NameOperatorDirty(NameOperator^ nameOperator)
    {
        if (nameOperator == nameReference)
            SetDirty(true);
    }
}