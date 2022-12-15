void func(int);

class A {
public:
    void func()
    {
        func(1);
        A::func(2);
        func();
        ::func(3);
        ::func();
    }
};
