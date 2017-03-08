#ifndef small_int_h
#define small_int_h


#include <type_traits>
#include <limits>


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
template <long long max_value, long long min_value = 0>
using integer = typename details::integer_t<max_value, min_value
	,unsigned char, char
	,unsigned short, short
	,unsigned int, int
	,unsigned long, long
	,unsigned long long, long long
>::type;


#endif//small_int_h
