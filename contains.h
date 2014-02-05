/* A utility function to kill the 'container.find(val) != std::end(container)

   pattern. Use this function to check if a container contains some value.

   For example,

     void Foo(const std::map<int> &x) {
       if (Contains(x, 15)) {
         // Do something that you don't care about the value for.
       }  // if
     }

   Note that, if you do care about the value though. You'll still want to use
   'find' to keep the iterator. Since a sequence of Contains then find will
   perform 2 searches rather than one.

   For example,

     void Foo(const std::map<int> &x) {
       auto iter = x.find(15);
       if (iter != std::end(x)) {
         // Do something with iter->second.
       }  // if
     }

   */

#include <algorithm>
#include <iterator>
#include <map>
#include <set>

#include <Std/decltype_auto.h>
#include <Std/type_traits.h>

#pragma once

namespace Base {

  /**
   *   Detect if find exists.
   **/

  template <typename TContainer>
  std::is_same<
    decltype(std::declval<TContainer>().find(
            std::declval<typename TContainer::key_type>())),
    typename TContainer::iterator>
  HasFindImpl(void *);

  template <typename>
  std::false_type HasFindImpl(...);

  template <typename TContainer>
  static constexpr bool HasFind() {
    return decltype(HasFindImpl<TContainer>(nullptr))::value;
  }

  /* Use member find if it exists. */
  template <typename TContainer>
  std::enable_if_t<HasFind<TContainer>(),
  bool> Contains(
      const TContainer &container,
      const typename TContainer::key_type &key) {
    return container.find(key) != std::end(container);
  }

  /* Use std::find if no member find exists. */
  template <typename TContainer>
  std::enable_if_t<!HasFind<TContainer>(),
  bool> Contains(
      const TContainer &container,
      const typename TContainer::value_type &val) {
    return std::find(std::begin(container),
                     std::end(container),
                     val) != std::end(container);
  }

}  // namespace Base

