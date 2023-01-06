# GENERIC PROGRAMMING - TEMPLATES

Generic demek türden bağımsız anlamında. Öyle kod var ki farklı veri türleri için kullanılabilir. Programlamanın çok önemli alanlarından biri. 
C++ ın en güçlü olduğu alan belki de bu. C++ terminolojisinde derleyicinin compile time da bizim için kod yazmasına dayanıyor. 
Derleyiciye kod yazdıran kodlara template deniyor. Temel kategorilere ayrılıyor.  
Function Templates   
Class Templates   
Alias Template		C++11 ile geldi   
Variable Template		C++11 ile geldi   
Concept Template		C++20 ile geldi  

Standart Template Library(STL) derleyici bu templatelerden kodları oluşturuyor ve sonra derliyor. Standart kütüphanenin %98-99 oranında şablonlardan oluşuyor.

Ortada bir template varsa keyword olarakta template olmak zorunda.Derleyici buradan anlıyor template olduğunu. Template den sonra açısal parantez <> var. Açısal parantez içinde bildirilen varlıklara template parametreleri deniyor. Template parametreleri,   
	a - Type/Tür parametresi olabilir  
        template < typename T, typename U > ya da template < class T >   
	b - non-type parameter olabilir.(sabit parametre)   
        template < int x >   
	c - template template parameter olabilir. Bu ders kapsamında değil.
```cpp
// T ve U template parametre
template<typename T, typename U> 
void func(T x, U y);

//birincisi tür ikincisi boyut olarak kullanılacak
template<typename T, std::size_t size>
struct Array {
};

int main()
{
    Array<int, 2> ar;
    func(2, 3.);   //func(int x, double y) yazılacak
}
```
Şablonlar başlık dosyalarında yer alıyor. Çünkü derleyicinin kod üretebilmesi için bu şablonların tanımlarını görmesi gerekiyor. Başlık dosyasına template kodları konulunca ODR ihlal edilmez. Mesela vector headerını include ettiğimizde vector header içindeki fonksiyon şablonlarının kodunu kendi dosyamıza yapıştırmış oluyoruz.

## FONKSIYON ŞABLONLARI

Template tür parametresi functionun bildirimi ya da tanımı içinde her yerde kullanılabilir.
```cpp
template<typename T> // T template parametresi
T& func(T x)   // x ise function paramete veya call parametre 
{
    x++;
    T a[10];
    T y = 10;
    if (x==y)
        x.foo();
    return x;
}
```
Burası compile edilirse hata vermez. Çünkü derleyici T nin ne olduğunu bilmiyor. Dolayısıyla T türüne bağlı kontrollerinin bu aşamada yapılma şansı yok.   
Derleyici Şablon Tür Parametresi Yerine Hangi Türün Kullanılacağını Nasıl Anlayacak?   
1. Deduction(çıkarım) 
Template tür parametresinin ne olduğuna derleyici, fonksiyona yapılan çağrıda kullanılan argümanların türünden hareketle karar verecek. auto type deduction ile tek bir istisna dışında aynı.
2. Explicit Olarak Programcının Argümanı Yazması
3. Default Tür Argümanı Kullanımı
```cpp
#include <iostream>
#include <type_traits>

template<typename T = int>
void func(T x = {})
{
    std::cout << typeid(T).name() << " " << x << std::endl;
}

int main()
{
    func(1.f);  //func(float x)  deduction
    func<double>(10.); // expcilit
    func();  //varsayılan argüman
}
/* ÇIKTI:
f 1
d 10
i 0
```
### Deduction(çıkarım)
auto (const volatile ref düşer. array to pointer conversion ve function to pointer conversion olur)
```cpp
#include <iostream>
#include <type_traits>

template<typename T>
void func(T x)
{
    std::cout << typeid(T).name() << std::endl;
}

int main()
{
    func(10);  // auto x = 10; int x=10; func(int)
    const int a = 5;
    func(a);   // auto x = a; int x=a; func(int)
    int i = 3;
    int& r = i;
    func(r);   // auto x = r; int x=r; func(int)

    int arr[] = {1, 2, 3, 4, 5};
    func(arr); // auto x = arr; int* x=arr; func(int*)

    func("yusuf"); //auto x= "yusuf"; const char* x="yusuf"; func(const char*)
}
/*
ÇIKTI:
i
i
i
Pi
PKc
```
auto &
```cpp
#include <iostream>
#include <type_traits>

template<typename T>
void func(T& x)
{
    std::cout << typeid(T).name() << std::endl;
}

int main()
{
    //func(10);  // auto& x = 10; int& x=10; sentaks hatası
    const int a = 5;
    func(a);   // auto& x = a; const int x=a; func(const int) func(int)
    int i = 3;
    int& r = i;
    func(r);   // auto& x = r; int& x=r; func(int&)

    int arr[5] = {1, 2, 3, 4, 5};
    func(arr); // auto& x = arr; int (&x)[5] = arr; func(int (&x)[5])

    func("yusuf"); //auto& x= "yusuf"; const char x[6]="yusuf"; func(const char (&r)[6])
}
/*
ÇIKTI:
i
i
A5_i
A6_c
```

