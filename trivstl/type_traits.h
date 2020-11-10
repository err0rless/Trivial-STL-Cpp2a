#ifndef type_traits_h
#define type_traits_h

namespace triv {

// unwrap_reference, unwrap_ref_decay
// https://en.cppreference.com/w/cpp/utility/functional/unwrap_reference
// U& if T is std::reference_wrapper<U>; T otherwise
// U& if std::decay_t<T> is std::reference_wrapper<U>; std::decay_t<T> otherwise
template <typename T>
struct unwrap_reference { using type = T; };

template <typename U>
struct unwrap_reference<std::reference_wrapper<U>> {
  using type = U&;
};

template <typename T>
struct unwrap_ref_decay : unwrap_reference<std::decay_t<T>> {};

template <typename T>
using unwrap_reference_t = typename unwrap_reference<T>::type;

template <typename T>
using unwrap_ref_decay_t = typename unwrap_ref_decay<T>::type;

// remove_cvref
template <typename T>
struct remove_cvref : std::remove_cv<std::remove_reference_t<T>> { };

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

// access_type_index
template <std::size_t Index, typename... Args>
struct access_type_index {};

template <std::size_t Index, typename T, typename... Types>
struct access_type_index<Index, T, Types...> {
  using type = typename access_type_index<Index - 1, Types...>::type;
};

template <typename T, typename... Types>
struct access_type_index<0, T, Types...> {
  using type = T;
};

template <std::size_t Index, typename... Types>
using access_t = typename access_type_index<Index, Types...>::type;

}

#endif /* type_traits_h */
