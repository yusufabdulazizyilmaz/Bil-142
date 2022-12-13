# Tür Çıkarımı
Tamamen derleme zamanıyla ilgili. Runtime ile ilgili değil. Değişkenin türünü açıkça yazmasakta, derleyici değişkenin türünü compile time da
anlıyor.
## Auto Belirleticisi
C++11 standartlarıyla gelen en önemli eklentilerden biri auto belirleyicisidir. 
auto belirleyicisi ile tanıtılan bir değişkenin tür bilgisini derleyici, derleme zamanında yapacağı bir çıkarımla anlar.
```cpp
auto x = 10; // x int olacak bu durumda.
```
akronim Her bir harf bir kelimeye denk gelen keilmeler. mesela AAA = Almost Always Auto.  
AUTO ÇIKARIMI NASIL YAPILIR  
1. auto nun yanında & yok. auto tek başına olduğu durumda Tür bilgisinden constluk ve referans düşer.
```cpp
int ival = 10;
const double cdval = 2.1987;
const double& cdr = cdval;
auto x = cdval; //cdval türü const double constluk düşer x değişkeni double türden.
auto y = cdr; //cdr türü const double& constluk ve ref düşer y değişkeni double türden.
auto z = &ival; //&ival türü int * z değişkeni int* türden.
```
Ayrıca Array to pointer ve function to pointer dönüşümleri olur. Array to pointer dönüşümü dizi isimlerinin ilk elemanlarının adresi olarak kullanılabilmesidir.
```cpp
int a1[10]{};
auto x1 = a1;  // a1 nın türü int [10] array to pointer dönüşümü ile int* x1 = a1;
auto x2 = "mert"; // "mert" ifadesinin türü const char [5] array to pointer dönüşümü ile const char* x2 = "mert";
int func(int);
auto f = func;  // func türü int(int) function to pointer dönüşümü ile int (*f) (int) = func;
```
2. auto nun yanında & var. auto ile tanıtılan değişkeninin bir referans olarak çıkarımının yapılması için auto anahtar sözcüğü ile birlikte & bildirgeçi (declarator) kullanılmalıdır. 
auto & x = buraya ne gelirse gelsin x ref türünden olacak. Bu durumda referansa ilk deger verme konusundaki kurallar geçerli olur:
Tür bilgisinden constluk ve referans düşmez ve Array to pointer function to pointer dönüşümleri olmaz.
```cpp
int ival = 10;
auto& r1 = ival;  //ival int türü int& r1 = x;
auto & r2 = 20; //20 int türü int& r2 = 20; sentaks hatası 20 PR value
const int cival = 10;
auto& r3 = cival;  // cival const int türünden const int& r3 = cival; constluk düşmedi
int a[]{ 1,2,3,4,5 };
auto& r4 = a;   // a in türü int(&)[5] int(&r4)[5] = a;
const int a[]{ 1,2,3,4,5 };
auto& r5 = a;   // a in türü const int(&)[5] const int(&r5)[5] = a;
auto& r6 = "ezgi";  // "ezgi" const char[5] const int(&r6)[5] = "ezgi";
int func(int);
auto& r7 = func; // (function to pointer conversion) dönüşümü olmaz int (&r7)(int) = func;
```

Auto belirleyicisi özellikle C++11 ile dile eklenen renge based for loop da kullanılır.
```cpp
std::list<std::string> namelist {"berk", "hasan", "turgut", "melih"};
for (auto r : namelist) {
	std::cout << r << "\n";
}
```
Burada auto belirteci ile tanıtılan döngü değişkeni, kapta (container) tutulan öğelerin türündedir. Tanıtılan döngü değişkeni bir referans isim olmadığından kapta tutulan öğenin kendisi değildir. Şüphesiz kopyalama yüzünden maliyet referans isim kullanılmasına göre daha yüksektir.  
Tanıtılan ismin kapta tutulan öğenin kendisinin yerine geçmesi isteniyorsa & bildirgeci kullanılmalıdır:  
```cpp
std::list<std::string> namelist {"berk", "hasan", "turgut", "melih"};
for (auto &r : namelist) {
	r += "can";
}
```
Kap salt okuma amaçlı olarak dolaşılacak ise hem kodun anlaşılırlığını sağlamak hem de kaptaki öğeleri yanlışlıkla değiştirmeye karşı korumak amacıyla const referanslar kullanılmalıdır:  
```cpp
std::list<std::string> namelist {"berk", "hasan", "turgut", "melih"};
for (const auto &r : namelist) {
	std::cout << r << "\n";
}
```
## Decltype Belirleticisi
C++11 ile birlikte decltype dile eklendi. decltype anahtar sözcüğü “declaration type” (bildirim türü) sözcüklerinden uydurulmuş. Bir tür kullanılması söz konusu olan her yerde decltype kullanabiliyoruz.  (decltype(expr))
1- decltype operandı isim formundaysa Bu isim hangi türden declere edildiyse bizim elde ettiğimizde o tür.
```cpp
int x = 56;
int& r = x;

decltype(x) // int türü
decltype(r) // int& türü

int a[10]{};
decltype(a) // int[10] türü.
const int b[3]{};
decltype(b) // const int[3] türü

const int y{ 12 };
decltype(y) // const int türü
decltype(r) t; //
decltype(a) k; // sentaks hatası yok. int k[10] demek;

const int x = 56;
decltype(x) y; // hatalı çünkü const nesneye ilk değer verme şartı var.
```
2- İsim formunda değilse Bu durumda decltype karşılığı elde edilen tür parantez içindeki ifadenin value kategorisine bağlı.  
a - eğer ifade pr value expr ise, decltype yerine gelen tür 	T türü  
b - eğer ifade L value exp.ise decltype yerine gelen tür 	T & türü  
c - eğer ifade X value exp.ise decltype yerine gelen tür 	T && türü  
```cpp
int x = 10;
decltype(x + 5) y; // isim değil x+5 PR value ve int türünden öyleyse ==> int y;
int* ptr = &x;
decltype(*ptr) z = y; // isim değil *ptr L value ve int türünden öyleyse int& z = y;

decltype(x) a = y; // x isim türü int dılayısıyla int a = y;
decltype((x)) b = y; // (x) isim formunda değil  L value ve int türünden dolayısıyla int& b = y;

int x = 10;
int y = 20;
decltype(++x) z = y;

++z;

std::cout << x << " " << y << " " << z; 
```
decltype unevaluated contex oluşturuyor. sizeof gibi. & gibi.
burada ++x için compiler işlem kodu üretmiyor.birkaç yerde daha var unevaluated contex.
