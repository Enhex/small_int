#ifndef small_int_h
#define small_int_h


#include <type_traits>
#include <limits>
#include <cstdint>


/*
automatically choose at compile time the smallest integer type that can contain a given range.
*/
namespace details
{
	template<typename T>
	struct integer_tag {
		using type = T;
	};

	template<long long max_value, long long min_value, typename...>
	struct integer_t {
		static_assert(max_value > min_value, "can't contain the value range");
	};

	template<long long max_value, long long min_value, typename T, typename... Ts>
	struct integer_t<max_value, min_value, T, Ts...> : std::conditional_t<(
			max_value > min_value &&
			max_value <= std::numeric_limits<T>::max() &&
			min_value >= std::numeric_limits<T>::min() &&
			(std::is_signed<T>::value || (max_value >= 0 && min_value >= 0))
		),
		integer_tag<T>, integer_t<max_value, min_value, Ts...>> {
	};
}

// used to remove the need to access ::type
//NOTE: First type in the list to be big enough to contain the range is picked, so order matters.
template <long long max_value, long long min_value = 0>
using integer = typename details::integer_t<max_value, min_value
	,unsigned char, char
	,unsigned short, short
	,unsigned int, int
	,unsigned long, long
	,unsigned long long, long long
>::type;

// least
template <long long max_value, long long min_value = 0>
using int_least = typename details::integer_t<max_value, min_value
	,uint_least8_t, int_least8_t
	,uint_least16_t, int_least16_t
	,uint_least32_t, int_least32_t
	,uint_least64_t, int_least64_t
>::type;

// fast
template <long long max_value, long long min_value = 0>
using int_fast = typename details::integer_t<max_value, min_value
	,uint_fast8_t, int_fast8_t
	,uint_fast16_t, int_fast16_t
	,uint_fast32_t, int_fast32_t
	,uint_fast64_t, int_fast64_t
>::type;

#endif//small_int_h
