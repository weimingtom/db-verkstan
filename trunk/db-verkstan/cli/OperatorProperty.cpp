#include "cli/Operator.hpp"

#include "cli/OperatorProperty.hpp"

namespace Verkstan
{
    OperatorProperty::OperatorProperty(Operator^ op,
                                       int index,
                                       String^ name, 
                                       Constants::OperatorPropertyTypes type)
    {
        Name = name;
        Type = type;
        Index = index;
        ParentOperator = op;
    }

      OperatorProperty::OperatorProperty(Operator^ op,
                                         int index,
                                         String^ name, 
                                         Constants::OperatorPropertyTypes type,
                                         List<String^>^ enumValues)
    {
        Name = name;
        Type = type;
        Index = index;
        EnumValues = enumValues;
        ParentOperator = op;
    }

    int OperatorProperty::Channel1::get()
    {
        return ParentOperator->getOperator()->properties[Index].channel1;
    }

    int OperatorProperty::Channel2::get()
    {
        return ParentOperator->getOperator()->properties[Index].channel2;
    }

    int OperatorProperty::Channel3::get()
    {
        return ParentOperator->getOperator()->properties[Index].channel3;
    }

    void OperatorProperty::Channel1::set(int channel)
    {
        System::Console::WriteLine("Channel1::set("+ channel + ")");
        ParentOperator->getOperator()->properties[Index].channel1 = channel;
        if (channel == -1)
        {
            ParentOperator->getOperator()->properties[Index].channelValue1 = 0.0f;
            ParentOperator->getOperator()->setDirty(true);
        }
    }

    void OperatorProperty::Channel2::set(int channel)
    {
        ParentOperator->getOperator()->properties[Index].channel2 = channel;
        if (channel == -1)
        {
            ParentOperator->getOperator()->properties[Index].channelValue2 = 0.0f;
            ParentOperator->getOperator()->setDirty(true);
        }
    }

    void OperatorProperty::Channel3::set(int channel)
    {
        ParentOperator->getOperator()->properties[Index].channel3 = channel;
        if (channel == -1)
        {
            ParentOperator->getOperator()->properties[Index].channelValue3 = 0.0f; 
            ParentOperator->getOperator()->setDirty(true);
        }
    }

    float OperatorProperty::Amplify1::get()
    {
        return ParentOperator->getOperator()->properties[Index].amplify1;
    }

    float OperatorProperty::Amplify2::get()
    {
        return ParentOperator->getOperator()->properties[Index].amplify2;
    }

    float OperatorProperty::Amplify3::get()
    {
        return ParentOperator->getOperator()->properties[Index].amplify3;
    }

    void OperatorProperty::Amplify1::set(float amplify)
    {
        ParentOperator->getOperator()->properties[Index].amplify1 = amplify;
    }

    void OperatorProperty::Amplify2::set(float amplify)
    {
        ParentOperator->getOperator()->properties[Index].amplify2 = amplify;
    }

    void OperatorProperty::Amplify3::set(float amplify)
    {
        ParentOperator->getOperator()->properties[Index].amplify3 = amplify;
    }

    float OperatorProperty::Offset1::get()
    {
        return ParentOperator->getOperator()->properties[Index].offset1;
    }
    
    float OperatorProperty::Offset2::get()
    {
        return ParentOperator->getOperator()->properties[Index].offset2;
    }

    float OperatorProperty::Offset3::get()
    {
        return ParentOperator->getOperator()->properties[Index].offset3;
    }

    void OperatorProperty::Offset1::set(float offset)
    {
        ParentOperator->getOperator()->properties[Index].offset1 = offset;
    }

    void OperatorProperty::Offset2::set(float offset)
    {
        ParentOperator->getOperator()->properties[Index].offset2 = offset;
    }

    void OperatorProperty::Offset3::set(float offset)
    {
        ParentOperator->getOperator()->properties[Index].offset3 = offset;
    }
}