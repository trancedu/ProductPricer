#pragma once
#include <variant>
#include "Data.h"

using ProductVariant = std::variant<
    StockData,
    CallableBondData,
    ConvertibleBondData
>; 