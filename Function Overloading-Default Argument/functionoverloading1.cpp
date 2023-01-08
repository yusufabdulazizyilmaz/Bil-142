void func(int&);

void func(int&&);

void func(const int&);

int f1();

int& f2();

void foo()
{
    int x = 10;
    const int cx = 20;

    func(x);
    func(cx);
    func(x+5);
    func(f1());
    func(f2());
}
