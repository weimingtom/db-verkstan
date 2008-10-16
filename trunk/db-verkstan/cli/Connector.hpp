#pragma once

#include "cli/Operator.hpp"

using namespace System;

namespace Verkstan
{
    public ref class Connector
    {
    public:
        static void Connect(Operator^ sender, Operator^ receiver);
        static void Disconnect(Operator^ op);
    };
}