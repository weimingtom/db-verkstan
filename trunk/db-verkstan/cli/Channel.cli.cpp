#include "cli/SceneOperator.hpp"

#include "cli/Channel.hpp"
#include "cli/Clip.hpp"

namespace Verkstan
{
    Channel::Channel(SceneOperator^ owner)
        :number(-1)
    {
        this->owner = owner;
        clips = gcnew List<Clip^>();
    }

    int Channel::Number::get()
    {
        return number;
    }
    
    void Channel::Number::set(int newNumber)
    {
        number = newNumber;
    }

    void Channel::AddClip(Clip^ clip)
    {
        clip->Channel = number;
        clips->Add(clip);
        owner->UpdateRealClips();
    }

    void Channel::RemoveClip(Clip^ clip)
    {
        clip->Channel = -1;
        clips->Remove(clip);
        owner->UpdateRealClips();
    }

    List<Clip^>^ Channel::Clips::get()
    {
        return clips;
    }
}