#pragma once

#include "cli/Constants.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan 
{ 
    ref class Operator;
    ref class OperatorProperty;

    public ref class OperatorProperties
    {
    public:
        OperatorProperties(Operator^ op);
        OperatorProperty^ operator[](int index);
        property int Count
        {
            int get();
        }
        void Add(String^ name, Constants::OperatorPropertyTypes type);
        void AddEnum(String^ name, List<String^>^ values);
        List<OperatorProperty^>^ GetList();
       
    private:
        List<OperatorProperty^>^ properties;
        Operator^ op;
    };
}