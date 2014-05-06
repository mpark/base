/* Defines a class to be thrown to denote that a functionality is not
   implemented yet. */

#pragma once

#include <stdexcept>

namespace Base {

  /* Throw this exception when something isn't implemented yet.

     For example, using <base/thrower.h>:

       THROW(Base::TNotImplementedError) << __func__ << " is not implemented.";
  */
  class TNotImplementedError : public std::runtime_error {
    public:

    /* Convenience type alias. */
    using TSuper = std::runtime_error;

    /* Inherit std::runtime_error's constructor. */
    using TSuper::TSuper;

  };  // TNotImplementedError

}  // namespace Base

