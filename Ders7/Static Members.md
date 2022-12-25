# Static Members
Nonstatic veri elemanları instanceları ilgilendirir. Sınıfın storage ihtiyacını da belirler. static veri elemaları fiilen class nesnesinin içinde değil. Öyle değişken olacak ki instance ı değilde sınıfın genelini ilgilendirecek. Yani hangi nesne olursa olsun aynı öğeyi kullanacak. Her sınıf için bir tane. C deki global değişkenler gibi. Sadece class scope a alınmış. Global yerine static değişken kullanmak avantaj olabiliyor.  
1 - Diğer isimlerle karışmıyor ve üye fonksiyonlar içinde bulunmasını sağlıyor.  
2 - Access control sözkonusu. Duruma göre client kodlardan gizlenebilir.  

```cpp
/*
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
void func()   
{				
}
//
```



```cpp
#include <iostream>
/*
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
    Myclass()
    {
        std::cout << "Myclass def ctor called this = " << this << "\n";
    }

    ~Myclass()
    {
        std::cout << "Myclass destructor called this = " << this << "\n";
    }
    static int s_ival;  // Bildirim.
private:

    static Nec myNec;   // incomplete type ile yazılabilir.

    A myA;  // non-static nesne olduğu için complete type olmalı

    static int s_array[]; Incomplete type olduğu için boyut yazmaya gerek yok.

    void func();


    // static int x = 10; // GEÇERSİZ
    static const int s_cival = 20; // const ve integral olmalı
    // const static double dx = 2.0; // GEÇERSİZ
};

//Myclass.cpp
#include "nec.h"   // farzet ki class Nec tanımı bu dosyada

int Myclass::s_ival{15};  //tanım !!!Tanımda static keywordu yok.
Nec Myclass::myNec{}; //default constructor
int Myclass::s_array[10];

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
    Myclass *p = &m;

    Myclass::s_ival = 50;       //geçerli
    p->s_ival = 20;             //geçerli
    m.s_ival = 10;              //geçerli
}
```
