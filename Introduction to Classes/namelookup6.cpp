class Nec {
public:
    void func(int x);

private:
    void func(double x);
    void foo();
};

void Nec::foo()
{
    //func(12);
    //func(1.2);
}
