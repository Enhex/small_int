#include "small_int.h"
#include <iostream>

using namespace std;

template<long long max, long long min = 0>
void print_int()
{
	cout << "(max=" << max << ", min=" << min << ") -> " << typeid(integer<max, min>).name() << " " << sizeof(integer<max, min>) << endl;
}

template<unsigned long long max>
void print_uint()
{
	cout << "max=" << max << " -> " << typeid(integer<max>).name() << " " << sizeof(integer<max>) << endl;
}

#define PRINT_TYPE_UINT(type) cout << "(" << #type << ") "; print_uint<numeric_limits<type>::max()>()
#define PRINT_TYPE_INT(type) cout << "(" << #type << ") "; print_int<numeric_limits<type>::max(), numeric_limits<type>::min()>()
#define PRINT_TYPE_INT_MIN(type) cout << "(" << #type << ") "; print_int<0, numeric_limits<type>::min()>()

int main()
{
	// unsigned
	cout << endl << "unsigned:" << endl;
	print_uint<1>();
	PRINT_TYPE_UINT(unsigned char);
	PRINT_TYPE_UINT(unsigned short);
	PRINT_TYPE_UINT(unsigned int);
	PRINT_TYPE_UINT(unsigned long);
	//PRINT_TYPE_UINT(unsigned long long);	// Too big for max_value

	// signed
	cout << endl << "signed:" << endl;
	print_int<-1, -2>();
	print_int<0, -1>();
	print_int<1, -1>();
	print_int<1, -1000>();
	cout << endl;
	PRINT_TYPE_INT(char);
	PRINT_TYPE_INT(short);
	PRINT_TYPE_INT(int);
	PRINT_TYPE_INT(long);
	PRINT_TYPE_INT(long long);

	cout << endl << "signed (max=0):" << endl;
	PRINT_TYPE_INT_MIN(char);
	PRINT_TYPE_INT_MIN(short);
	PRINT_TYPE_INT_MIN(int);
	PRINT_TYPE_INT_MIN(long);
	PRINT_TYPE_INT_MIN(long long);

	// constexpr
	constexpr unsigned ce = 10;
	integer<ce> a = ce;
}