#pragma once

#include <string>
#include <variant>

template <typename T, typename Error = std::string>
using Exception = std::variant<T, Error>;
