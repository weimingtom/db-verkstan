#include "cli/SceneOperator.hpp"

#include "cli/Channel.hpp"
#include "cli/Clip.hpp"

namespace Verkstan
{
    SceneOperator::SceneOperator(String^ typeName,
                                 int operatorId,
                                 Constants::OperatorTypes type,
                                 List<OperatorInput^>^ inputs)
        : CoreOperator(typeName,
                       operatorId,
                       type,
                       inputs)
    {
        channels = gcnew List<Channel^>();
        getOperator()->beats = DB_TICKS_PER_BEAT;
    }

    void SceneOperator::AddChannel(Channel^ channel)
    {
        channels->Add(channel);
        channels[channels->Count - 1]->Number = channels->Count - 1;
    }

    void SceneOperator::RemoveChannel(int index)
    {
        channels->Remove(channels[index]);
    }

    void SceneOperator::RemoveChannel(Channel^ channel)
    {
        channels->Remove(channel);
    }

    List<Channel^>^ SceneOperator::Channels::get()
    {
        return channels;
    }

    void SceneOperator::UpdateRealClips()
    {
        for (int i = 0; i < DB_MAX_OPERATOR_CLIPS; i++)
            getOperator()->operatorClips[i] = -1;

        int numberOfClips = 0;
        int beats = DB_TICKS_PER_BEAT;
        for (int i = 0; i < channels->Count; i++)
        {
            int clipsCount = channels[i]->Clips->Count;
            for (int j = 0; j < clipsCount; j++)
            {
                getOperator()->operatorClips[i] = channels[i]->Clips[j]->Id;
                numberOfClips++;
                if (channels[i]->Clips[j]->End > beats)
                    beats = channels[i]->Clips[j]->End;
            }
        }

        getOperator()->numberOfClips = numberOfClips;
        getOperator()->beats = beats;
    }
    
    int SceneOperator::Beats::get()
    {
         return getOperator()->beats;
    }
}