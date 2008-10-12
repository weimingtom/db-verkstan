#define OPERATOR_HEADERS 1
#include "cli/Operators.hpp"
#undef OPERATOR_HEADERS

#include "cli/OperatorFactory.hpp"
#include "cli/Operators/CoreOperator.hpp"
#include "cli/Operators/NameOperator.hpp"

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
            categories["Misc"] = gcnew List<String^>();
        categories["Misc"]->Add("Name");
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
        VerkstanCore::Operator* op = new opClass##();\
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
        List<OperatorProperty^>^ properties = gcnew List<OperatorProperty^>();\
        List<OperatorInput^>^ inputs = gcnew List<OperatorInput^>();\
        ob = gcnew CoreOperator(opName,  \
                               id,      \
                               Constants::OperatorTypes::Texture,   \
                               properties,  \
                               inputs);                                              
       
#define ADD_PROP(propName, propType, defaultValue)    \
    properties->Add(gcnew OperatorProperty(properties->Count, propName, Constants::OperatorPropertyTypes::##propType));  \
    ob->Set##propType##Property(properties->Count - 1, defaultValue);
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
        Operator^ ob;
#define OPERATOR_DEFINES 1
#include "cli/Operators.hpp"
#undef OPERATOR_DEFINES

        if (name == "Name")
        {
            List<OperatorProperty^>^ properties = gcnew List<OperatorProperty^>();\
            ob = gcnew NameOperator(properties);
        }

        return ob;
     }

    void OperatorFactory::Delete(Operator^ op)
    {
        //delete operators[operatorBinding->Id];
        //operators[operatorBinding->Id] = 0;
    }
}