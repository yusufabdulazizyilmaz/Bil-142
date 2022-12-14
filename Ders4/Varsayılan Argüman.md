# Varsayılan Argüman
Öncelikle bi̇r fonksi̇yonun kaç parametresi̇ varsa ona o kadar argüman göndermeli̇yi̇z.
```cpp
void foo(int, int, int);
int main()
{
	foo(1, 2);  //SENTAKS HATASI
	foo(1); //SENTAKS HATASI
	foo(); //SENTAKS HATASI
	foo(1, 2, 3, 4); //SENTAKS HATASI
	foo(1, 2, 3); //GEÇERLİ.
}
```
default parameter i̇se parametreye argüman göndermi̇yorum sen varsayilan argümanlari kullan demek.
```cpp
void func(int, int, int = 10);
int main()
{
	func(1, 2, 3); //geçerli. 1, 2, 3 gönderildi
	func(1, 2); //geçerli. func(1, 2, 10) gibi çağrılmış olacak.
}
```
varsayilan argüman programa maaliyet getirmez çünkü tamamen compile time ile ilgili bir olaydır.  
Neden kullanıyoruz öyle fonksi̇yonlar var ki̇ yapilan çağrilar çok büyük oranda beli̇rli̇ parametreler i̇çi̇n hep ayni değerler argüman olarak
gönderi̇li̇yor. client kodun rahat etmesi̇ i̇çi̇n kullanabi̇li̇ri̇z.  
1. eğer bi̇r fonksi̇yonun bi̇ldi̇ri̇mi̇nde bi̇r parametre i̇çi̇n default argument beli̇rti̇lmi̇şse onun sağindaki̇ tüm parametreleri̇nde default argument
almasi gereki̇yor.
```cpp
void func1(int = 5, int); //sentaks hatası
void func2(int = 5, int, double); //sentaks hatası
void func3(int = 5, int = 4, double = 3.4); //geçerli
```
2. bi̇ldi̇ri̇mde varsayilan argument beli̇rti̇lmi̇şse tanimda kesi̇nli̇kle beli̇rti̇lmeyecek.yoksa sentaks hatasi.
```cpp
void func1(int x, int y = 10); 
void func1(int x, int y = 10)  // sentaks hatası
{
} 
```
3. varsayilan i̇fadeni̇n sabi̇t i̇fadesi̇ olmasi gerekmi̇yor.
```cpp
int foo(int x = 10);
int func(int y = foo());
int main()
{
	func(); // çağrılırsa func(foo(10)); çağrılacak aslında.
}
```
4. Varsayılan argüman her fonksiyon çağrısında tekrar ele alınır.
```cpp
#include <iostream>

int x{};

int foo()
{
	return ++x;
}

void func(int i = foo())
{
	std::cout << i << " ";
}

int main()
{
	func();
	func();
	func();
}
```
Ekran = 1 2 3  
Varsayılan Argüman için [inceleyiniz](https://necatiergin2019.medium.com/fonksiyonlar%C4%B1n-varsay%C4%B1lan-arg%C3%BCman-almas%C4%B1-default-arguments-1be6aec48f03). 
