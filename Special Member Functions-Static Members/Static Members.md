# Static Data Members
Nonstatic veri elemanları instanceları ilgilendirir. Sınıfın storage ihtiyacını da belirler. static veri elemaları fiilen class nesnesinin içinde değil. Öyle değişken olacak ki instance ı değilde sınıfın genelini ilgilendirecek. Yani hangi nesne olursa olsun aynı öğeyi kullanacak. Her sınıf için bir tane. C deki global değişkenler gibi. Sadece class scope a alınmış. Global yerine static değişken kullanmak avantaj olabiliyor.  
1 - Diğer isimlerle karışmıyor ve üye fonksiyonlar içinde bulunmasını sağlıyor.  
2 - Access control sözkonusu. Duruma göre client kodlardan gizlenebilir.  

```cpp
/*
Derleyicinin varlığından haberdar olduğu ancak henüz tanımını görmediği bir türe “tamamlanmamış tür” (incomplete type) denir. 
 * ICOMPLETE İLE NELER YAPILIR ?
class Myclass;
Myclass* p = nullptr; pointer yada referans değişken tanımında.
Myclass func(Myclass x); // fonksiyon bildiriminde.
extern int x; // Extern bildirimi.
typedef Myclass c1; // tür eş ismi bildirimleri.
using c1 = Myclass*; // using ile tür eş isim bildiriminde
static Myclass m1; veri elemanında

değişken veya instance tanımlanamaz
pointer dereference edilemez
sizeof operandı yapılamaz
Myclass *p = new Myclass; olamaz.(storage ihtiyacı belli değil)
Çözünürlük operatörü operandı da olamıyor
 */
//Myclass.h
#include "a.h"   // farzet ki class A tanımı bu dosyada

class Nec; // forward decleration
class Myclass {
public:

private:
    static int s_ival;  // Bildirim.

    static Nec myNec;   // incomplete type ile yazılabilir.

    A myA;  // non-static nesne olduğu için complete type olmalı

    static int s_array[]; //Incomplete type olduğu için boyut yazmaya gerek yok.



};

//Myclass.cpp
#include "nec.h"   // farzet ki class Nec tanımı bu dosyada

int Myclass::s_ival{15};  //tanım !!!Tanımda static keywordu yok.
Nec Myclass::myNec{}; //default constructor
int Myclass::s_array[10];
```
Static member functionlar :: . -> operatörleri ile çağrılabiliyor. Nonstaticler ise :: operatörü ile çağrılamıyor.
Çünkü Nesne gerekli nonstaticte . veya -> operatörleri kullanılabilir.
```cpp
//Myclass.h
class Myclass {
public:
    static int s_ival;
private:
    void func();
    
};

//Myclass.cpp
#include "Myclass.h"

int Myclass::s_ival{15};
void Myclass::func()
{
    s_ival = 12;
    Myclass::s_ival = 12;
    this->s_ival = 34;
}

//main.cpp
int main()
{
    Myclass m;
    Myclass* p = &m;

    Myclass::s_ival = 50;       //geçerli
    p->s_ival = 20;             //geçerli
    m.s_ival = 10;              //geçerli
}
```
# ODR ve Inline 
Aynı kaynak dosyada aynı 2 tanım sentaks hatası (ODR), farklı kaynak dosyalarda aynı varlığın birden fazla tanımı doğrudan undefined behavior. Öyle varlıklar var ki tanımlarının token by token aynı olması durumunda ODR ihlal edilmiyor.
class definition, enumaration type, inline variable, inline functions, templated entity(template or member of template)
```cpp
//.h
// bu tanımlarda ODR ihlal ediliyor. ODR ihlal edilmesi Undefined behavior. bildirim birden çok olabilir ama tanım tek olmalı.
int x = 10;

void foo()
{
}

// istisnalar
class Myclass {
    void baz()   // burada tanımı yapılınca inline oluyor.
    {
    }
};

enum TraficLight {

};

inline void func(int x)
{
    x*x;
}

inline int ival = 35;

template<typename T>
struct A {
    void f() { }
};

//Myclass.h
class Myclass {

private:
    // static int x = 10; // GEÇERSİZ
    static const int s_cival = 20; // const ve integral olmalı
    //static const double dx = 2.0; // GEÇERSİZ
    static constexpr int x = 10;  //GEÇERLİ
    static constexpr double s_dval = 2.3;  //GEÇERLİ

    inline static std::string str{"Alican"}; //SENTAKS HATASI DEĞİL C++17 de dile geldi.

};
```
# Static Member Function
Sınıf içerisinde static keyword ile bildirilen functionlar. Class scope içerisinde olan ve sınıfın private data memberslarına erişim hakkı olan fakat
this pointerı olmayan yani bir sınıf nesnesi için çağrılmayacak, bir sınıf nesnesinin örtülü olarak adresini talep etmeyecek, instance ile ilgili olmayan ve sınıfın geneliyle ilgili olan functions.

```cpp
// myclass.h
class Myclass {
public:
    static void func();
private:
    static void foo(int x)  //inline tanımlandı
    {
        x*x;
    }

    void baz();

    int a; // no static
    static int s_a;
};

// myclass.cpp
void Myclass::func()  //cpp file da tanımlandı
{
    /*STATİC MEMBER FUNCLARIN BİR THİS PTR YOK VE BİR SINIF NESNESİ İÇİN ÇAĞRILMIYOR BU SEBEPLE
     SINIFIN NONSTATİC ÜYELERİNİ (data or function), SINIFIN STATİC ÜYE FUNCLARI İÇİNDE KULLANMAM SENTAKS HATASI */
    // a = 10;
    // baz();
    s_a = 10;
    foo(3);
}

//main.cpp
int main()
{
    Myclass m;
    Myclass* p = &m;
    Myclass & r = m;

    Myclass::func();
    m.func();
    r.func();
    p->func();            
}
```
# SINGLETON İDİYOMU
Pattern = Öyle bir kalıp ki birden fazla problemde bunu kullanabiliyoruz. Dilden bağımsızdır.  
idiom = dile bağımlı.  
Öyle durumlar var ki sınıf türünden tek bir nesnenin oluşturulmasına izin verilecek. Bu nesneye global bir access de sağlamak gerekecek.
```cpp
class Singleton {
public:
    static Singleton& get_instance() // Global bir access verildi.
    {
        static Singleton instance; // Default CTor çağrıldı. Statik ömürlü bir Singleton nesnesi yaratıldı.
        // Tekrar çağrılsa bile yine aynı nesne dönecek varsa yaratmayacak tekrar.
        return instance;
    }

    Singleton(const Singleton&) = delete;

    Singleton& operator=(const Singleton&) = delete;

    void func();

    void foo();

private:
    Singleton() = default;
};

int main()
{
    Singleton::get_instance().foo();
    Singleton::get_instance().func();
    auto& rs = Singleton::get_instance();
}
```
