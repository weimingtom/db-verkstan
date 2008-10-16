#include "cli/Operators/ReferenceOperator.hpp"

#include "cli/Internal/NameAndReferenceOperatorManager.hpp"

namespace Verkstan
{
    ReferenceOperator::ReferenceOperator(List<OperatorProperty^>^ properties)
        : Operator("Reference", 
                   -1, 
                   Constants::OperatorTypes::Reference,
                   Constants::OperatorTypes::Reference,
                   properties)
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
     
    void ReferenceOperator::CascadeProcess()
    {
        if (nameOperator != nullptr)
            nameOperator->CascadeProcess();
    }

    void ReferenceOperator::Process()
    {
        dirty = false;
    }

    void ReferenceOperator::SetDirty(bool dirty)
    {
        /*
        this->dirty = dirty;

        for (int i = 0; i < outputConnections->Count; i++)
            outputConnections[i]->SetDirty(dirty);*/
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
            FindNameAndUpdateConnections();
        }
    }

    void ReferenceOperator::ConnectOutWith(Operator^ op)
    {
        outputConnections->Add(op);
    }

    void ReferenceOperator::ConnectInWith(Operator^ op)
    {

    }

    void ReferenceOperator::Disconnect()
    {  
        /*
        if (reference == nullptr)
        {
            outputConnections->Clear();
            return;
        }

        for (int i = 0; i < outputConnections->Count; i++)
            outputConnections[i]->DisconnectInFrom(reference);
         
        outputConnections->Clear();
        */
    }

    bool ReferenceOperator::IsProcessable()
    {
        return nameOperator != nullptr && nameOperator->IsProcessable();
    }

    void ReferenceOperator::DisconnectInFrom(Operator^ op)
    {
        
    }

    void ReferenceOperator::DisconnectOutFrom(Operator^ op)
    {
        outputConnections->Remove(op);
    }

    Core::Operator* ReferenceOperator::getOperator()
    {
        if (nameOperator != nullptr)
            return nameOperator->getOperator();
        return 0;
    }

    void ReferenceOperator::FindNameAndUpdateConnections()
    {
         NameOperator^ newNameOperator = NameAndReferenceOperatorManager::FindNameOperator(DisplayName);

         if (newNameOperator != nameOperator && nameOperator != nullptr && reference != nullptr)
         {
            for (int i = 0; i < outputConnections->Count; i++)
            {
                reference->DisconnectOutFrom(outputConnections[i]);
                outputConnections[i]->DisconnectInFrom(reference);
                outputConnections[i]->UpdateRealInputConnections();
            }
            reference->UpdateRealOutputConnections();
         }

         nameOperator = newNameOperator;

         FindReferenceAndUpdateConnections();
    }

    void ReferenceOperator::FindReferenceAndUpdateConnections()
    {
        Operator^ newReference;
        if (nameOperator != nullptr)
            newReference = nameOperator->getInput();
        else
            newReference = nullptr;

        if (newReference != reference && reference != nullptr)
        {
            for (int i = 0; i < outputConnections->Count; i++)
            {
                reference->DisconnectOutFrom(outputConnections[i]);
                outputConnections[i]->DisconnectInFrom(reference);
                outputConnections[i]->UpdateRealInputConnections();
            }
            reference->UpdateRealOutputConnections();
        }
        if (newReference != reference && newReference != nullptr)
        {
            for (int i = 0; i < outputConnections->Count; i++)
            {
                newReference->ConnectOutWith(outputConnections[i]);
                outputConnections[i]->ConnectInWith(newReference);
                outputConnections[i]->UpdateRealInputConnections();
            }
            newReference->UpdateRealOutputConnections();
        }

        reference = newReference;
    }

    void ReferenceOperator::UpdateConnections()
    {
        /*
        if (nameOperator == nullptr || reference == nullptr)
            return;

        for (int i = 0; i < outputConnections->Count; i++)
        {
            reference->ConnectOutWith(outputConnections[i]);
            outputConnections[i]->DisconnectInFrom(reference);
            outputConnections[i]->UpdateRealInputConnections();
        }
        reference->UpdateRealOutputConnections();
        */
    }

    void ReferenceOperator::UpdateRealInputConnections()
    {

    }

    void ReferenceOperator::UpdateRealOutputConnections()
    {

    }

    void ReferenceOperator::UpdateRealConnections()
    {

    }

    int ReferenceOperator::getOperatorId()
    {
        return -1;
    }
}