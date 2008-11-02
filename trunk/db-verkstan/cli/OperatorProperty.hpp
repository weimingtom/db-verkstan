#pragma once

#include "cli/Constants.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan 
{ 
    ref class Operator;
    public ref class OperatorProperty
    {
    public:
        OperatorProperty(Operator^ op,
                         int index, 
                         String^ name, 
                         Constants::OperatorPropertyTypes type);
        OperatorProperty(Operator^ op,
                         int index, 
                         String^ name, 
                         Constants::OperatorPropertyTypes type,
                         List<String^>^ enumValues);
        property String^ Name;
        property Constants::OperatorPropertyTypes Type;
        property int Index;
        property List<String^>^ EnumValues;
        property Operator^ ParentOperator;
        property int Channel1
        {
            int get();
            void set(int channel);
        }
        property int Channel2
        {
            int get();
            void set(int channel);
        }
        property int Channel3
        {
            int get();
            void set(int channel);
        }
        property float Amplify1
        {
            float get();
            void set(float amplify);
        }
        property float Amplify2
        {
            float get();
            void set(float amplify);
        }
        property float Amplify3
        {
            float get();
            void set(float amplify);
        }
    };
}