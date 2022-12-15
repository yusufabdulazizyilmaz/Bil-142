# This Göstericisi (Pointer)
this bir anahtar sözcüktür. (keyword) Sadece sınıfların nonstatic üye fonksiyonlarında kullanılabilir. Önceden de ifade ettiğimiz gibi
sınıfların nonstatic üye fonksiyonlarının gizli bir parametresi vardır. this ile bu parametreye erişiriz. Yani this demek, bu üye fonksiyon 
hangi nesne için çağrıldıysa o nesnenin adresi demektir.  
```cpp
#include <iostream>

class Nec {
public:
    void func();

private:
    void foo(int);

    int mx;
};

void Nec::func()
{
    std::cout << "this : " << this << "\n";
    // takip eden 3 satır aynı şey
    mx = 10;
    this->mx = 10;
    Nec::mx = 10;
    // takip eden 3 satır aynı şey
    foo(12);
    this->foo(12);
    Nec::foo(12);
}

int main()
{
    Nec neco;
    std::cout << "&neco : " << &neco << "\n";
    neco.func();
}
/*Çıktı:
&neco : 005EF84F
this : 005EF84F
*/
```
Bu this pointerını neden kullanacağız?
1- local değişken sınıfın veri elemanı ile aynı isimli olduğunda sınıfın veri elamanına erişmek için kullanılabilir.
```cpp
class Nec {
public:
    void func();

private:
    int mx;
};

void Nec::func()
{
    int mx{};
    mx = 12;   //BURADA LOCAL MX KULLANILIR.
    this->mx = 15;    //CLASS DATA MEMBER OLAN MX KULLANILIR. Nec::mx = 15; aynı şey
}
```
2- Sınıfın üyesi olmayan free functionları sınıfın üye fonksiyonundan ilgili nesne ile çağırmak için this kullanılmak zorundadır.
```cpp
class Nec {
public:
    void func();

private:
    int mx;
};

void foo(Nec* p);

void f(Nec& r);

void g(Nec);

void Nec::func()
{
    // Func hangi nesne ile çağrıldıysa o argüman ile foo yuçağırsın
    // this olmadan bunu yapmanın yolu yok.
    foo(this);
    f(*this); //*this nesnenin kendisi
    g(*this); //*this nesnenin kendisi
}
```
3- Geri dönüş değeri türü T& olan üye fonksiyonların return ifadesi *this olmak zorundadır.  
Geri dönüş değeri türü T* olan üye fonksiyonların return ifadesi this olmak zorundadır.
```cpp
class Nec {
public:
    Nec& func();    // operator overloading konusunda bol bol göreceğiz
    Nec* baz();
    void foo();

private:
    int mx;
};

Nec& Nec::func()
{
    //...
    return *this;
}

Nec* Nec::baz()
{
    //...
    return this;
}

int main()
{
    Nec mynec;
    mynec.func();    // Nec * türden adres gönderdi implicit olarak.
    mynec.func().foo();   // bu işlem yapılabilir Buna chaining deniyor.
}
```
