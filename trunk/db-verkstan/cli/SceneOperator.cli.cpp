#include "cli/SceneOperator.hpp"

#include "cli/Clip.hpp"

namespace Verkstan
{
    SceneOperator::SceneOperator(Operator^ sceneOperator)
        : CoreOperatorProxy(sceneOperator)
    {
        clips = gcnew List<Clip^>();
    }

    void SceneOperator::AddClip(Clip^ clip)
    {
        clips->Add(clip);

        UpdateClips();
    }

    void SceneOperator::RemoveClip(Clip^ clip)
    {
        clips->Remove(clip);

        UpdateClips();
    }

    void SceneOperator::UpdateClips()
    {
        for (int i = 0; i < DB_MAX_OPERATOR_CLIPS; i++)
            getOperator()->operatorClips[i] = -1;

        for (int i = 0; i < clips->Count; i++)
            getOperator()->operatorClips[i] = clips[i]->Id;

        getOperator()->numberOfClips = clips->Count;
    }
}