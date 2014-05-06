/* Defines a class which represents an optional value. */

#pragma once

#include <cassert>
#include <type_traits>
#include <utility>

namespace Base {

  /* An optional value which may or may not have an instance of TVal.  */
  template <typename TVal_>
  class TOptional {
    public:

    /* Bring TVal into scope for look-up. */
    using TVal = TVal_;

    /* Default-construct to an invalid state. */
    TOptional() : IsValid(false) {}

    /* Move-and-Swap. */
    TOptional(TOptional &&that) : TOptional() {
      if (that) {
        TOptional temp(std::move(*that));
        Swap(temp);
      }  // if
    }

    /* Copy-and-Swap. */
    TOptional(const TOptional &that) : TOptional() {
      if (that) {
        TOptional temp(*that);
        Swap(temp);
      }  // if
    }

    /* Move the value in. */
    TOptional(TVal &&val) : TOptional() {
      Construct(std::move(val));
    }

    /* Copy the value in. */
    TOptional(const TVal &val) : TOptional() {
      Construct(val);
    }

    /* Delegate to Destroy(). */
    ~TOptional() {
      assert(this);
      Destroy();
    }

    /* Move-and-Swap. */
    TOptional &operator=(TOptional &&that) {
      assert(this);
      assert(&that);
      TOptional temp(std::move(that));
      return Swap(temp);
    }

    /* Copy-and-Swap. */
    TOptional &operator=(const TOptional &that) {
      assert(this);
      assert(&that);
      TOptional temp(that);
      return Swap(temp);
    }

    /* Move-and-Swap. */
    TOptional &operator=(TVal &&val) {
      assert(this);
      assert(&val);
      TOptional temp(std::move(val));
      return Swap(temp);
    }

    /* Copy-and-Swap. */
    TOptional &operator=(const TVal &val) {
      assert(this);
      assert(&val);
      TOptional temp(val);
      return Swap(temp);
    }

    /* Returns true iff a valid value exists. */
    explicit operator bool() const {
      assert(this);
      return IsValid;
    }

    /* Returns a const-ref to the value. */
    const TVal &operator*() const {
      assert(this);
      assert(*this);
      return *Get();
    }

    /* Returns a ref to the value. */
    TVal &operator*() {
      assert(this);
      assert(*this);
      return *Get();
    }

    /* Returns a const-pointer to the value. */
    const TVal *operator->() const {
      assert(this);
      assert(*this);
      return Get();
    }

    /* Returns a pointer to the value. */
    TVal *operator->() {
      assert(this);
      assert(*this);
      return Get();
    }

    /* Default-and-Swap. */
    TOptional &Reset() {
      assert(this);
      TOptional temp;
      return Swap(temp);
    }

    /* Swap this and that. */
    TOptional &Swap(TOptional &that) {
      assert(this);
      assert(&that);
      if (*this && that) {
        using std::swap;
        swap(IsValid, that.IsValid);
        swap(**this, *that);
      } else if (*this) {
        that.Construct(std::move(**this));
        Destroy();
      } else if (that) {
        Construct(std::move(*that));
        that.Destroy();
      }  // if
      return *this;
    }

    private:

    /* Interpret the buffer as and const TVal *. */
    const TVal *Get() const {
      assert(this);
      return static_cast<const TVal *>(static_cast<const void *>(&Val));
    }

    /* Interpret the buffer as and TVal *. */
    TVal *Get() {
      assert(this);
      return static_cast<TVal *>(static_cast<void *>(&Val));
    }

    /* Forward a value in and set ourselves to be valid. */
    template <typename TVal>
    void Construct(TVal &&val) {
      assert(this);
      assert(&val);
      assert(!*this);
      new (&Val) std::decay_t<TVal>(std::forward<TVal>(val));
      IsValid = true;
    }

    /* If we have a value, invalidate ourselves and destroy the value. */
    void Destroy() {
      assert(this);
      if (*this) {
        IsValid = false;
        Get()->~TVal();
      }  // if
    }

    /* A flag to indicate our validity. */
    bool IsValid;

    /* Aligned storage for TVal. */
    std::aligned_storage_t<sizeof(TVal)> Val;

  };  // TOptional

}  // namespace Base

