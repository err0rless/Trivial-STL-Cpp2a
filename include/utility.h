#ifndef _TRIV_UTILITY_H_
#define _TRIV_UTILITY_H_

namespace triv {

template <bool... Conditions>
struct _And {
  static constexpr bool value = (... && Conditions);
};

template <bool... Conditions>
constexpr bool _And_v = _And<Conditions...>::value;

template <bool... Conditions>
struct _Or {
  static constexpr bool value = (... || Conditions);
};

template <bool... Conditions>
constexpr bool _Or_v = _Or<Conditions...>::value;

} // namespace triv

#endif // _TRIV_UTILITY_H_
