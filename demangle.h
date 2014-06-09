/* Demangles the name of a C++ type using `abi::__cxa_demangle`.

   If you want the name of a static type, use the templatized version.
   Use the version that takes `std::type_info` if you want the name of a
   dynamic type of a polymorphic type.

   __NOTE:__ The top-level ref/cv-qualifiers ignored because that's
             the behavior of `typeid`.

   Examples:

     // Static type.
     Demangle<int>();  // "int"
     Demangle(typeid(int));  // "int"

     int x;
     Demangle<decltype(x)>();  // "int"
     Demangle(typeid(x));  // "int"

     // Dynamic type.
     struct TBase {
       virtual ~TBase() {}
     };

     struct TDerived : TBase {};

     const TBase &base = TDerived{};
     Demangle<decltype(base)>();  // "TBase"
     Demangle(typeid(base));  // "TDerived"

     // Top-level ref/cv-qualifiers ignored
     const int &y = 42;
     Demangle<int>();  // "int"
     Demangle<const int>();  // "int"
     Demangle(typeid(y));  // "int"
*/

#pragma once

#include <memory>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <map>

#include <cxxabi.h>

namespace Base {

  /* Use __cxa_demangle to demangle a mangled name.
     Since abi::__cxa_demangle returns a `char *` to a heap-allocated string,
     we cache based on the `type_index`. */
  inline const char *Demangle(const std::type_info &type_info) {
    static std::map<std::type_index, std::unique_ptr<char, void (*)(void *)>> cache;
    auto type_index = std::type_index(type_info);
    auto iter = cache.find(type_index);
    if (iter != std::end(cache)) {
      return iter->second.get();
    }  // if
    int status;
    std::unique_ptr<char, void (*)(void *)> result(
        abi::__cxa_demangle(type_info.name(), nullptr, nullptr, &status),
        std::free);
    if (status != 0) {
      throw std::runtime_error("Demangle failed.");
    }  // if
    std::tie(iter, std::ignore) = cache.emplace(type_index, std::move(result));
    return iter->second.get();
  }

  /* We store the demangled name of `T` as a static local variable.
     We can cache the result here since the demangled name of a type `T` does
     not change and each `T` gets its own template instantiation and therefore
     its own static local variable.

     __Note:__  `typeid` ignores top-level ref/cv-qualifiers. */
  template <typename T>
  inline const char *Demangle() {
    static const char *result = Demangle(typeid(T));
    return result;
  }

}  // namespace Base
