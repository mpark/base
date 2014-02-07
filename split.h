/* Provides a utility function to split a std::string into
   std::vector<std::string>. */

#pragma once

#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace Base {

  std::vector<std::string> Split(const std::string &str) {
    std::istringstream isstrm(str);
    return std::vector<std::string>(
               std::istream_iterator<std::string>{isstrm},
               std::istream_iterator<std::string>{});
  }

}  // namespace Base

