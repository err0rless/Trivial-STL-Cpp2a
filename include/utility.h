#ifndef _TRIV_UTILITY_H_
#define _TRIV_UTILITY_H_

namespace triv {

// Alias for index_sequence, make_index_sequence in STL
template <std::size_t... Seq>
using idx_seq = std::index_sequence<Seq...>;

template <std::size_t N>
using make_idx_seq = std::make_index_sequence<N>;

// And, Or
template <bool... Conditions> concept And = (... && Conditions);
template <bool... Conditions> concept Or = (... || Conditions);

// first_of
// first_of<int, double, float, char>::type -> int
template <typename... Args>
struct first_of {};

template <typename First, typename... Rest>
struct first_of<First, Rest...> { using type = First; };

template <typename... Args>
using first_of_t = typename first_of<Args...>::type;

// tuple_range_seq
// tuple_range_seq<3, 6>::type -> std::index_sequence<3, 4, 5, 6>
template <std::size_t N0, std::size_t N1>
struct add { static constexpr std::size_t value = N0 + N1; };

template <std::size_t N, typename Seq>
struct __range_seq_impl {};

template <std::size_t N, std::size_t... Seq>
struct __range_seq_impl<N, std::index_sequence<Seq...>> {
  using type = std::index_sequence<add<N, Seq>::value...>;
};

template <std::size_t Begin, std::size_t End>
struct range_seq {
  using type = 
      typename __range_seq_impl<Begin, std::make_index_sequence<(End - Begin) + 1>>::type;
};

template <std::size_t Begin, std::size_t End>
using range_seq_t = typename range_seq<Begin, End>::type;

} // namespace triv

#endif // _TRIV_UTILITY_H_
