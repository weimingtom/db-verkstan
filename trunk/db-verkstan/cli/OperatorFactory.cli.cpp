#define OPERATOR_HEADERS 1
#include "cli/Operators.hpp"
#undef OPERATOR_HEADERS

#include "cli/OperatorFactory.hpp"
#include "cli/Operator.hpp"
#include "cli/CoreOperator.hpp"
#include "cli/LoadOperator.hpp"
#include "cli/StoreOperator.hpp"
#include "cli/SceneOperator.hpp"
#include "cli/ClipFactory.hpp"
#include "cli/Clip.hpp"

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
        Core::Operator* o = new Core::opClass##();  \
        int id;                                     \
        for (int i = 0; i < DB_MAX_OPERATORS; i++)  \
        {                                           \
        if (Core::operators[i] == 0)                \
            {                                       \
            Core::operators[i] = o;                 \
                id = i;                             \
                break;                              \
            }                                       \
        }                                           \
        OperatorProperties^ properties = gcnew OperatorProperties();\
        List<OperatorInput^>^ inputs = gcnew List<OperatorInput^>();\
        op = gcnew CoreOperator(opName,  \
                                opName,  \
                               id,      \
                               Constants::OperatorTypes::##opType,   \
                               properties,  \
                               inputs);                                              

  
#define ADD_BYTE_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::Byte);  \
    op->SetByteProperty(properties->Count - 1, value);
#define ADD_INT_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::Int);  \
    op->SetIntProperty(properties->Count - 1, value);
#define ADD_FLOAT_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::Float);  \
    op->SetFloatProperty(properties->Count - 1, value);
#define ADD_STRING_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::String);  \
    op->SetStringProperty(properties->Count - 1, value);
#define ADD_TEXT_PROP(name, value) \
    properties->Add(name, Constants::OperatorPropertyTypes::Text);  \
    op->SetStringProperty(properties->Count - 1, value);
#define ADD_COLOR_PROP(name, r, g, b) \
    properties->Add(name, Constants::OperatorPropertyTypes::Color);  \
    op->SetColorProperty(properties->Count - 1, gcnew Color(r, g, b));
#define ADD_VECTOR_PROP(name, x, y, z) \
    properties->Add(name, Constants::OperatorPropertyTypes::Vector);  \
    op->SetVectorProperty(properties->Count - 1, gcnew Vector(x, y, z));
#define ADD_ENUM_PROP(name, enumValues, value) \
    String^ tmpEnumValues = gcnew String(enumValues); \
    array<String^>^ splitted = tmpEnumValues->Split(gcnew array<Char>{','}); \
    List<String^>^ enumValuesList = gcnew List<String^>();  \
    for (int enumIndex = 0; enumIndex < splitted->Length; enumIndex++) \
        enumValuesList->Add(splitted[enumIndex]);   \
    properties->AddEnum(name, enumValuesList);  \
    int defaultValue;   \
    String^ defaultValueString = gcnew String(value);   \
    for (int listIndex = 0; listIndex < enumValuesList->Count; listIndex++) \
    {   \
        if (enumValuesList[listIndex] == defaultValueString)   \
        {   \
            defaultValue = listIndex;\
            break;\
        }\
    }\
    op->SetByteProperty(properties->Count - 1, defaultValue);
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
            properties->Add("Name", Constants::OperatorPropertyTypes::String);
            op = gcnew StoreOperator("Store",properties);
        }

        if (name == "Load")
        {
            OperatorProperties^ properties = gcnew OperatorProperties();
            properties->Add("Name", Constants::OperatorPropertyTypes::String);
            op = gcnew LoadOperator("Load",properties);
        }

        /*
        if (name == "Scene")
        {
            Clip^ c1 = ClipFactory::Create("Sine");
            c1->Channel = 0;
            c1->Start = 0;
            c1->End = 256*6;

            Clip^ c2 = ClipFactory::Create("Sine");
            c2->Channel = 0;
            c2->Start = 256*12;
            c2->End = 256*18;

            SceneOperator^ so = gcnew SceneOperator(op);
            so->AddClip(c1);
            so->AddClip(c2);
            return so;
        }

        if (name == "Transform Model")
        {
             Core::Operator* coreOp = op->getOperator();
             coreOp->properties[6].channel = 0;
             coreOp->properties[6].amplify = 2.0f;
             coreOp->properties[4].channel = 0;
             coreOp->properties[4].amplify = 2.0f;
        }*/

        return op;
     }
}