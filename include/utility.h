#ifndef _TRIV_UTILITY_H_
#define _TRIV_UTILITY_H_

#include "tuple.h"

namespace triv {

template <bool... Conditions>
struct all {
  static constexpr bool value = (... && Conditions);
};

template <bool... Conditions>
struct one_of {
  static constexpr bool value = (... || Conditions);
};

} // namespace triv

#endif // _TRIV_UTILITY_H_
