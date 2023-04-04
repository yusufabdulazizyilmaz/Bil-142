# Soru-1
```cpp
#include <cstdio>
#include <complex>

template<typename T1, typename T2>//0 
void f(T1, T2) { putchar('0');}
template<typename T>  		   //1 
void f(T) { putchar('1'); }
template<typename T>  		   //2 
void f(T, T){ putchar('2'); } 
template<typename T>  		   //3 
void f(T *) { putchar('3'); }
template<typename T>		   //4 
void f(T*, T) { putchar('4'); } 
template<typename T> 		   //5 
void f(T, T*) { putchar('5'); } 
template<typename T> 	       //6 
void f(int, T *) { putchar('6'); } 
template<>   		   		   //7 
void f<int>(int) { putchar('7'); }
 
void f(int, double)  //8 
{putchar('8');} 
void f(int)  //9 
{putchar('9');}
 
int main()
{
	int i = 10; 
	double  d = 2.3; 
	float  ff = 7.8f;  
	std::complex<double> c;
 
	f(i);         // a
	f<int>(i);    // b
	f(i, i);      // c
	f(c);         // d
	f(i, ff);     // e
	f(i, d);      // f
	f(c, &c);     // g
	f(i, &d);     // h
	f(&d, d);     // i
	f(&d);        // j
	f(d, &i);     // k
	f(&i, &i);    // l
}
```
* f(i); ile f(T)//1,f<int>(int)//7 ve f(int)//9 arasından 9 seçilir ekrana 9
* f<int>(i);  ile f(int)//1 f<int>(int)//7 arasından 7 seçilir ekrana 7
* f(i, i); ile f(T1,T2)//0, f(T,T) //2 ve f(int,double)//8 arasından 2 seçilir ekrana 2
* f(c);  ile f(T)//1 ile ekrana 1
* f(i, ff); ile f(T1,T2)//0 ve f(int,double)//8 arasından 0 seçilir ekrana 0
* f(i, d); ile  f(T1,T2)//0 ve f(int,double)//8 arasından 8 seçilir ekrana 8
* f(c, &c); ile  f(T1,T2)//0 ve  f(T, T*)//5 arasından 5 seçilir ekrana 5
* f(i, &d); ile f(T1,T2)//0 ve  f(int, T *)//6 arasından 6 seçilir ekrana 6
* f(&d, d); ile f(T1,T2)//0 ve  f(T*, T)//4 arasından 4 seçilir ekrana 4
* f(&d); ile  f(T)//1 ve f(T *)//3 arasından 3 seçilir ekrana 3
* f(d, &i); ile f(T1,T2)//0 ve  f(int, T *)//6 arasından 0 seçilir ekrana 0
* f(&i, &i); ile f(T1,T2)//0 ve  f(T, T)//2 arasından 2 seçilir ekrana 2 

# Soru-2
```cpp
#include <iostream>
#include <utility>
int func(int&) { return 1; }
int func(int&&) { return 2; }

template <typename T>
int f1(T&& x) { return func(x); }

template <typename T>
int f2(T&& x) { return func(std::move(x)); }

template <typename T>
int f3(T&& x) { return func(std::forward<T>(x)); }

int main() {
	int ival = 10;
	std::cout << f1(ival) << f1(20);
	std::cout << f2(ival) << f2(20);
	std::cout << f3(ival) << f3(20);
	return 0;
}
```
* std::cout << f1(ival) << f1(20); için  
f1() içerisinde func(x); çağrısında x L value olduğu için func(int &) çağrılacak ekrana 11
* std::cout << f2(ival) << f2(20); için  
f2() içerisinde func(std::move(x)); çağrısında std::move(x) PR value olduğu için func(int &&) çağrılacak ekrana 22
* std::cout << f3(ival) << f3(20); için  
f3() içerisinde func(std::forward<T>(x)); çağrısında std::forward ile xin değer kategorisi değiştirmediğinden  
f3(ival) için func(int &) çağrılacak ekrana 1, f3(20) için func(int &&) çağrılacak ekrana 2
* Çıktı: 112212

# Soru-3
```cpp
#include <iostream>
 
template <class T> 
void func(T &x) { 
	std::cout << "1"; 
}
template <> 
void func(const int &x) {
	std::cout << 2;
}
int main() {
	int ival = 0;
	func(ival);
}
```
* func için const int türü için specialization yapılmış. ival L value ama const değil.
func(ival); ile derleyici void func(int &) fonksiyonunu yazar ve ekrana 1 yazar.

# Soru-4
```cpp
#include <iostream>

template<class T>
void func(T) {
	std::cout << 'A';
}
template<>
void func<>(int*)  {
	std::cout << 'B';
}
template<class T>
void func(T*) {
	std::cout << 'C';
}
int main() {
	int *ptr = nullptr;
	func(ptr);
}
```
* func(T) için int* türünde explicit specialization yapılmış ve func(T*) ile function overloading yapılmış. Explicit specialization function overloading sete katılmaz.
func(ptr); ile adres türünden bir çağrıda partial ordering rules of templates düşünülerek daha spesifik olan func(T*) seçilir ekrana C yazar.
* Çıktı: C

# Soru-5
```cpp
#include <iostream>
template <class T>
void func(T) 
{
	static int ival = 0;
	std::cout << ++ival;
}
int main() 
{
	func(1);
	func(1.0);
	func(1);
}
```
* func(1); ile void func(int) fonksiyonu derleyici tarafından yazılır ve ekrana 1 yazdırılır.
* func(1.0); ile void func(double) fonksiyonu derleyici tarafından yazılır ve ekrana 1 yazdırılır.
* func(1); ile daha önceden derleyici tarafından yazılan void func(int) fonksiyonu çağrılır ekrana 2 yazar
* Çıktı: 112

