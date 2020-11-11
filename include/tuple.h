#ifndef tuple_h
#define tuple_h

#include <utility>
#include <type_traits>
#include "type_traits.h"
#include "utility.h"
#include "concepts.h"

// Internal implementation
namespace triv::__tuple_impl::detail {

// use concepts in header concepts.h
using namespace triv::concepts;

// first_of
// first_of<int, double, float, char>::type -> int
template <typename... Args>
struct first_of {};

template <typename First, typename... Rest>
struct first_of<First, Rest...> { using type = First; };

template <typename... Args>
using first_of_t = typename first_of<Args...>::type;

template <std::size_t... Seq>
using idx_seq = std::index_sequence<Seq...>;

template <std::size_t N>
using make_idx_seq = std::make_index_sequence<N>;

// tuple_range_seq
// tuple_range_seq<3, 6>::type -> std::index_sequence<3, 4, 5, 6>
template <std::size_t N0, std::size_t N1>
struct __tuple_add {
  static constexpr std::size_t value = N0 + N1;
};

template <std::size_t N, typename Seq>
struct __tuple_range_seq_impl {};

template <std::size_t N, std::size_t... Seq>
struct __tuple_range_seq_impl<N, idx_seq<Seq...>> {
  using type = idx_seq<__tuple_add<N, Seq>::value...>;
};

template <std::size_t Begin, std::size_t End>
struct tuple_range_seq {
  using type = 
      typename __tuple_range_seq_impl<Begin, make_idx_seq<(End - Begin) + 1>>::type;
};

template <std::size_t Begin, std::size_t End>
using tuple_range_t = typename tuple_range_seq<Begin, End>::type;

struct tuple_default_construct {
  explicit tuple_default_construct(void) = default; 
};

// pack_expands_to_tuple
template <typename TupleType, typename... Args>
concept pack_expands_to_tuple = 
    sizeof...(Args) == 1 &&
    same_as<TupleType, triv::remove_cvref_t<first_of_t<Args...>>>;

template <typename T>
concept tuple_type = requires { typename T::__tuple_base_t; };

// Tuple initialization concepts
template <typename TupleType, typename... Args>
concept initializable_with = 
    tuple_type<TupleType> &&
    not pack_expands_to_tuple<TupleType, Args...> &&
    TupleType::size == sizeof...(Args);

template <typename TupleType, typename... Args>
concept partial_initializable_with = 
    tuple_type<TupleType> &&
    not pack_expands_to_tuple<TupleType, Args...> &&
    TupleType::size > sizeof...(Args);

// tuple_leaf
// Element class that actually holds its value
template <std::size_t Index, typename T>
class tuple_leaf {
  T data_;
public:
  using value_type = T;
  
  explicit constexpr tuple_leaf(void) 
    requires (not std::is_reference_v<T>)
    : data_{}
  { }

  explicit constexpr tuple_leaf(detail::tuple_default_construct)
    requires (not std::is_reference_v<T>)
    : data_{} 
  { }

  template <typename _T>
  explicit constexpr tuple_leaf(_T&& element) 
    requires (not same_as<triv::remove_cvref_t<_T>, tuple_leaf> && 
              not same_as<_T, detail::tuple_default_construct>)
    : data_{std::forward<_T>(element)}
  { }
  
  constexpr tuple_leaf(const tuple_leaf &) = default;
  constexpr tuple_leaf(tuple_leaf &&) = default;
  
  constexpr       T &get(void)       noexcept { return data_; }
  constexpr const T &get(void) const noexcept { return data_; }
  
  // https://github.com/llvm-mirror/libcxx/blob/master/include/tuple#L334
  template <typename Another>
  constexpr tuple_leaf &operator=(Another&& _t) {
    data_ = std::forward<Another>(_t);
    return *this;
  }
};

// tuple_impl
// https://github.com/llvm-mirror/libcxx/blob/master/include/tuple#L367
template <typename IdxSeq, typename... Types>
class tuple_impl {};

// Actual class that inherites the leafs that hold the values,
// so it can be static casted with base leafs.
template <std::size_t... Index, typename... Types>
class tuple_impl<std::index_sequence<Index...>, Types...>
    : public tuple_leaf<Index, Types>...
{
public:
  // Constructors
  explicit constexpr tuple_impl(void)
    : tuple_leaf<Index, Types>{}...
  { }

  template <typename... Args>
  explicit constexpr tuple_impl(Args&&... args) noexcept
    : tuple_leaf<Index, Types>{ std::forward<Args>(args) }...
  { }

  template <std::size_t... ArgsIndex, 
            std::size_t... DefaultIndex,
            typename... Args>
  explicit constexpr tuple_impl(idx_seq<ArgsIndex...>, 
                                idx_seq<DefaultIndex...>, 
                                Args&&... args)
    requires (sizeof...(ArgsIndex) + sizeof...(DefaultIndex) == sizeof...(Types))
    : tuple_leaf<ArgsIndex, triv::access_t<ArgsIndex, Types...>>{ 
        std::forward<Args>(args) }...
    , tuple_leaf<DefaultIndex, triv::access_t<DefaultIndex, Types...>>{ 
        tuple_default_construct{} }...
  { }
  
  constexpr tuple_impl(const tuple_impl &) = default;
  constexpr tuple_impl(tuple_impl &&) = default;
  
  constexpr tuple_impl &operator=(const tuple_impl &_t) noexcept {
    (tuple_leaf<Index, Types>::operator=(
        static_cast<const tuple_leaf<Index, Types> &>(_t).get()), ...);
    return *this;
  }
};

}

