/*
The MIT License (MIT)

Copyright (c) 2017 Yehonatan Ballas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

	//TODO C++17: use auto non-type template parameter for values
	template<long long max_value, long long min_value, typename...>
	struct integer_t {
		static_assert(true, "can't contain the value range");
	};

	template<long long max_value, long long min_value, typename T, typename... Ts>
	struct integer_t<max_value, min_value, T, Ts...> : std::conditional_t<(
			// check if inside the integer type's range
			max_value <= std::numeric_limits<T>::max() &&
			min_value >= std::numeric_limits<T>::min() &&
			// if integer type is unsigned, make sure the values aren't negative
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
