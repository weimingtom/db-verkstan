#include <vcclr.h>
#include "OperatorBinding.hpp"
#include "Color.hpp"
#include "OperatorBindingInput.hpp"
#include "OperatorBindingProperty.hpp"
#include "Vector.hpp"

namespace Verkstan
{
    OperatorBinding::OperatorBinding(unsigned char number,
                               String^ name,
                               unsigned short operatorId,
                               Constants::OperatorTypes type)
    {
        this->number = number;
        this->name = name;
        this->id = operatorId;
        this->type = type;
        this->properties = gcnew List<OperatorBindingProperty^>(); 
        this->inputs = gcnew List<OperatorBindingInput^>();
    }

    OperatorBinding::~OperatorBinding()
    {
        delete InternalOperator::operators[id];
        InternalOperator::operators[id] = 0;
    }

    unsigned char OperatorBinding::Number::get()
    {
        return number;
    }

    unsigned short OperatorBinding::Id::get()
    {
        return id;
    }

    String^ OperatorBinding::Name::get()
    {
        return name;
    }

    short OperatorBinding::NumberOfConstantInputs::get()
    {
        short result = 0;
        for (int i = 0; i < inputs->Count; i++)
        {
            OperatorBindingInput^ input = inputs[i];

            if (input->Infinite || input->Optional)
                return -1;

            result++;
        }

        return result;
    }

    List<OperatorBindingProperty^>^ OperatorBinding::Properties::get() 
    {
        return properties;
    }

    List<OperatorBindingInput^>^ OperatorBinding::Inputs::get() 
    {
        return inputs;
    }

    Constants::OperatorTypes OperatorBinding::Type::get() 
    {
        return type;
    }

    void OperatorBinding::AddProperty(String^ name, Constants::OperatorPropertyTypes type)
    {
        OperatorBindingProperty^ prop = gcnew OperatorBindingProperty(properties->Count,
                                                        name,
                                                        type);
        properties->Add(prop);
    }

    void OperatorBinding::AddEnumProperty(String^ name, List<String^>^ values)
    {
        OperatorBindingProperty^ prop = gcnew OperatorBindingProperty(properties->Count,
                                                        name,
                                                        Constants::OperatorPropertyTypes::Enum,
                                                        values);
        properties->Add(prop);
    }

    void OperatorBinding::AddInput(Constants::OperatorTypes type, bool infinite, bool optional)
    {
        OperatorBindingInput^ input = gcnew OperatorBindingInput(inputs->Count, type, infinite, optional);
        inputs->Add(input);
    }

    unsigned char OperatorBinding::GetByteProperty(int index)
    {
        return getOperator()->properties[index].byteValue;
    }

    void OperatorBinding::SetByteProperty(int index, unsigned char value)
    {
        getOperator()->properties[index].byteValue = value; 
        getOperator()->setDirty(true);
    }

    int OperatorBinding::GetIntProperty(int index)
    {
         return getOperator()->properties[index].intValue;
    }

    void OperatorBinding::SetIntProperty(int index, int value)
    {
        getOperator()->properties[index].intValue = value; 
        getOperator()->setDirty(true);
    }

    float OperatorBinding::GetFloatProperty(int index)
    {
        return getOperator()->properties[index].floatValue;
    }

    void OperatorBinding::SetFloatProperty(int index, float value)
    {
        getOperator()->properties[index].floatValue = value; 
        getOperator()->setDirty(true);
    }

    String^ OperatorBinding::GetStringProperty(int index)
    {   
        return gcnew String(getOperator()->getStringProperty(index));   
    }

    void OperatorBinding::SetStringProperty(int index, String^ string)
    {
        // Pin memory so GC can't move it while native function is called
        pin_ptr<const wchar_t> wch = PtrToStringChars(string);
     
        // Conversion to char* :
        // Can just convert wchar_t* to char* using one of the 
        // conversion functions such as: 
        // WideCharToMultiByte()
        // wcstombs_s()
        // ... etc
        size_t convertedChars = 0;
        size_t sizeInBytes = ((string->Length + 1) * 2);
        errno_t err = 0;
        char *ch = (char*)malloc(sizeInBytes);

        err = wcstombs_s(&convertedChars, 
                         ch, 
                         sizeInBytes,
                         wch, 
                         sizeInBytes);

        strcpy(getOperator()->properties[index].stringValue, ch);
        getOperator()->setDirty(true);
    }

