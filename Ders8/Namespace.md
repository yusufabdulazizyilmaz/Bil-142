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

