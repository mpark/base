/* Defines a class to represent a code location within the body of source code.
   This is useful for reporting errors and for logging. */

#pragma once

#include <cassert>
#include <cstddef>
#include <ostream>

/* Use this macro to represent the current location in the code. */
#define HERE ::Base::TCodeLocation(__FILE__, __LINE__)

namespace Base {

  /* A code location (file and line) within the body of source code. */
  class TCodeLocation {
    public:

    /* Do-little. */
    TCodeLocation(const char *file, std::size_t line)
        : File(file), Line(line) {
      assert(File);
      assert(Line > 0);
    }

    /* Stream out a human-readable version of our state. */
    void Write(std::ostream &strm) const {
      assert(this);
      assert(&strm);
      strm << '[' << File << ": " << Line << ']';
    }

    private:

    /* Never null. */
    const char *File;

    /* Always > 0. */
    std::size_t Line;

  };  // TCodeLocation

  /* Standard stream inserter for Base::TCodeLocation. */
  inline std::ostream &operator<<(
        std::ostream &strm,
        const TCodeLocation &that) {
    assert(&strm);
    assert(&that);
    that.Write(strm);
    return strm;
  }

}  // namespace Base

