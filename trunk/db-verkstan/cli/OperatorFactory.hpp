#pragma once

#include "cli/Constants.hpp"
#include "cli/Operator.hpp"

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace Verkstan 
{
    public ref class OperatorFactory
    {
    public:
        static ICollection<String^>^ GetCategories();
        static ICollection<String^>^ GetNamesInCategory(String^ category);
        static Operator^ Create(String^ name);
        static void Delete(Operator^ OP);
     
    private:
        static void CreateCategories();
        static Dictionary<String^, List<String^>^>^ categories;
    };
}