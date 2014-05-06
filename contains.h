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

#pragma once

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace Base {

  /**
   *   Detect if find exists.
   **/

  template <typename TContainer, typename TElem>
  std::is_same<
    decltype(std::declval<TContainer>().find(std::declval<TElem>())),
    typename TContainer::iterator>
  HasFindImpl(void *);

  template <typename, typename>
  std::false_type HasFindImpl(...);

  template <typename TContainer, typename TElem>
  static constexpr bool HasFind() {
    return decltype(HasFindImpl<TContainer, TElem>(nullptr))::value;
  }

  /* Use member find if it exists. */
  template <typename TContainer, typename TKey>
  std::enable_if_t<HasFind<TContainer, TKey>(),
  bool> Contains(const TContainer &container, const TKey &key) {
    return container.find(key) != std::end(container);
  }

  /* Use std::find if no member find exists. */
  template <typename TContainer, typename TVal>
  std::enable_if_t<!HasFind<TContainer, TVal>(),
  bool> Contains(const TContainer &container, const TVal &val) {
    return std::find(std::begin(container),
                     std::end(container),
                     val) != std::end(container);
  }

  template <typename TContainer, typename TUnaryPred>
  bool ContainsIf(const TContainer &container, TUnaryPred &&unary_pred) {
    return std::find_if(std::begin(container),
                        std::end(container),
                        std::forward<TUnaryPred>(unary_pred)) != std::end(container);
  }

}  // namespace Base

