# small_int
Automatically select the smallest integer type that can contain a given range at compile time

## Example
```C++
// evaluates into unsigned char, assuming it's the smallest integer type that can represent the value range [0,100]
integer<100> n;
// evaluates into char, assuming it's the smallest integer type that can represent the value range [-100,100]
integer<100, -100> n;
// evaluates into short, assuming it's the smallest integer type that can represent the value range [-1000,1]
integer<1, -1000> n;
```

For more examples, see [this](small_int/Source.cpp).
