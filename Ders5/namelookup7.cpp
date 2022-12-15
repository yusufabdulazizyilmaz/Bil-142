class E {
    int x(int)
    {
        return 1;
    }

public:
    void foo();
};

int x = 20;

void E::foo()
{
    E myE;
    //if (auto x = ::x+5; x>10)
    //    x = myE.x(x);

    //++x;
    //auto val = x(::x);
    //E::x(::x);

}
