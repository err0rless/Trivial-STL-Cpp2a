#ifndef utility_h
#define utility_h

#include "tuple.h"

namespace ext {

template <bool... Conditions>
struct all {
  static constexpr bool value = (... && Conditions);
};

template <bool... Conditions>
struct one_of {
  static constexpr bool value = (... || Conditions);
};

} // namespace ext

#endif /* utility_h */
