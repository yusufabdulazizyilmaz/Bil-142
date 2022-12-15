class Myclass {
public:
    void func();
    //...
};

int main()
{
    Myclass m;

    //func();
    //Myclass::func(&m);
    //Myclass::func(m);
    //m.func();
    //m.Myclass::func();
    //Myclass::func();
    //&m->func();
    //(&m)->Myclass::func();
}
