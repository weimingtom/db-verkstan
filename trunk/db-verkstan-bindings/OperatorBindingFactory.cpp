#include "core.hpp"

#define OPERATOR_HEADERS 1
#include "operators.hpp"

#include "OperatorBindingFactory.hpp"

namespace VerkstanBindings
{
#define ADD_OP_TO_CAT(name, category) \
if (!categories->ContainsKey(category)) \
    categories[category] = gcnew List<String^>(); \
categories[category]->Add(name);

    void OperatorBindingFactory::CreateCategories()
    {
        categories = gcnew Dictionary<String^, List<String^>^>();
#define OPERATOR_CATEGORY_DEFINES 1
#include "operators.hpp"
    }

    ICollection<String^>^ OperatorBindingFactory::GetCategories()
    {
        if (!categories)
            CreateCategories();

        return categories->Keys;
    }

    ICollection<String^>^ OperatorBindingFactory::GetNamesInCategory(String^ category)
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
        Operator* op = new opClass##();             \
        int id;                                     \
        for (int i = 0; i < DB_MAX_OPERATORS; i++)  \
        {                                           \
            if (operators[i] == 0)                  \
            {                                       \
                operators[i] = op;                  \
                id = i;                             \
                break;                              \
            }                                       \
        }                                           \
        List<OperatorBindingProperty^>^ properties = gcnew List<OperatorBindingProperty^>();\
        List<OperatorBindingInput^>^ inputs = gcnew List<OperatorBindingInput^>();\
        ob = gcnew OperatorBinding(opName,  \
                                   id,      \
                                   Constants::OperatorTypes::Texture,   \
                                   properties,  \
                                   inputs);                                              
       
#define ADD_PROP(propName, propType, defaultValue)    \
    properties->Add(gcnew OperatorBindingProperty(properties->Count, propName, Constants::OperatorPropertyTypes::##propType));  \
    op->set##propType##Property(properties->Count - 1, defaultValue);
#define ADD_INPUT(inType) \
    if (inputs->Count > 0 && !inputs[inputs->Count - 1]->Infinite) \
        throw gcnew System::Exception("Unable to add an input because last added input was infinite!"); \
    inputs->Add(gcnew OperatorBindingInput(inputs->Count, Constants::OperatorTypes::##inType, false));
#define ADD_INFINITE_INPUT(inType) \
    if (inputs->Count > 0 && !inputs[inputs->Count - 1]->Infinite) \
        throw gcnew System::Exception("Unable to add an input because last added input was infinite!"); \
    inputs->Add(gcnew OperatorBindingInput(inputs->Count, Constants::OperatorTypes::##inType, true));
#define END_OP() }

    OperatorBinding^ OperatorBindingFactory::Create(String^ name)
    {
        OperatorBinding^ ob;
#define OPERATOR_DEFINES 1
#include "operators.hpp"
        return ob;
     }
}