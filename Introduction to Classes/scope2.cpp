class D {
public:
    void func();

    void foo()
    {
        func();
        foo();
        D::func();
    }
};

void g(D dx)
{
    dx.func();
    dx.D::func();
}
