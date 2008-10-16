#define OPERATOR_HEADERS 1
#include "cli/Internal/Operators.hpp"
#undef OPERATOR_HEADERS

#include "cli/OperatorFactory.hpp"
#include "cli/Operators/CoreOperator.hpp"

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
#include "cli/Internal/Operators.hpp"
#undef OPERATOR_CATEGORY_DEFINES
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
        List<OperatorProperty^>^ properties = gcnew List<OperatorProperty^>();\
        List<OperatorInput^>^ inputs = gcnew List<OperatorInput^>();\
        op = gcnew CoreOperator(opName,  \
                               id,      \
                               Constants::OperatorTypes::Texture,   \
                               properties,  \
                               inputs);                                              
       
#define ADD_PROP(propName, propType, defaultValue)    \
    properties->Add(gcnew OperatorProperty(properties->Count, propName, Constants::OperatorPropertyTypes::##propType));  \
    op->Set##propType##Property(properties->Count - 1, defaultValue);
#define ADD_INPUT(inType) \
    if (inputs->Count > 0 && !inputs[inputs->Count - 1]->Infinite) \
        throw gcnew System::Exception("Unable to add an input because last added input was infinite!"); \
    inputs->Add(gcnew OperatorInput(inputs->Count, Constants::OperatorTypes::##inType, false));
#define ADD_INFINITE_INPUT(inType) \
    if (inputs->Count > 0 && !inputs[inputs->Count - 1]->Infinite) \
        throw gcnew System::Exception("Unable to add an input because last added input was infinite!"); \
    inputs->Add(gcnew OperatorInput(inputs->Count, Constants::OperatorTypes::##inType, true));
#define END_OP() }

    Operator^ OperatorFactory::Create(String^ name)
    {
        Operator^ op;
#define OPERATOR_DEFINES 1
#include "cli/Internal/Operators.hpp"
#undef OPERATOR_DEFINES

        return op;
     }
}