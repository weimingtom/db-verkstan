#include "cli/joints.hpp"

#include "cli/Joint.hpp"

namespace Verkstan
{
    void Joints::Add(Joint^ joint)
    {
        joints->Add(joint);
    }

    void Joints::Remove(Joint^ joint)
    {
        joints->Remove(joint);
    }

    Joint^ Joints::Find(String^ name)
    {
        for (int i = 0; i < joints->Count; i++)
            if (joints[i]->Name == name)
                return joints[i];
        return nullptr;
    }

    List<Joint^>^ Joints::GetAll()
    {
        return joints;
    }
}