#include "cli/Internal/NameAndReferenceOperatorManager.hpp"

namespace Verkstan
{
    void NameAndReferenceOperatorManager::AddNameOperator(NameOperator^ nameOperator)
    {
        nameOperators->Add(nameOperator);
        NameAndReferenceOperatorManager::RefreshReferenceOperators();
    }

    void NameAndReferenceOperatorManager::RemoveNameOperator(NameOperator^ nameOperator)
    {
        nameOperators->Remove(nameOperator);
        NameAndReferenceOperatorManager::RefreshReferenceOperators();
    }

    void NameAndReferenceOperatorManager::AddReferenceOperator(ReferenceOperator^ referenceOperator)
    {
        referenceOperators->Add(referenceOperator);
    }

    void NameAndReferenceOperatorManager::RemoveReferenceOperator(ReferenceOperator^ referenceOperator)
    {
         referenceOperators->Remove(referenceOperator);
    }

    NameOperator^ NameAndReferenceOperatorManager::FindNameOperator(String^ name)
    {
        for (int i = 0; i < nameOperators->Count; i++)
        {
            if (nameOperators[i]->DisplayName == name)
                return nameOperators[i];
        }

        return nullptr;
    }

    void NameAndReferenceOperatorManager::RefreshReferenceOperators()
    {
        for (int i = 0; i < referenceOperators->Count; i++)
            referenceOperators[i]->RefreshReference();
    }

    void NameAndReferenceOperatorManager::NameOperatorDirty(NameOperator^ nameOperator)
    {
        for (int i = 0; i < referenceOperators->Count; i++)
            referenceOperators[i]->NameOperatorDirty(nameOperator);
    }
}