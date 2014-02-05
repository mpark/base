/* A utility function to kill the 'container.find(val) != std::end(container)'
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

#include <iterator>

#include <Std/decltype_auto.h>

#pragma once

namespace Base {

  template <typename TContainer, typename TVal>
  auto Contains(const TContainer &container, const TVal &val)
      DECLTYPE_AUTO(container.find(val) != std::end(container));

  template <typename TContainer, typename TVal>
  auto Contains(const TContainer &container, const TVal &val)
      DECLTYPE_AUTO(std::find(std::begin(container),
                              std::end(container),
                              val));

}  // namespace Base

