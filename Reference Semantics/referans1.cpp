#include <iostream>

int main()
{
    int a = 10;
    int& r = a;
    std::cout << "a = " << a << std::endl;
    r += 2;
    std::cout << "a = " << a << std::endl;
    r = -r;
    std::cout << "a = " << a << std::endl;
    return 0;
}
