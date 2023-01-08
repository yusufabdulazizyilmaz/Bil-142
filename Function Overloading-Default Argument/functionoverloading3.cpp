#include <iostream>

void func(int)
{
    std::cout << "int";
}

void func(double)
{
    std::cout << "double";
}

int main()
{
    func(2.F);
}
