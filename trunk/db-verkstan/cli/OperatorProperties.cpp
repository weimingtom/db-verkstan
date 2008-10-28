#include "cli/OperatorProperties.hpp"

namespace Verkstan 
{ 
    OperatorProperties::OperatorProperties()
    {
        properties = gcnew List<OperatorProperty^>();
    }

    OperatorProperty^ OperatorProperties::operator[](int index)
    {
        return properties[index];
    }

    int OperatorProperties::Count::get()
    {
        return properties->Count;
    }

    List<OperatorProperty^>^ OperatorProperties::GetList()
    {
        return properties;
    }

    void OperatorProperties::Add(String^ name, Constants::OperatorPropertyTypes type)
    {
        OperatorProperty^ prop = gcnew OperatorProperty(properties->Count,
                                                        name,
                                                        type);
        properties->Add(prop);
    }

    void OperatorProperties::AddEnum(String^ name, List<String^>^ values)
    {
        OperatorProperty^ prop = gcnew OperatorProperty(properties->Count,
                                                        name,
                                                        Constants::OperatorPropertyTypes::Enum,
                                                        values);
        properties->Add(prop);
    }
}