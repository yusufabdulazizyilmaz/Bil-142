#include <iostream>

void Swap(int& r1, int& r2)
{
    int temp = r1;
    r1 = r2;
    r2 = temp;
}

int main()
{
    int x = 10, y = 34;
    std::cout << "x = " << x << " y = " << y << "\n";
    Swap(x, y);
    std::cout << "x = " << x << " y = " << y << "\n";
}
