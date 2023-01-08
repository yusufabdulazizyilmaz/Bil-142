### Bilinirlik Alanı (Scope)  
Bilinirlik alanı (scope), bir ismin tanınabildiği program aralığıdır. Her isim derleyici tarafından ancak "o
ismin bilinirlik alanı" içinde tanınabilir. Bilinirlik alanı doğrudan kaynak kod ile ilgili bir kavramdır, dolayısıyla derleme zamanına ilişkindir. aynı scope'ta isimler tek olmalı.  
C dilinde: file scope, block scope, function scope, function prototype scope  
**File scope:** Bir ismin bildirildikten sonra tüm kaynak dosya içinde, yani tanımlanan tüm işlevlerin hepsinin içinde bilinmesidir.  
**Block scope:** İki küme parantezi arasındaki bölgeye blok denilmektedir.  {} Bir ismin bildirildikten sonra yalnızca bir blok içinde, bilinmesidir. Bir blokta bildirilen bir ismin potansiyel kapsamı, bildirim noktasında başlar ve bloğun sonunda biter.  
```cpp
int main() {
    int i = 0; // scope of outer i begins
    ++i; // outer i is in scope
    {
        int i = 1; // scope of inner i begins,
                   // scope of outer i pauses
        i = 42; // inner i is in scope
    } // block ends, scope of inner i ends,
      // scope of outer i resumes
} // block ends, scope of outer i ends
//int j = i; // error: i is not in scope
```
Derleyici, bir ismin kullanımı ile karşılaştığında bu ismin hangi yazılımsal varlığa ait olduğunu bulmaya çalışır. Bu işleme **"isim arama" (name lookup)** denir. İsim arama, dar bilinirlik alanından geniş bilinirlik alanına doğru yapılır. Yani derleyici söz konusu ismi önce kendi bloğunda arar. Eğer isim, bu blok içinde tanımlanmamış ise bu kez isim kapsayan bloklarda aranır. İsim, kapsayan bloklarda da bulunamaz ise bu kez global isim
alanında aranır. Dar bilinirlik alanına sahip isim, daha geniş bilinirlik alanında yer alan aynı ismi maskeler, onun görünmesini engeller (name hiding). isim arama bir kez yapılır ve bulunduğunda da arama devam etmez.

```cpp
#include <stdio.h>
int main() {
  int printf = 0;
  printf(“Merhaba Dunya\n”);
}

// Name lookup
// Context control
// Access control (sınıflarla ilgili)
```
**function scope:** Bir ismin, bildirildikten sonra yalnızca bir blok içinde bilinmesidir. Yalnızca goto etiketlerini kapsayan özel bir tanımdır.  
**function prototype scope:** Fonksiyon bildirimlerinde, parametre değişkenlerinin türlerinden sonra isimleri de yazılabilir.
Bildirimlerde yer alan parametre değişkenleri isimlerinin bilinirlik alanları, yalnızca bildirim parametre ayracı ile sınırlıdır.  
```cpp
double pow(double base, double exp); // base ve exp değişkenlerinin scopu function prototype scope
```
C++ dilinde: **namespace scope**(file scope kapsıyor), block scope, function scope, function prototype scope, **class scope**  
Blokların içinde ya da işlevlerin parametre ayraçları içinde tanımlanan değişkenlere, yerel değişkenler (local variables) denir.
Blokların dışında tanımlanan değişkenler "global değişkenler" (global variables) olarak isimlendirilir.  
scope leakage değişkenin bilindiği fakat kulanılmadığı yerlere verilen isim. değişken kulanıldığı yere yakın yerde tanımlanmalı.    
**İlk değer vermeli if deyimi (if statement with initializer)** C++17 ile doğrudan dil çekirdeğine yapılan bir eklemedir.
```cpp
if (ilk değer verme deyimi; koşul ifadesi)
    deyim;
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    map<int, string> mymap;
    ///
    auto iter = mymap.find(20);
    if (iter!=mymap.end()) {
        iter->second = "necati";
    }
    //
}
/*find üye işlevinden alınan geri dönüş değerinin yalnızca bu if deyiminde kullanılacağını,   
kodun başka bir yerinde bu değere gereksinim duyulmayacağını düşünelim.  
Kodda kullanılan if deyiminden sonra da iter ismi bilinir, değil mi?  
Yani iter ismini yalnızca atama işleminde ve if deyimi içinde kullanmamıza karşın,  
iter ismi main işlevinin sonuna kadar her yerde bilinecek. Yukarıdaki kodda iter isminin bilinirlik alanını  
yalnızca kullanıldığı yerle sınırlamak için yapay bir blok oluşturabilirdik:*/ 
    
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    map<int, string> mymap;
    ///
    {
        auto iter = mymap.find(20);
        if (iter!=mymap.end()) {
            iter->second = "necati";
        }
    }
    //
}
    
// C++17'de dile eklenen if with initializer ile yapay scope oluşturmadan da bu problemi çözebiliriz.
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    map<int, string> mymap;
    ///

    if (auto iter = mymap.find(20); iter!=mymap.end()) {
        iter->second = "necati";
    }
    //
}
```
