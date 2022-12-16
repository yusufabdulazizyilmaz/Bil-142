# Constructor and Destructor
Bir sınıf nesnesini hayata getiren sınıfın üye fonksiyonlarına sınıfın constructorları deniyor.
Bir sinif varsa, sınıf nesnelerini hayata getirmek için constructor kullanmalıyız. Destructor ise nesnenin hayatını sonlandırıyor.  
CONSTRUCTOR KURALLARI.  
1 - CONSTRUCTOR İSMİ SINIF İSMİYLE AYNI OLMALIDIR.  
2 - GLOBAL FONKSİYON OLAMAZ.  
3 - SINIFIN STATİC ÜYE FONKSİYONU OLAMAZ(non-static). 
4 - GERİ DÖNÜŞ DEĞERİ KAVRAMI YOK.  
5 - CONST ÜYE FONKSIYON OLAMAZ.  
6 - SINIFIN PUBLIC, PRIVATE, PROTECTED FONKSIYONLARI OLABILIR. PRIVATE VE PROTECTED OLUNCA CLIENT KODLAR TARAFINDAN ÇAĞRILAMAZ.  
7 - CONSTRUCTOR OVERLOAD EDILEBILIYOR. 
8 - BIR SINIFIN PARAMETRE DEĞIŞKENI OLMAYAN YA DA TÜM PARAMETRELERI DEFAULT ARGÜMAN ALAN CONSTRUCTORLARA DEFAULT CONSTRUCTOR DENIR.  
9 - CONSTRUCTOR İSMİ İLE ÇAĞRILAMAZ. YANİ . -> OPERATÖRLERİYLE ÇAĞRILAMAZ.  

DESTRUCTOR KURALLARI.   
1 - İSMİ SINIF ~İSMİYLE AYNI OLAN FONKSİYONLAR ~Myclass();  
2 - GLOBAL FONKSİYON OLAMAZ.  
3 - SINIFIN STATIC ÜYE FONKSİYONU OLAMAZ.  
4 - GERİ DÖNÜŞ DEĞERİ KAVRAMI YOK.  
5 - CONST ÜYE FONKSIYON OLAMAZ.  
6 - SINIFIN PUBLIC, PRIVATE,PROTECTED FONKSIYONLARI OLABILIR. PRIVATE VE PROTECTED OLUNCA CLIENT KODLAR TARAFINDAN ÇAĞRILAMAZ.  
7 - DESTRUCTOR OVERLOAD EDILEMEZ. !!!!!!  FARK BURADA PARAMETRESI OLMAYAN BIR FONKSIYON OLMAK ZORUNDA.  
8 - DESTRUCTOR İSMİ İLE ÇAĞRILABİLİR. AMA ASLA BİR DESTRUCTORU İSİMLE ÇAĞIRMAYIN.  
```cpp
class Myclass {
public:
    Myclass();                      // default constructor

    //Myclass(int x = 5);             // default constructor

    Myclass(int x, double y);

    ~Myclass();                     // destructor

    static Myclass(int x, int y);  //static olamaz
    Myclass(double dval) const;    //const olamaz
};

Myclass globalM;  // default initialization default constructor

int main()
{
    Myclass m1; // default initialization default constructor

    Myclass m2{}; // value initialization  default constructor

    static Myclass m3;  // default initialization default constructor

    static Myclass m4{}; // value initialization  default constructor

    const Myclass m5; // default initialization default constructor

}

```


```cpp
#include <iostream>

class Myclass {
public:
    Myclass()
    {
        std::cout << this << " default cunstructor called\n";
    }

    ~Myclass()
    {
        std::cout << this << " destructor called\n";
    }
};

Myclass g1;                                   // 0x1023bc000
Myclass g2;                                   // 0x1023bc001

void func()
{
    std::cout << "func basladi\n";
    Myclass x;                                // 0x16da4b76f
    std::cout << "func calisiyor\n";
}

void foo()
{
    static Myclass m;                         // 0x1023bc008 Sadece 1 kez yaratıldığına dikkat edin
    std::cout << "foo() cagrildi\n";
}

int main()
{
    std::cout << "main basladi\n";
    func();
    foo();
    foo();
    foo();
    foo();
    foo();
    Myclass x{};                              // 0x16da4b7bf (Value initialization olsa bile default constructor cagrildi)
    Myclass* ptr = &x;                        // default constructor nesne hayata getirilmediği için çağrılmadı
    Myclass& r = x;                           // default constructor nesne hayata getirilmediği için çağrılmadı
    std::cout << "main sona erdi\n";
    Myclass z();                              // neden constructor çağrılmadı çünkü bu bir fonksiyon bildirimidir.
}

/* ÇIKTI:
0x1023bc000 default cunstructor called
0x1023bc001 default cunstructor called
main basladi
func basladi
0x16da4b76f default cunstructor called
func calisiyor
0x16da4b76f destructor called
0x1023bc008 default cunstructor called
foo() cagrildi
foo() cagrildi
foo() cagrildi
foo() cagrildi
foo() cagrildi
0x16da4b7bf default cunstructor called
main sona erdi
0x16da4b7bf destructor called
0x1023bc008 destructor called
0x1023bc001 destructor called
0x1023bc000 destructor called */
```

CONSTRUCTOR NEDEN VAR?  
BİR SINIF NESNESİ HAYATA GELDİĞİNDE ONUN ELEMANLARIDA HAYATA GELİYOR. CONSTRUCTOR IN EN ÖNEMLİ ÖZELLİKLERİNDEN BİRİ, SINIF NESNESİ ELEMANLARINA 
İLK DEĞER VERİYOR.  
DESTUCTOR İSE SINIFIN HAYATI SONA ERDİĞİNDE YAPILMASI GEREKEN İŞLER VAR. CONSTUCTOR BİR KAYNAK KULLANIYOR. DESTRUCTOR İSE KAYNAĞI GERİ VERİYOR.
Resource Acquisition Is Initialization (RAII) idiyom kaynak edinimi nesne hayata gelirken olur kaynak geri verilmesi nesnenin hayatı sonlanırken olur.
