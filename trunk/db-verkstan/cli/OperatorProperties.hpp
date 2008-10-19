#pragma once

#include "cli/Constants.hpp"
#include "cli/OperatorProperty.hpp"

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace Verkstan 
{ 
    public ref class OperatorProperties
    {
    public:
        OperatorProperties();
        OperatorProperty^ operator[](int index);
        property int Count
        {
            int get();
        }
        property int CoreCount
        {
            int get();
        }
        void Add(String^ name, Constants::OperatorPropertyTypes type, int numberOfValues);
        List<OperatorProperty^>^ GetList();

    private:
        List<OperatorProperty^>^ properties;
        int coreCount; 
    };
}