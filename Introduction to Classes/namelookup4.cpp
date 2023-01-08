class Nec {
public:
    void func(int x);               //1
    void func(int x, int y);        //2
};

int main()
{
    Nec mynec;
    //mynec.func(2);
    //mynec.func(1,2);
}
