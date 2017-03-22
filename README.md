# small_int
Automatically select the smallest integer type that can contain a given range at compile time

## Example
```C++
#include <small_int.h>
int main()
{
	// evaluates into unsigned char, assuming it's the smallest integer type that can represent the value range [0,100]
	integer<100> i;
	// evaluates into int_least8_t
	int_least<-100, 100> l;
	// evaluates into int_fast16_t
	int_fast<1, -1000> f;
}

```

For more examples, see [this](small_int/Source.cpp). Possible output:
```
unsigned:
max=1 -> unsigned char 1
(unsigned char) max=255 -> unsigned char 1
(unsigned short) max=65535 -> unsigned short 2
(unsigned int) max=4294967295 -> unsigned int 4
(unsigned long) max=4294967295 -> unsigned int 4

signed:
(max=-1, min=-2) -> char 1
(max=0, min=-1) -> char 1
(max=1, min=-1) -> char 1
(max=1, min=-1000) -> short 2

(char) (max=127, min=-128) -> char 1
(short) (max=32767, min=-32768) -> short 2
(int) (max=2147483647, min=-2147483648) -> int 4
(long) (max=2147483647, min=-2147483648) -> int 4
(long long) (max=9223372036854775807, min=-9223372036854775808) -> __int64 8

signed (max=0):
(char) (max=0, min=-128) -> char 1
(short) (max=0, min=-32768) -> short 2
(int) (max=0, min=-2147483648) -> int 4
(long) (max=0, min=-2147483648) -> int 4
(long long) (max=0, min=-9223372036854775808) -> __int64 8

least (1000) -> unsigned short
fast (1000) -> unsigned int

range -> char
flipped_range -> char
```
