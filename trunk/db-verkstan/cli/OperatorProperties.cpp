#include "cli/OperatorProperties.hpp"

namespace Verkstan 
{ 
    OperatorProperties::OperatorProperties()
    {
        properties = gcnew List<OperatorProperty^>();
        coreCount = 0;
    }

    OperatorProperty^ OperatorProperties::operator[](int index)
    {
        return properties[index];
    }

    int OperatorProperties::Count::get()
    {
        return properties->Count;
    }
    
    int OperatorProperties::CoreCount::get()
    {
        return coreCount;
    }

    List<OperatorProperty^>^ OperatorProperties::GetList()
    {
        return properties;
    }

    void OperatorProperties::Add(String^ name, Constants::OperatorPropertyTypes type, int numberOfValues)
    {
        OperatorProperty^ prop = gcnew OperatorProperty(properties->Count,
                                                        coreCount,
                                                        name,
                                                        type);
        properties->Add(prop);
        coreCount += numberOfValues;
    }

    void OperatorProperties::AddEnum(String^ name, List<String^>^ values)
    {
        OperatorProperty^ prop = gcnew OperatorProperty(properties->Count,
                                                        coreCount,
                                                        name,
                                                        Constants::OperatorPropertyTypes::Enum,
                                                        values);
        properties->Add(prop);
        coreCount += 1;
    }
}