# CLASS TEMPLATES / SINIF ŞABLONLARI
Burada oluşturacağımız şablondan hareketle amaç derleyiciye bir sınıfın kodunu yazdırmak.
```cpp
#include <iostream>
#include <vector>
/*class Myclass<int> {
    int f(int x);
    int foo(const int&);
private:
    int mx;
};*/

template<typename T>
class Myclass {
public:
    Myclass()
    {
        std::cout << typeid(*this).name() << "\n";
    }
    
    // EĞER FUNC IÇINDE SINIFIN ISMINI DOĞRUDAN KULLANIRSAK HANGI AÇILIMSA O AÇILIMI KULLANMIŞ OLURUZ.
    void func(T arg)
    {
        Myclass x; // Myclass <T> x;
        Myclass<T> y;
	square(arg);
    }

    //  T int ise int square(int x );
    T square(T x);

    T foo(const T& arg)
    { 
        return mx;
    }


private:
    T mx;
};

// buradan başlıyor tanım
template<typename T>
T Myclass<T>::square(T x)
{
    Myclass temp; //Myclass<T> temp;
    return x*x;
}

int main()
{
    Myclass<int> x;
    Myclass<double> y;

    //x = y; // bu atama yapılamaz çünkü aynı sınıf türünden değil.

    // NOT : SINIFIN ÜYE FONKSIYONLARI ÇAĞRILMADIĞI SÜRECE YAZILMAYACAK !!!!!!!!!!!!
    Myclass<float> mz;  // şuan da foo func veya square kodu yazılmayacak
    mz.foo(12.f); // Artık burada sadece foo functionu yazılacak square ve func yazılmayacak.

    // std::vector<double> bir sınıf yani tür olduğu için T yerine kullanılabilir
    Myclass<std::vector<double>> w1;

    std::vector<Myclass<int>> w2;
}
```
class şablonları, default template argument alabiliyor.
```cpp
template <typename T, typename A = std::allocator<T>>
class vector{
	//..
};

template<typename T = int, typename U = Nec<T>>
struct Myclass {
    
};

int main()
{
    Myclass <double,int> m1;    //Myclass<double, int>
    Myclass<double> m2;         //Myclass<double, Nec<double>>
    Myclass<> m3;               //Myclass<int, Nec<int>>
    
    
    std::vector<int> vx; //std::vector<int, std::allocator<int>>
}
```
## MEMBER TEMPLATES
```cpp
template<typename T>
class Myclass {
public:
    void func(T x);

    Myclass() = default;

    //Copy constructor Myclass(const Myclass &);
    Myclass(const Myclass<T>&);  //Myclass(const Myclass<int>&) demek !!!!!

    void foo(Myclass);

    // Member template
    template<typename U>
    void fooNew(Myclass<U> x);
};

int main()
{
    Myclass<int> mx; // Myclass int açılımı. T burada int
    mx.func(1.0); // Bu adımda template type deduction yapılmayacak çünkü T belli zaten.
    Myclass<int> my = mx; //copy constructor

    Myclass<double> md;

    //md.foo(mx); sentaks hatası

    md.fooNew(mx); // geçerli fooNew(Myclass<int>) U int

}
```
## Pair Class Template
STL de en sık kullanılan sınıf şablonlarından biri. Özü çok basit ama içeriği karışık.  
1 - En çok kullanıldığı yer bir fonksiyondan 2 adet değer döndürmek için.   
2 - bir sınıfın veri elemanını pair yapabiliriz.   
3 - Container denen sınıflarda pair tutmak çok sık karşımıza çıkan yapı. insanların yaşlarını ve isimlerini birarada tutmak istedik ama bir nedenden ötürü sınıf yapmak istemedik
```cpp
std::pair<int,double> foo();

class Person {
private:
    std::pair<std::string, int> mx;
};

int main()
{
    std::vector<std::pair<std::string, int>> ivec;
}
```

