#ifndef small_int_h
#define small_int_h


#include <type_traits>
#include <limits>


/*
small_int will automatically choose at compile time the smallest integer type that can contain a given range.
*/
template<typename T>
struct small_int_base
{
	static_assert(std::is_integral<T>::value,
		"small_int_base can only be instantiated with an integral type.");

	constexpr small_int_base(T value) : v(std::move(value)) {}
	

	T& operator=(T other) {
		v = other;
		return v;
	}
	T& operator=(T&& other) {
		v = other;
		return v;
	}

	T v;

	// Convert to the underlying value
	operator T& () noexcept { return v; }
	constexpr operator const T& () const noexcept { return v; }

	// Access members of the underlying type
	T* operator->() { return &value; }
	constexpr const T* operator->() const { return &value; }
};


template<long long max_value, long long min_value = 0, typename Enable = void>
struct small_int : public small_int_base<size_t> {
	using small_int_base::small_int_base;
	static_assert(max_value > min_value, "small_int can't contain the value range");
};




// char
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 &&
	min_value >= std::numeric_limits<char>::min() &&
	max_value <= std::numeric_limits<char>::max()
	)>::type> :
	public small_int_base<char> {
	using small_int_base::small_int_base;
};

// unsigned char
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value <= std::numeric_limits<unsigned char>::max()
	)>::type> :
	public small_int_base<unsigned char> {
	using small_int_base::small_int_base;
};




// short
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 && ((
		min_value < std::numeric_limits<char>::min() &&
		min_value >= std::numeric_limits<short>::min())
		|| (
		max_value > std::numeric_limits<char>::max() &&
		max_value <= std::numeric_limits<short>::max())
	))>::type> :
	public small_int_base<short> {
	using small_int_base::small_int_base;
};

// unsigned short
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value > std::numeric_limits<unsigned char>::max() &&
	max_value <= std::numeric_limits<unsigned short>::max()
	)>::type> :
	public small_int_base<unsigned short> {
	using small_int_base::small_int_base;
};




// int
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 && ((
		min_value < std::numeric_limits<short>::min() &&
		min_value >= std::numeric_limits<int>::min())
		|| (
		max_value > std::numeric_limits<short>::max() &&
		max_value <= std::numeric_limits<int>::max())
	))>::type> :
	public small_int_base<int> {
	using small_int_base::small_int_base;
};

// unsigned int
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value > std::numeric_limits<unsigned short>::max() &&
	max_value <= std::numeric_limits<unsigned int>::max()
	)>::type> :
	public small_int_base<unsigned int> {
	using small_int_base::small_int_base;
};




// long
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 && ((
		min_value < std::numeric_limits<int>::min() &&
		min_value >= std::numeric_limits<long>::min())
		|| (
		max_value > std::numeric_limits<int>::max() &&
		max_value <= std::numeric_limits<long>::max())
	))>::type> :
	public small_int_base<long> {
	using small_int_base::small_int_base;
};

// unsigned long
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value > std::numeric_limits<unsigned int>::max() &&
	max_value <= std::numeric_limits<unsigned long>::max()
	)>::type> :
	public small_int_base<unsigned long> {
	using small_int_base::small_int_base;
};




// long long
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value < 0 && ((
		min_value < std::numeric_limits<long>::min() &&
		min_value >= std::numeric_limits<long long>::min())
		|| (
		max_value > std::numeric_limits<long>::max() &&
		max_value <= std::numeric_limits<long long>::max())
	))>::type> :
	public small_int_base<long long> {
	using small_int_base::small_int_base;
};

// unsigned long long
//NOTE: can't map values greater than long long's max
template<long long max_value, long long min_value>
struct small_int<max_value, min_value, typename std::enable_if<(
	max_value > min_value &&
	min_value >= 0 &&
	max_value > std::numeric_limits<unsigned long>::max() &&
	max_value <= std::numeric_limits<long long>::max()
	)>::type> :
	public small_int_base<unsigned long long> {
	using small_int_base::small_int_base;
};


// Marco for directly using the underlying type
#define EXPAND(x) x
#define GET_SMALL_INT_MACRO(_1, _2, NAME, ...) NAME
#define SMALL_INT(...) EXPAND(GET_SMALL_INT_MACRO(__VA_ARGS__, SMALL_INT_2, SMALL_INT_1)(__VA_ARGS__))

#define SMALL_INT_1(max_value) decltype(small_int<max_value>::v)
#define SMALL_INT_2(max_value, min_value) decltype(small_int<max_value, min_value>::v)

#endif//small_int_h