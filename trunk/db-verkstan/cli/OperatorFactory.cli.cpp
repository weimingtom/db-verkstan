#define OPERATOR_HEADERS 1
#include "cli/Operators.hpp"
#undef OPERATOR_HEADERS

#include "cli/OperatorFactory.hpp"
#include "cli/Operator.hpp"
#include "cli/CoreOperator.hpp"
#include "cli/LoadOperator.hpp"
#include "cli/StoreOperator.hpp"
#include "cli/SceneOperator.hpp"
#include "cli/Clip.hpp"
#include "cli/Channel.hpp"
#include "cli/GeneratorClip.hpp"

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
        List<OperatorInput^>^ inputs = gcnew List<OperatorInput^>();\
        op = gcnew CoreOperator(opName,  \
                                opName,  \
                               id,      \
                               Constants::OperatorTypes::##opType,   \
                               inputs);                                              

  
#define ADD_BYTE_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Byte);  \
    op->SetByteProperty(op->Properties->Count - 1, value);
#define ADD_INT_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Int);  \
    op->SetIntProperty(op->Properties->Count - 1, value);
#define ADD_FLOAT_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Float);  \
    op->SetFloatProperty(op->Properties->Count - 1, value);
#define ADD_STRING_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::String);  \
    op->SetStringProperty(op->Properties->Count - 1, value);
#define ADD_TEXT_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Text);  \
    op->SetStringProperty(op->Properties->Count - 1, value);
#define ADD_COLOR_PROP(name, r, g, b) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Color);  \
    op->SetColorProperty(op->Properties->Count - 1, gcnew Color(r, g, b));
#define ADD_VECTOR_PROP(name, x, y, z) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Vector);  \
    op->SetVectorProperty(op->Properties->Count - 1, gcnew Vector(x, y, z));
#define ADD_ENUM_PROP(name, enumValues, value) \
    String^ tmpEnumValues = gcnew String(enumValues); \
    array<String^>^ splitted = tmpEnumValues->Split(gcnew array<Char>{','}); \
    List<String^>^ enumValuesList = gcnew List<String^>();  \
    for (int enumIndex = 0; enumIndex < splitted->Length; enumIndex++) \
        enumValuesList->Add(splitted[enumIndex]);   \
    op->AddEnumProperty(name, enumValuesList);  \
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
    op->SetByteProperty(op->Properties->Count - 1, defaultValue);
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
            op = gcnew StoreOperator("Store");
            op->AddProperty("Name", Constants::OperatorPropertyTypes::String);
        }

        if (name == "Load")
        {
            op = gcnew LoadOperator("Load");
            op->AddProperty("Name", Constants::OperatorPropertyTypes::String);
        }
   
        if (name == "Scene")
        {
            SceneOperator^ so = gcnew SceneOperator(op);
            Channel^ channel1 = gcnew Channel(so);
            so->AddChannel(channel1);
            GeneratorClip^ c1 = gcnew GeneratorClip();
            c1->Start = 0;
            c1->End = 256*40;
            c1->Period = DB_TICKS_PER_BEAT;
            c1->Type = Constants::GeneratorClipTypes::Sine;
            channel1->AddClip(c1);

            Channel^ channel2 = gcnew Channel(so);
            so->AddChannel(channel2);
            GeneratorClip^ c2 = gcnew GeneratorClip();
            c2->Start = 0;
            c2->End = 256*40;
            c2->Period = DB_TICKS_PER_BEAT * 4;
            c2->Type = Constants::GeneratorClipTypes::Sine;
            channel2->AddClip(c2);

            Channel^ channel3 = gcnew Channel(so);
            so->AddChannel(channel3);
            GeneratorClip^ c3 = gcnew GeneratorClip();
            c3->Start = 0;
            c3->End = 256*40;
            c3->Period = DB_TICKS_PER_BEAT;
            c3->Type = Constants::GeneratorClipTypes::RampUp;
            channel3->AddClip(c3);

            Channel^ channel4 = gcnew Channel(so);
            so->AddChannel(channel4);
            GeneratorClip^ c4 = gcnew GeneratorClip();
            c4->Start = 0;
            c4->End = 256*40;
            c4->Period = DB_TICKS_PER_BEAT;
            c4->Type = Constants::GeneratorClipTypes::RampDown;
            channel4->AddClip(c4);
          
            return so;
        }
   
        return op;
     }
}