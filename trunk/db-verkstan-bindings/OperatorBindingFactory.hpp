#pragma once

#include "Constants.hpp"
#include "OperatorBinding.hpp"

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace VerkstanBindings 
{
    public ref class OperatorBindingFactory
    {
    public:
        static ICollection<String^>^ GetCategories();
        static ICollection<String^>^ GetNamesInCategory(String^ category);
        static OperatorBinding^ Create(String^ name);
     
    private:
        static void CreateCategories();
        static Dictionary<String^, List<String^>^>^ categories;
    };
}