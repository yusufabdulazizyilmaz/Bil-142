# NAMESPACE (İSİM ALANI)
İsim alanı, global isim alanında oluşturabileceğimiz ve isimlerin birbirleriyle karışmasını engellemeye yönelik ve bu isimleri
bir arada tutan bir paket/container gibi bir yapı. İsim alanında bildirilen isimler özel bir scope ait. Bu namespace scope. Tüm standart kütüphaneden gelen isimler ismi std olan bir namespace içinde.
```cpp 

// .h
namespace Std {
    int ival{1};
    namespace Chrono { //nested namespace
        int x = 10;
    }
}

//Derleyici bir namespaceden sonra tekrar aynı tanımı görürse bunları otomatik birleştirir.
/*Neden namespaceler birden fazla kez oluşturulabilip birleştiriliyorlar?
  Bir sürü library var. Farklı librarylerin hepsini kendi başlık dosyası içinde aynı namespacelere koyuyor bunları.
  std::string x; string header file
  std::vector<int>vec; vector header filedan
 */
namespace Std {
    class String {
        void foo();
    };
}
// .cpp
namespace Std {
    void String::foo()   //tanımı
    {

    }
}

int main()
{
    Std::ival = 12;
    Std::Chrono::x = 20;
    Std::String myString;
}
```
Bir namespace içindeki isimlerin, bir namespace ismiyle nitelenmeden ilgili namespace te aranıp bulunmasını sağlayan 3 adet araç var.  
1 - Using Decleration (**using namespace_name::object_name;**) 
```cpp
using value_type = int;    // type alias
namespace Std {
    int ival{1};
}

void func()
{
    using Std::ival; // using decleration kapsamı var ve enjekte ediliyor
    ival = 12;
    int ival = 18;  // geçersiz ival diye bir değişken var
}

int main()
{
    ival = 12; // geçersiz using decleration kapsamında değil
}
```
2 - Using Namespace Decleration (**using namespace namespace_name;**) 
```cpp


namespace Std {
    int ival{1};
    namespace Chrono { //nested namespace
        int x = 10;
    }
}
namespace Std2 {
    int ival{1};
}

void func()
{
    // tüm isimleri birden o scopeda görünür kılar fakat enjekte etmez
    using namespace Std;

    ival = 12;

    Chrono::x = 20;

    int ival = 10; //geçerli
    ival = 12; //yerel ival
    Std::ival = 12;
}

void foo()
{
    using namespace Std;
    using namespace Std2;
    ival = 20;  //geçersiz Ambiguity
}
```
Başlık dosyası içinde asla using bildirimi veya using namespace bildirimi yapmayın.
Bunu include eden herkeste de bu bildirim olur.Bu durumda da namespace lerin varlık sebebi ortadan kalkar.

3 - ADL(Argument Depended Lookup)  

KURAL: EĞER BİR FONKSİYON ÇAĞRISINDA FONKSİYONA ARGÜMAN OLARAK GÖNDERİLEN İFADE, BİR NAMESPACE İÇİNDE TANIMLANAN TÜRLERDEN BİRİNE İLİŞKİN İSE, O ZAMAN BU İSİM NORMAL ARANDIĞI YERİN DIŞINDA BU İSMİN AİT OLDUĞU TÜRÜN AİT OLDUĞU NAMESPACE İÇİNDE ARANIR.

```cpp
namespace Nec {
    class Myclass {
    };

    enum color {
        Red, Green, White
    };

    void foo(Myclass m);

    void func(int);

    void baz(Myclass m);
}

void baz(Nec::Myclass m);

int main()
{
    func(4); //SENTAKS HATASI.
    Nec::Myclass m;
    foo(m); // SENTAKS HATASI DEĞİL. :D:D	Nec::foo(m) diye çağrılmadığı halde sentaks hatası değil.
    func(Nec::color::Red);

    std::vector<std::string> svec;
    // code
    auto iter = find(next(svec.begin()), prev(svec.end()), "ali");
    auto iter = std::find(std::next(svec.begin()), std::prev(svec.end()), "ali");

    baz(m); //BURADA AMBIGIUTY VAR. FUNC İSMİ HEM GLOBALDA HEM DE NEC İÇİNDE BULUNDU. ÖNCELİK YOK BURADA.
}
```
## UNNAMED NAMESPACE

Sadece ilgili kaynak dosyada geçerli olan ve bir using bildirimi olmadan bu namespacedeki isimleri bunu kapsayan namespacede (genelde global namespacede) kullanabileceğimiz bir özellik.
```cpp
namespace Nec {

    namespace {
        int x;
    }
    int y = x;

}

namespace {
    int x;
}

/*namespace name1
{
    int x;
}
using namespace name1;*/

int main()
{
    x = 12;
}
```
UNNAMED NAMESPACE LER INTERNAL LINKAGE A AIT.  
EXTERNAL LINKAGE = FARKLI KAYNAK DOSYALARDA AYNI VARLIĞA İŞARET EDİYORSA.  
INTERNAL LİNKAGE = SADECE O KAYNAK DOSYADA KULLANILDIĞINDA AYNI VARLIĞI GÖSTERİYORSA.  
```cpp
//nutility.h
const int x = 10;
void fx();

//nutility.cpp
#include "nutility.h"
#include <iostream>

void fx()
{
    std::cout << "nutility &x = " << &x << "\n";
}
//main.cpp
#include "nutility.h"
#include <iostream>

int main()
{
    fx(); // buradaki x adres ile
    std::cout << "&x = " << &x << "\n";
}
/* 
ÇIKTI: (inline olmadan)  INTERNAL LİNKAGE
nutility &x = 0x10041fe18
&x = 0x10041fe14

ÇIKTI: (inline)  EXTERNAL LİNKAGE
nutility &x = 0x102607e18
&x = 0x102607e18
*/

```
