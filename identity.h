/* Defines a class which simply returns the type as identity. */

#pragma once

namespace Base {

  /* Returns a type as identity. This is analogous to the
     std::integral_constant<> defined in the <type_traits> header,
     but operates on types instead of integrals. */
  template <typename T>
  class TIdentity {
    public:

    /* Bring the type T into scope for look-up. */
    using TType = T;

  };  // TIdentity

}  // namespace Base

