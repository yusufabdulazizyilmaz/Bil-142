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
