#ifndef small_int_h
#define small_int_h


#include <type_traits>
#include <limits>


/*
small_int will automatically choose at compile time the smallest integer type that can contain a given range.
*/
template<long long max_value, long long min_value = 0, typename Enable = void>
struct small_int_t {
	using type = size_t;
	static_assert(max_value > min_value, "small_int can't contain the value range");
};




// char
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 &&
	min_value >= std::numeric_limits<char>::min() &&
	max_value <= std::numeric_limits<char>::max()
	)>::type> {
	using type = char;
};

// unsigned char
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value <= std::numeric_limits<unsigned char>::max()
	)>::type> {
	using type = unsigned char;
};




// short
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 && ((
		min_value < std::numeric_limits<char>::min() &&
		min_value >= std::numeric_limits<short>::min())
		|| (
		max_value > std::numeric_limits<char>::max() &&
		max_value <= std::numeric_limits<short>::max())
	))>::type> {
	using type = short;
};

// unsigned short
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value > std::numeric_limits<unsigned char>::max() &&
	max_value <= std::numeric_limits<unsigned short>::max()
	)>::type> {
	using type = unsigned short;
};




// int
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 && ((
		min_value < std::numeric_limits<short>::min() &&
		min_value >= std::numeric_limits<int>::min())
		|| (
		max_value > std::numeric_limits<short>::max() &&
		max_value <= std::numeric_limits<int>::max())
	))>::type> {
	using type = int;
};

// unsigned int
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value > std::numeric_limits<unsigned short>::max() &&
	max_value <= std::numeric_limits<unsigned int>::max()
	)>::type> {
	using type = unsigned int;
};




// long
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 && ((
		min_value < std::numeric_limits<int>::min() &&
		min_value >= std::numeric_limits<long>::min())
		|| (
		max_value > std::numeric_limits<int>::max() &&
		max_value <= std::numeric_limits<long>::max())
	))>::type> {
	using type = long;
};

// unsigned long
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value > std::numeric_limits<unsigned int>::max() &&
	max_value <= std::numeric_limits<unsigned long>::max()
	)>::type> {
	using type = unsigned long;
};




// long long
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 && ((
		min_value < std::numeric_limits<long>::min() &&
		min_value >= std::numeric_limits<long long>::min())
		|| (
		max_value > std::numeric_limits<long>::max() &&
		max_value <= std::numeric_limits<long long>::max())
	))>::type> {
	using type = long long;
};

// unsigned long long
//NOTE: can't map values greater than long long's max
template<long long max_value, long long min_value>
struct small_int_t<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value > std::numeric_limits<unsigned long>::max() &&
	max_value <= std::numeric_limits<long long>::max()
	)>::type> {
	using type = unsigned long long;
};




// Alias template to remove the need to access small_int_t::type
template<long long max_value, long long min_value = 0>
using small_int = typename small_int_t<max_value, min_value>::type;


#endif//small_int_h