#pragma once

#include "cli/Constants.hpp"

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace Verkstan 
{
    ref class Operator;

    public ref class OperatorFactory
    {
    public:
        static ICollection<String^>^ GetCategories();
        static ICollection<String^>^ GetNamesInCategory(String^ category);
        static Operator^ Create(String^ name);
     
    private:
        static void CreateCategories();
        static Dictionary<String^, List<String^>^>^ categories;
    };
}