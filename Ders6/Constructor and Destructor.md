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
CONSTRUCTOR INITIALIZER LIST or MEMBER INITIALIZER LIST(MIL).  
DEFAULT MEMBER INITIALIZER or in-class initializer.  
```cpp
#include <iostream>

class Myclass {
public:
    Myclass();

    void print() const;

private:
    int m_first{0};         // DEFAULT MEMBER INITIALIZER or in-class initializer
    int m_a, m_b, m_c, m_d;
    const int m_constx;
};

Myclass::Myclass()
        :m_a{10}, m_b{20}, m_constx{100},  //Member Initializer List (MIL)
         m_first{1}                     // tüm veri elemanlarına değer vermek zorunda değiliz (m_c).
{
    // bu initialize değil assignment önce bu satıra kadar m_d değişkeni çöp
    // değer ile hayata gelir sonra m_d değişkenine 40 değeri atanır.
    // mümkün olduğunca bunu yapmamaya çalışacağız.
    m_d = 40;
    // veri elemanı referans ya da const olduğunda atama işlemi yapamayız. mecbur MIL kullanacağız
    // m_constx = 25; // sentaks hatası
}
void Myclass::print() const
{
    std::cout << "m_first = " << m_first << "\n"
              << "m_a = " << m_a << "     mb = " << m_b << "\n"
              << "m_c = " << m_c << "     md = " << m_d << "\n"
              << "mconstx = " << m_constx << "\n";
}

int main()
{
    Myclass x;
    x.print();
}
/* ÇIKTI:
m_first = 1                 // !!!!!! MILin default member initializera üstünlüğü var. Oyüzden m_first = 1 oldu.
m_a = 10     mb = 20
m_c = 1     md = 40
mconstx = 100*/
```
Veri elemanlarının hayata gelme sırası sınıfın tanımındaki bildirim sırasına göredir. Bizim örneğimizde öncelikle m_first hayata gelecektir.
MIL sırası değişkenlerin hayata gelme zamanında etkisizdir. Mülakatlarda da sıkça sorulan bu soru bize deneyimsiz yazılımcıları yanlış yönlendirmemek
için bildirim sırasına uygun şekilde MIL sırası gözetmemizi önermektedir.

CONVERSION CONSTRUCTOR
User Defined Conversion 2 ye ayrılıyor.  
	Conversion Constructor  
	Type-cast Operator Function  
Standart Conversion Zaten var olan dönüşümler. Ör int --> double  

Eğer bir dönüşüm Standart dönüşüm + User defined dönüşüm ya da User defined dönüşüm + Standart dönüşüm gibi olabiliyorsa derleyici bu dönüşümü gerçekleştrmek zorundadır.

```cpp
#include <iostream>

class Myclass {
public:
    Myclass()
    {
    }
    /*
    conversion constructor
    Compiler ne zaman int, myclass türünden bir değişkene dönüşmesi gerekiyorsa, bu durumdan vazife çıkaracak,
    Myclass(int); Constructor ile geçiçi nesne yaratıp daha sonra da Copy Assignment/Move assignment func ile atama yapacak.
    */
    Myclass(int x). 
    {
        std::cout << "Myclass(int x) x : " << this << "\n";
    }

    operator int()   // Type-cast Operator Function
    {
        std::cout << " operator int \n";
        return 12;
    }
};

void func(Myclass p);
int main()
{
    double dval = 10.;
    Myclass m;
    m = dval;      // derleyici gözünden m = Myclass(static_cast<int>(dval));
    dval x = Myclass();  // derleyici gözünden m = static_cast<double>(Myclass().operator int());
    std::cout << x;   // 12 yazar
    func(15);     //geçerli derleyici gözünden p = Myclass(15);
    
    Myclass m2 = 18; // derleyici gözünden Myclass m2 = Myclass(18); 
}

/*
ÇIKTI:
*/
```
 C++ TA CONVERSION CTOR BAŞIMIZI BELAYA BU DURUMDAN ÖTÜRÜ SOKMASIN DİYE BİR ARAÇ VAR. ADI EXPLICIT CONSTRUCTOR  

EXPLICIT CONSTRUCTOR

```cpp
#include <iostream>

class Myclass {
public:
    Myclass()
    {
    }
    /*
    explicit constructor
    int türünden myclass türüne ben açıkça (explicit) belirttiğim zaman dönüşüme izin ver. Üzerine vazife olmayan bu dönüşümü yapma.
    */
    explicit Myclass(int x). 
    {
        std::cout << "Myclass(int x) x : " << this << "\n";
    }

    operator int()   // Type-cast Operator Function
    {
        std::cout << " operator int \n";
        return 12;
    }
};

void func(Myclass p);
int main()
{
    double dval = 10.;
    Myclass m;
    m = dval;      	//SENTAKS HATASI
    m = static_cast<Myclass>(dval); //geçerli
    func(15);     //geçersiz
    func(static_cast<Myclass>(15));     //geçerli 
    
    Myclass m2 = 18; // geçersiz
    Myclass m2{18};  // geçerli
}
/*
ÇIKTI:
*/
```

