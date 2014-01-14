/* Defines a class which throws an error with a formatted error message.

   For example,

     Base::TThrower<std::runtime_error>(HERE) << "Some error message."; */

#pragma once

#include <exception>
#include <sstream>
#include <type_traits>

#include <Base/code_location.h>

/* Use this macro to throw an exception, and stream some error message. */
#define THROW(exception) ::Base::TThrower<exception>(HERE)

namespace Base {

  /* A class which throws TError after streaming a formatted error message. */
  template <typename TError>
  class TThrower {
    public:

    /* Assert that TError is derived from std::exception. */
    static_assert(std::is_base_of<std::exception, TError>::value,
                  "TError must be derived from std::exception.");

    /* Construct off of a code location and stream it immediately. */
    TThrower(const Base::TCodeLocation &code_location) {
      assert(&code_location);
      Strm << code_location << ": ";
    }

    /* Throw an instance of TError with the formatted error message. */
    [[noreturn]] ~TThrower() noexcept(false) {
      assert(this);
      throw TError(Strm.str());
    }

    /* Stream an arbitrary value to the buffer. */
    template <typename TVal>
    void Write(const TVal &val) {
      assert(this);
      assert(&val);
      Strm << val;
    }

    private:

    /* The buffer for our formatted error message. */
    std::ostringstream Strm;

  };  // TThrower

  /* Stream values to the buffer of the temporary TThrower instance. */
  template <typename TError, typename TVal>
  TThrower<TError> &&operator<<(
        TThrower<TError> &&thrower, const TVal &val) {
    assert(&thrower);
    thrower.Write(val);
    return std::move(thrower);
  }

}  // namespace Base

