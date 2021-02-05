
#pragma once

#include "header.h"

void variant_polymoprhism() {

    std::variant<Base, Derived1, Derived2, Derived3> var;

    var = Base{};
    std::visit(CallPrintName{}, var);

    var = Derived1{};
    std::visit(CallPrintName{}, var);

    var = Derived2{};
    std::visit(CallPrintName{}, var);

    var = Derived3{};
    std::visit(CallPrintName{}, var);
};