    Vector^ OperatorBinding::GetVectorProperty(int index)
    {
        D3DXVECTOR3 vector = getOperator()->properties[index].vectorValue;
        return gcnew Vector(vector.x, vector.y, vector.z);
    }

    void OperatorBinding::SetVectorProperty(int index, Vector^ vector)
    {
        getOperator()->properties[index].vectorValue.x = vector->X;
        getOperator()->properties[index].vectorValue.y = vector->Y;
        getOperator()->properties[index].vectorValue.z = vector->Z;
        getOperator()->setDirty(true);
    }

    Color^ OperatorBinding::GetColorProperty(int index)
    {
        D3DXCOLOR color = getOperator()->properties[index].colorValue;
        return gcnew Color((unsigned char)(color.r * 255), 
                           (unsigned char)(color.g * 255), 
                           (unsigned char)(color.b * 255));
    }

    void OperatorBinding::SetColorProperty(int index, Color^ color)
    {
        getOperator()->properties[index].colorValue.r = color->R / 255.0f;
        getOperator()->properties[index].colorValue.g = color->G / 255.0f;
        getOperator()->properties[index].colorValue.b = color->B / 255.0f;
        getOperator()->setDirty(true);
    }

    InternalOperator* OperatorBinding::getOperator()
    {
        InternalOperator* op = InternalOperator::operators[id];
        return InternalOperator::operators[id];
    }

    void OperatorBinding::ClearInputConnections()
    {
        for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
            getOperator()->inputs[i] = -1;
        getOperator()->numberOfInputs = 0;
    }

    void OperatorBinding::ClearOutputConnections()
    {
        for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
            getOperator()->outputs[i] = -1;
        getOperator()->numberOfOutputs = 0;
    }

    int OperatorBinding::GetInputConnectionId(int index)
    {
        return getOperator()->inputs[index];
    }

    int OperatorBinding::GetOutputConnectionId(int index)
    {
        return getOperator()->outputs[index];
    }

    void OperatorBinding::SetInputConnectionId(int index, int id)
    {
        getOperator()->inputs[index] = id;
    }

    void OperatorBinding::SetOutputConnectionId(int index, int id)
    {
        getOperator()->outputs[index] = id;
    }

    int OperatorBinding::GetMaxInputConnections()
    {
        return DB_MAX_OPERATOR_CONNECTIONS;
    }

    int OperatorBinding::GetMaxOutputConnections()
    {
        return DB_MAX_OPERATOR_CONNECTIONS;
    }

    int OperatorBinding::GetNumberOfInputConnections()
    {
        return getOperator()->numberOfInputs;
    }

    int OperatorBinding::GetNumberOfOutputConnections()
    {
        return getOperator()->numberOfOutputs;
    }

    void OperatorBinding::SetNumberOfInputConnections(int number)
    {
        InternalOperator* op = getOperator();
        getOperator()->numberOfInputs = number;
    }

    void OperatorBinding::SetNumberOfOutputConnections(int number)
    {
        getOperator()->numberOfOutputs = number;
    }

    void OperatorBinding::SetDirty(bool dirty)
    {
        InternalOperator* op = getOperator();
        int opi = (int)op;
        System::Console::WriteLine("setDirty = " + opi);
        op->setDirty(dirty);
    }

    bool OperatorBinding::IsDirty()
    {
        return getOperator()->isDirty();
    }

    int OperatorBinding::GetNumberOfRequiredInputs()
    {
        int result = 0;

        for (int i = 0; i < inputs->Count; i++)
        {
            if (!inputs[i]->Optional && !inputs[i]->Infinite)
                result++;
        }

        return result;
    }
}