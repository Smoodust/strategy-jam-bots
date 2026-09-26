#pragma once

#include <string_view>

namespace sjb {

// Project version, taken from project() in CMakeLists.txt.
std::string_view version() noexcept;

}  // namespace sjb
