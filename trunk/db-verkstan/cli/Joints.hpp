#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref class Joint;

    public ref class Joints
    {   
    public:
        static void Add(Joint^ joint);
        static void Remove(Joint^ joint);
        static Joint^ Find(String^ name);
        static List<Joint^>^ GetAll();
    private:
        static List<Joint^>^ joints = gcnew List<Joint^>();
    };
}