int foo(int& x, int& y)
{
    x = 3;
    y = 4;
    return x+y;
}

int main()
{
    int x = 1;
    int y = 2;
    int z = foo(x, x);

    std::cout << x << y << z;
}
