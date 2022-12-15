class Nec {
public:
    void foo();

    void func(int);

private:
    int x;
};

void Nec::foo()
{
    //func(3);
}

int main()
{
    Nec mynec;
    //mynec.foo();
}
