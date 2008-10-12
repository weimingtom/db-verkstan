#include "cli/Operators/NameOperator.hpp"
#include "cli/Operators/ReferenceOperator.hpp"

using namespace System;
#using <mscorlib.dll>
using namespace System::Collections::Generic;

namespace Verkstan
{
    public ref class NameAndReferenceOperatorManager
    {
    public:
        static void AddNameOperator(NameOperator^ nameOperator);
        static void RemoveNameOperator(NameOperator^ nameOperator);
        static void AddReferenceOperator(ReferenceOperator^ referenceOperator);
        static void RemoveReferenceOperator(ReferenceOperator^ referenceOperator);
        static NameOperator^ FindNameOperator(String^ name);
        static void RefreshReferenceOperators();
        static void NameOperatorDirty(NameOperator^ nameOperator);

    private:
        static List<NameOperator^>^ nameOperators = gcnew List<NameOperator^>();
        static List<ReferenceOperator^>^ referenceOperators = gcnew List<ReferenceOperator^>();
    };
}