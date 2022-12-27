# Numaralandırma Sabitleri (ENUM)

## Enum vs Scoped Enum (Enum Class)  
1- Numaralandırma türlerinde (Enum) tanıtılan numaralandırma sabitlerinin kapsamları (scope) ilgili türün kapsamı iken Numaralandırma sınıfı(Enum Class) türlerinin kendi kapsamları var ve tanıtılan numaralandırma sabitleri numaralandırma sınıfının kendi kapsamında yer alıyor.

```cpp
enum Color {white, red, magenta, black};
enum TrafficLight {red, yellow, green};
// red için redefinition hatası olur çünkü her ikisinin de kapsamı ait oldukları enumun kapsamıdır.
// Color ve TrafficLight kapsamları aynıdır.

enum class ScopedColor {white, red, magenta, black};
enum class ScopedTrafficLight {red, yellow, green};
// red için hata alamayız çünkü artık red kapsamlandırılmıştır. ScopedColor::red ya da ScopedTrafficLight::red yazmalıyız.
```
2- Kapsamsız numaralandırma türlerinden tam sayı ve gerçek sayı türlerine örtülü (implicit) tür dönüşümü var. Enum class için örtülü dönüşüm yoktur. 
Explicit dönüşüm yani programcının bilerek isteyerek yaptığı dönüşümler ikisi için de geçerlidir. Çünkü enum türlerinden underlying type dönüşüm promotion kategorisindedir. (Hatırla integral promotion floating-point promotion)

Bir numaralandırma türüne ilişkin derleyici tarafından arka planda kullanılan tam sayı türüne underlying type (baz tür)deniyor. C’de numaralandırma türlerinin baz türü her zaman int türüdür. C++03'de bir numaralandırma türüne ilişkin baz türün ne olacağına karar veren derleyicidir. C++11 ile baz türü programcı belirleyebilmektedir.

----> (implicit)    ******> (explicit)    
Enum ------> int,double   

Enum Class ******> int, double  

int, double  ******> Enum, Enum Class  
```cpp
enum Color {white = 0, red, magenta, black};
Color myclor = 1; //geçersiz
Color myclor = static_cast<Color>(1); //geçerli 
int x = mycolor; //geçerli 

enum class ScopedColor {white = 3, red, magenta = 12, black};
ScopedColor myclor = 5; //geçersiz
ScopedColor myclor = static_cast<Color>(12); //geçerli
int x = ScopedColor::mycolor; //geçersiz 
```
## Forward Decleration (Ön Bildirim) ve Enum 
Bir türü ön bildirimle kullanabildiğimiz durumlarda bu türün tanımını içeren başlık dosyasını kendi kodumuza dahil etmemiz gerekmez. Bu durumda başlık dosyalarının birbirine bağımlılığı ortadan kaldırır. Önemli artıları yaptığımız değişiklikten etkilenen dosyalar azalır ve derleme süresi kısalır. Ancak bunun için derleyicinin söz konusu numaralandırma türü için bellekte kaç byte yer ayrılacağını bilmesi gerekir.
```cpp
// ScopedColor.h
enum class ScopedColor : char {white = 3, red, magenta = 12, black};

//.cpp
#include "ScopedColor.h";
class Myclass{
	ScopedColor mycolor;
};


// FORWARD DECLERATIONS 
//.h
enum class ScopedColor : char;
class Myclass{
	ScopedColor mycolor;
};
//.cpp
#include "ScopedColor.h";

```
Scoped Enum için [inceleyiniz](https://necatiergin2019.medium.com/numaraland%C4%B1rma-s%C4%B1n%C4%B1flar%C4%B1-enum-classes-a6276c93f06d) 
## C++20 Using Enum Declerations

```cpp
//C++20 using enum <enum_name>
enum class Days{Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

void func()
{
	using enum Days;

	auto d1 = Sunday;
	auto d2 = Monday; 
	auto d3 = Friday; 
	//...
}
```
