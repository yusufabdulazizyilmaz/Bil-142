#include <iostream>

int main()
{
    int x = 0;
    decltype((++x)) y = x;
    decltype(x) z = x;
    ++x;
    y += 2;
    z += 5;

    std::cout << x << y << z;
}
