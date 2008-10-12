#pragma once

#include "Constants.hpp"
#include "Operator.hpp"

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace VerkstanBindings 
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