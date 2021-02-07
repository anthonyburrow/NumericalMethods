#pragma once

#include <string>

#include "quadratic.hpp"

namespace mylib {
    mylib::quad_params read_params(const std::string &filename);
}
