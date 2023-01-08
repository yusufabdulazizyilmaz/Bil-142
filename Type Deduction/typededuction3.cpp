#include <iostream>

int& func(int& r)
{
    ++r;
    return r;
}

int main()
{
    int x = 10;
    auto f = func;
    auto y = f(x);
    auto& r = f(x);
    r += 400;
    y += 50;

    std::cout << "x = " << x << "\n";
}
