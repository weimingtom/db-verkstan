#include "cli/Clip.hpp"  

namespace Verkstan
{
    Clip::Clip()
    {

    }

    Clip::~Clip()
    {
        delete Core::clips[id];
        Core::clips[id] = 0;
    }

    int Clip::Id::get()
    {
        return id;
    }

    int Clip::Start::get()
    {
        return getClip()->start;
    }

    int Clip::End::get()
    {
        return getClip()->end;
    }

    int Clip::Channel::get()
    {
        return getClip()->channel;
    }

    void Clip::Start::set(int value)
    {
        getClip()->start = value;
    }

    void Clip::End::set(int value)
    {
        getClip()->end = value;
    }

    void Clip::Channel::set(int value)
    {
        getClip()->channel = value;
    }

    Core::Clip* Clip::getClip()
    {
        return Core::clips[id];
    }
}