// Interface
namespace triv {

using namespace triv::__tuple_impl;

// tuple
template <typename... Types>
class tuple {
private:
  static constexpr std::size_t size = sizeof...(Types);
  using __tuple_base_t = 
      detail::tuple_impl<detail::make_idx_seq<sizeof...(Types)>, Types...>;
  __tuple_base_t base_;
public:
  explicit constexpr tuple(void) : base_{} {
    static_assert((... && default_constructible<Types>), 
                  "At least one of the Types is not default constructible");
  }

  template <typename... Args>
  explicit constexpr tuple(Args&&... args)
    requires detail::initializable_with<tuple, Args...>
    : base_{ std::forward<Args>(args)... }
  { }

  template <typename... Args, 
            std::size_t n_type = sizeof...(Types),
            std::size_t n_args = sizeof...(Args)>
  explicit constexpr tuple(Args&&... args)
    requires detail::partial_initializable_with<tuple, Args...>
    : base_{ detail::tuple_range_t<0, n_args - 1>(), 
             detail::tuple_range_t<n_args, n_type - 1>(), 
             std::forward<Args>(args)... }
  { }
  
  constexpr tuple(const tuple<Types...> &) = default;
  constexpr tuple(tuple<Types...> &&) = default;
  
  constexpr tuple &operator=(const tuple &_t) {
    base_.operator=(_t.base_);
    return *this;
  }

  // Friends  
  template <std::size_t _Index, typename... _Types> 
  friend inline constexpr auto &get(tuple<_Types...> &Tuple);

  template <std::size_t _Index, typename... _Types> 
  friend inline constexpr const auto &get(const tuple<_Types...> &Tuple);

  template <std::size_t _Index, typename... _Types> 
  friend inline constexpr auto &&get(tuple<_Types...> &&Tuple);

  template <std::size_t _Index, typename... _Types> 
  friend inline constexpr const auto &&get(const tuple<_Types...> &&Tuple);
};

// CTAD guides for tuple
template <typename... Types>
tuple(Types...) -> tuple<Types...>;

template <typename First, typename Second>
tuple(std::pair<First, Second>) -> tuple<First, Second>;

// get (https://github.com/llvm-mirror/libcxx/blob/master/include/tuple#L1005)
template <std::size_t Index, typename... Types>
inline constexpr auto &get(tuple<Types...> &Tuple) {
  using type_at_index = triv::access_t<Index, Types...>;
  using leaf_t = detail::tuple_leaf<Index, type_at_index>;
  return static_cast<leaf_t &>(Tuple.base_).get();
}

template <std::size_t Index, typename... Types>
inline constexpr const auto &get(const tuple<Types...> &Tuple) {
  using type_at_index = triv::access_t<Index, Types...>;
  using leaf_t = detail::tuple_leaf<Index, type_at_index>;
  return static_cast<const leaf_t &>(Tuple.base_).get();
}

template <std::size_t Index, typename... Types>
inline constexpr auto &&get(tuple<Types...> &&Tuple) {
  using type_at_index = triv::access_t<Index, Types...>;
  using leaf_t = detail::tuple_leaf<Index, type_at_index>;
  return static_cast<typename leaf_t::value_type &&>(
           static_cast<leaf_t &&>(Tuple.base_).get());
}

template <std::size_t Index, typename... Types>
inline constexpr const auto &&get(const tuple<Types...> &&Tuple) {
  using type_at_index = triv::access_t<Index, Types...>;
  using leaf_t = detail::tuple_leaf<Index, type_at_index>;
  return static_cast<typename leaf_t::value_type const &&>(
           static_cast<const leaf_t &&>(Tuple.base_).get());
}

// tie (https://github.com/llvm-mirror/libcxx/blob/master/include/tuple#L1115)
template <typename... Args>
constexpr auto tie(Args&... args) -> tuple<Args&...> {
  return tuple<Args&...>(args...);
}

// make_tuple
// https://github.com/llvm-mirror/libcxx/blob/master/include/tuple#L1135
template <typename... Args>
constexpr auto make_tuple(Args&&... args) {
  return tuple<triv::unwrap_ref_decay_t<Args>...>{ std::forward<Args>(args)... };
}

} // namespace triv

#endif /* tuple_h */
