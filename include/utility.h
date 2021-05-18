#ifndef _TRIV_UTILITY_H_
#define _TRIV_UTILITY_H_

namespace triv {

template <bool... Conditions> concept And = (... && Conditions);
template <bool... Conditions> concept Or = (... || Conditions);

} // namespace triv

#endif // _TRIV_UTILITY_H_