```cpp
#include <iostream>

template<typename T, typename U>
struct Pair {
    Pair() = default;

    // bunun sayesinde Pair<int,double> x{123,5.6}; yapabiliriz.
    Pair(const T& t, const U& u)
            :first(t), second(u) { }

    //conversion constructor
    template<typename K, typename M>
    Pair(const Pair<K, M>& other)
            : first(other.first), second(other.second) { }

    T first{}; //value init edildi. Bu da zero init
    U second{};
};

//burası idiyom < operatorü STL in en önemli operatörü kabul ediliyor. implementasyonlarda < kullanıyoruz.
template<typename T, typename U>
[[nodiscard]] bool operator<(const Pair<T, U>& left, const Pair<T, U>& right)
{
    return left.first<right.first || !(right.first<left.first) && left.second<right.second;
}

template<typename T, typename U>
Pair<T, U> MakePair(const T& t, const U& u)
{
    return Pair<T, U>(t, u); // bu bir geçici nesne
}

int main()
{
    Pair<int, double> p1;
    std::cout << p1.first << " " << p1.second << "\n";
    Pair<int, double> p2{123, 5.6};
    std::cout << p2.first << " " << p2.second << "\n";

    std::cout << std::boolalpha << (p1<p2) << "\n";

    Pair<int, int> p3;
    p1 = p3; //önce conversion ctor sonra operator=()

    auto p4 = MakePair(12, 4.5);
}
```

```cpp
#include <utility>
#include <string>
#include <iostream>

//PAIRIN BIR INSERTERI YOK. ÖYLE BIR FUNC YAZALIM KI HERTÜRLÜ PAIRI ÇIKIŞ AKIMINA VERSIN.
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

int main()
{
    std::pair<int, double>p{ 23, 5.6 };
    std::cout << p << "\n";
    std::cout << std::make_pair(12, 4.5)<<"\n";
    std::cout << std::make_pair(std::make_pair(33, 6.7), 
            std::make_pair(std::bitset<32>{1234u},std::string("Alican"))) << "\n";
    
    std::cout << std::make_pair("Veli", 
            std::make_pair(std::bitset<32>{1234u},std::string("Alican"))) << "\n";
}
```
## EXPLICIT SPECIALIZATION
Sınıf ve fonksiyon şablonlarında, bir şablonun belirli tür açılımı için derleyicinin kod yazmasi yerine benim verdiğim kodun kullanılmasını sağlayabilirim. Buna TEMPLATE EXPLICIT SPECIALIZATION denir. Belirli bir tür template in ana yapisina uymuyorsa ve o tür için özel bir koda ihtiyaç varsa onu specialization olarak verebiliriz.

```cpp
template<typename T, int n> // burası görünür durumda olmalı.
class Myclass {
public:
	Myclass()
	{
		std::cout << "primary template Myclass<T>\n";
	}
};
// <> (diamond) explicit specialization
template <>
class Myclass<int, 5>
{
public:
	Myclass()
	{
		std::cout << "Myclass<int,5> explicit specialization\n";
	}
};

int main()
{
    Myclass <char,4> cx;
    Myclass <double,5> dx;
    Myclass <int,5> ix; // Bunun için bizim yazdığımız specialization çalışır.
}
#include <iostream>
// 1 -100 arası sayıları ekrana döngü kodu olmadan yazdır.
template<int n>
struct A : A <n-1> {
    A()
    {
        std::cout << n << " ";
    }
};
template<>
struct A<0> {
};
int main()
{
    A<100> ax;
}
```


```cpp
#include <iostream>

template <typename T>
void func(T x)
{
    std::cout << "primary template for type\n";
}
template <>
void func(int x)
{
    std::cout << "func<int> explicit specialization\n";
}
int main()
{
    func(2.3);
    func('A');
    func(5);
}
```

Template explicit specialization function overload sete dahil edilmiyor.
```cpp
template <typename T>
void func(T x)
{
    std::cout << "1\n";
}
template <>
void func(int *x)
{
    std::cout << "2\n";
}
template <typename T>
void func(T *x)
{
    std::cout << "3\n";
}
int main()
{
    int x{};
    func(&x); 
}
// ÇIKTI:3
```
## PARTIAL SPECIALIZATION
Daha sınırlı bir tür kümesi için alternatif template in kullanılmasını istiyoruz. Burada artık template kod artık bir tür için değil, bir tür ailesi için kullanılıyor. Sınıf şablonları için var. Function şablonları için yok.
```cpp
#include <utility>
template<typename T>
class Myclass{
};
// Pointer için partial specialization
template<typename T>
class Myclass<T *>
{
};
// Referans için partial specialization
template <typename T>
class Myclass<T&> {
};
// Pair türleri için partial specialization
template <typename T, typename U>
class Myclass< std::pair <T,U>> {
};
```
