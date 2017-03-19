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


	template<long long first_value, long long second_value>
	struct min {
		static constexpr long long value = first_value < second_value ? first_value : second_value;
	};
	template<long long first_value, long long second_value>
	struct max {
		static constexpr long long value = first_value > second_value ? first_value : second_value;
	};

	// used to remove the need to sort the values to min/max and access ::type
	//NOTE: First type in the list to be big enough to contain the range is picked, so order matters.
	//NOTE: first/second values will are sorted into min/max values, so their ordered doesn't matter.
	template <long long first_value, long long second_value, typename... Ts>
	using alias_base = typename details::integer_t<
		details::max<first_value, second_value>::value,
		details::min<first_value, second_value>::value,
		Ts...>::type;
}

template <long long first_value, long long second_value = 0>
using integer = typename details::alias_base<first_value, second_value
	,unsigned char, char
	,unsigned short, short
	,unsigned int, int
	,unsigned long, long
	,unsigned long long, long long
>;

// least
template <long long first_value, long long second_value = 0>
using int_least = typename details::alias_base<first_value, second_value
	,uint_least8_t, int_least8_t
	,uint_least16_t, int_least16_t
	,uint_least32_t, int_least32_t
	,uint_least64_t, int_least64_t
>;

// fast
template <long long first_value, long long second_value = 0>
using int_fast = typename details::alias_base<first_value, second_value
	,uint_fast8_t, int_fast8_t
	,uint_fast16_t, int_fast16_t
	,uint_fast32_t, int_fast32_t
	,uint_fast64_t, int_fast64_t
>;

#endif//small_int_h