```cpp
template <typename T>
void func(T x, T y);
int main()
{
	func(1,2); // GEÇERLİ. int int
	func("ali","veli"); //GEÇERLİ. const char *, const char *
	func(3.4,2.44); // GEÇERLİ double double
	func(2,3.4); //SENTAKS HATASI. int double. int mi double mı ? Ambigiuty.
		
}

template<typename T>
void func(T& x, T& y);

int main()
{
    int a[5]{}, b[5]{}, c[4]{};
    func("Ali", "Can"); //Geçerli
    func("Umut", "Haydar"); //Geçersiz çünkü const char [5] , const char [7]
    func(a, b);    //GEÇERLİ
    func(a, c); //GEÇERSİZ çünkü int [5] , int [4]
}

template<typename T>
void func(T*);

int main()
{
    int x{};
    int* ptr{&x};
    int** p{&ptr};
    func(p);  // T int*
}

template<typename T, typename U>
void func(T (*)(U));

int foo(double);
int main()
{
    func(foo); // T int, U double
}

```
### CALLABLE
STLde Algorithm denilen fonksiyon şablonlarını öğrenince burası çok önemli olacak.
Bu templateten derleyicinin yazacağı kodun geçerli olabilmesi için T nin hangi türler olma ihtimali var?
```cpp
#include <iostream>

template<typename T>
void func(T x)
{
    x();
}

void foo()
{
    std::cout << "foo()\n";
}

// ismi functor ama başka bir şeyde olabilirdi. önemli olan call operatörünü overload etmesi
class Functor {
public:
    void operator()()
    {
        std::cout << "Functor::operator()()\n";
    }
};

int main()
{
    func(foo);   //func(void(*x)())

    auto fptr = foo;
    func(fptr);  //

    Functor f;
    func(f);

    func([] { std::cout << "yusuf"; });
}
/* ÇIKTI:
foo()
foo()
Functor::operator()()
yusuf
*/
```
a - functionları   
b - function pointerları   
c - Functor sınıfları    
d - Lambda ifadeleri    
### OVERLOADING
Fonksiyon şablonları ile gerçek fonksiyonlar birbirini overload edebilir. Derleyici fonksiyon şablonuna gelince template argument deduction yaparak bir imza elde ediyor. Bu imza ile gerçek fonksiyon arasından karar verilir. İmza ile gerçek fonksiyonun imzası aynı olduğunda gerçek fonksiyon, function overload resolutionda üstünlüğü vardır.
```cpp
#include <iostream>

template<typename T>
void func(T x)
{
    std::cout << "function template \n";
}

void func(int)
{
    std::cout << "Gercek Function\n";
}

template<typename T>
void func(T x, T y)
{
    std::cout << "TT" << "\n";
}

template<typename T, typename U>
void func(T x, U y)
{
    std::cout << "TU" << "\n";
}

template<typename T>
void func(T* x)
{
    std::cout << "2";
}

int main()
{
    func('A');
    func(1.);
    func(24);
    func(1, 2);
    func(1, 2.);
    //PARTIAL ORDERING RULES (Function parametresi daha spesifik olan seçilecek.)
    int x{};
    func(&x);  
}
/* ÇIKTI:
function template 
function template 
Gercek Function
TT
TU
2*/
```
