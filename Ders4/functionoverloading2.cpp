void func(int);    //1
void func(double);    //2
void func(long);    //3
void func(bool);    //4

void foo()
{
    int x = 10;

    func('A');
    func(2.3F);
    func(4u);
    func(10>5);
    func(&x);
    func(nullptr);
}
