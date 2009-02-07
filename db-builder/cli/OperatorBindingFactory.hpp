#pragma once

#include "Constants.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan 
{
    ref class OperatorBinding;

    public ref class OperatorBindingFactory
    {
    public:
        static ICollection<String^>^ GetCategories();
        static ICollection<String^>^ GetNamesInCategory(String^ category);
        static OperatorBinding^ Create(String^ typeName);
     
    private:
        static void CreateCategories();
        static Dictionary<String^, List<String^>^>^ categories;
    };
}