#ifndef _CONCEPTS_H_
#define _CONCEPTS_H_

#include <type_traits>

namespace ext {
inline namespace concepts {

// same_as
template <typename T, typename U>
concept same_as = std::is_same_v<T, U> && std::is_same_v<U, T>;

// default_constructible
template <typename T>
concept default_constructible = std::is_default_constructible_v<T>;

}
}

#endif
