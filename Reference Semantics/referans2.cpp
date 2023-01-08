#include <iostream>
void func(int &r)
{
    r = 20;
}
int main()
{
    int a = 10;
    func(a);
    std::cout << a << std::endl;
    return 0;
}
