#define OPERATOR_HEADERS 1
#include "cli/Operators.hpp"
#undef OPERATOR_HEADERS

#include "cli/OperatorFactory.hpp"
#include "cli/Operator.hpp"
#include "cli/CoreOperator.hpp"
#include "cli/LoadOperator.hpp"
#include "cli/StoreOperator.hpp"

namespace Verkstan
{
#define ADD_OP_TO_CAT(name, category) \
if (!categories->ContainsKey(category)) \
    categories[category] = gcnew List<String^>(); \
categories[category]->Add(name);

    void OperatorFactory::CreateCategories()
    {
        categories = gcnew Dictionary<String^, List<String^>^>();
#define OPERATOR_CATEGORY_DEFINES 1
#include "cli/Operators.hpp"
#undef OPERATOR_CATEGORY_DEFINES

        if (!categories->ContainsKey("Misc"))
            categories->Add("Misc", gcnew List<String^>());
        
        if (!categories["Misc"]->Contains("Store"))
            categories["Misc"]->Add("Store");

        if (!categories["Misc"]->Contains("Load"))
            categories["Misc"]->Add("Load");
    }

    ICollection<String^>^ OperatorFactory::GetCategories()
    {
        if (!categories)
            CreateCategories();

        return categories->Keys;
    }

    ICollection<String^>^ OperatorFactory::GetNamesInCategory(String^ category)
    {
        if (!categories)
            CreateCategories();

        if (!categories->ContainsKey(category))
            return gcnew List<String^>();
        
        return categories[category];
    }

#define DEF_OP(opName, opClass, opType)             \
    if (name == opName)                             \
    {                                               \
        Core::Operator* o = new opClass##();\
        int id;                                     \
        for (int i = 0; i < DB_MAX_OPERATORS; i++)  \
        {                                           \
            if (operators[i] == 0)                  \
            {                                       \
                operators[i] = o;                   \
                id = i;                             \
                break;                              \
            }                                       \
        }                                           \
        OperatorProperties^ properties = gcnew OperatorProperties();\
        List<OperatorInput^>^ inputs = gcnew List<OperatorInput^>();\
        op = gcnew CoreOperator(opName,  \
                               id,      \
                               Constants::OperatorTypes::##opType,   \
                               properties,  \
                               inputs);                                              

  
#define ADD_BYTE_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::Byte, 1);  \
    op->SetByteProperty(properties->CoreCount - 1, value);
#define ADD_INT_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::Int, 1);  \
    op->SetIntProperty(properties->CoreCount - 1, value);
#define ADD_FLOAT_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::Float, 1);  \
    op->SetFloatProperty(properties->CoreCount - 1, value);
#define ADD_STRING_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::String, 1);  \
    op->SetStringProperty(properties->CoreCount - 1, value);
#define ADD_TEXT_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::Text, 1);  \
    op->SetStringProperty(properties->CoreCount - 1, value);
#define ADD_COLOR_PROP(name, r, g, b) \
    properties->Add(name, Constants::OperatorPropertyTypes::Color, 3);  \
    op->SetByteProperty(properties->CoreCount - 3, r);  \
    op->SetByteProperty(properties->CoreCount - 2, g);  \
    op->SetByteProperty(properties->CoreCount - 1, b);
#define ADD_VECTOR_PROP(name, x, y, z) \
    properties->Add(name, Constants::OperatorPropertyTypes::Vector, 3);  \
    op->SetFloatProperty(properties->CoreCount - 3, x);  \
    op->SetFloatProperty(properties->CoreCount - 2, y);  \
    op->SetFloatProperty(properties->CoreCount - 1, z);
#define ADD_INPUT(inType) \
    if (inputs->Count > 0 && inputs[inputs->Count - 1]->Infinite) \
        throw gcnew System::Exception("Unable to add an input because last added input was infinite!"); \
    inputs->Add(gcnew OperatorInput(inputs->Count, Constants::OperatorTypes::##inType, false, false));
#define ADD_INFINITE_INPUT(inType) \
    if (inputs->Count > 0 && inputs[inputs->Count - 1]->Infinite) \
        throw gcnew System::Exception("Unable to add an input because last added input was infinite!"); \
    inputs->Add(gcnew OperatorInput(inputs->Count, Constants::OperatorTypes::##inType, true, false));
#define ADD_OPTIONAL_INPUT(inType) \
    if (inputs->Count > 0 && inputs[inputs->Count - 1]->Infinite) \
        throw gcnew System::Exception("Unable to add an optional input because last added input was infinite!"); \
    inputs->Add(gcnew OperatorInput(inputs->Count, Constants::OperatorTypes::##inType, false, true));
#define END_OP() }

    Operator^ OperatorFactory::Create(String^ name)
    {
        Operator^ op;
#define OPERATOR_DEFINES 1
#include "cli/Operators.hpp"
#undef OPERATOR_DEFINES

        if (name == "Store")
        {
            OperatorProperties^ properties = gcnew OperatorProperties();
            properties->Add("Name", Constants::OperatorPropertyTypes::String, 1);
            op = gcnew StoreOperator(properties);
        }

        if (name == "Load")
        {
            OperatorProperties^ properties = gcnew OperatorProperties();
            properties->Add("Name", Constants::OperatorPropertyTypes::String, 1);
            op = gcnew LoadOperator(properties);
        }

        return op;
     }
}