C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında 
bu programın çıktısı ne olur?

# TYPE DEDUCTION
```cpp
#include <iostream>
int main()
{
	int x = 5;
	decltype((x)) y{ x };
	decltype(y *= 2) z = x;
	decltype(y--) t = x;
	int &rx{ x };
	auto ax{ rx };
	++y;
	z *= 2;
	t *= 5;
	ax += 10;
	std::cout << "x = " << x << "\n";
}
```
Çıktı: 12
* decltype((x)) y{ x }; (x) kompleks lvalue ve int, y int& ve x’e bağlanmış.
* decltype(y *= 2) z = x; y*=2 kompleks lvalue ve int, z int& ve x’ bağlanmış.
* decltype(y--) t = x; y-- kompleks prvalue ve int, t int ve ilk değeri x(5).
* int &rx{ x }; rx referansı x’e bağlanmış.
* auto ax{ rx }; ax int türünden ve ilk değeri x(5)
* ++y; x 6 oldu.
* z *= 2; x 12 oldu
* t *= 5; t 25 oldu 
* ax += 10; ax 15 oldu
* std::cout << "x = " << x << "\n"; ekrana 12 yazar
```cpp
#include <iostream>

int main() 
{
	int x = 0;
	decltype((x)) y = x;
	decltype(x) z = x;
	++x;
	y += 2;
	z += 5;

	std::cout << x << y << z;
}
```
Çıktı: 335
* int x{0}, 
* decltype((x)) y = x; (x) kompleks lvalue ve int int& y =x; y demek x demek
* decltype(x) z = x;  int z = x;  z{0}
* ++x; x{1} y{1}
* y += 2;  x{3} y{3}
* z += 5; z{5}
* std::cout << x << y << z;  3 3 5

```cpp
int &f2(int &r1, int &r2)
{
	r1 += r2;
	return r1;
}
void f1(int &r1, int &r2)
{
	r1 *= r2;
	++f2(r1, r2); 
	++f2(r2, r1); 
}
#include <iostream>
int main()
{
	int x = 2, y = 5;
f1(x, y);
	std::cout << x << " " << y << "\n";
}
``` 
Çıktı:16 22
* f2 r1 ve r2 referanslarını alıp r1 referansına r2 değerini ekleyip r1 değerinde değişiklik yapıp r1 gönderiyor
* f1 r1 ve r2 referanslarını alıp f2 fonksiyonunu kullanıp r1 ve r2yi değiştiriyor
* int x = 2, y = 5;   x{2}   y{5}
* f1(x, y); r1 {2} r2{5}
* r1 *= r2;  r1{10}
* ++f2(r1, r2);  r1{10} r2{5} f2(r1, r2) ile r1{15} r2{5} ++ r1{16} r2{5}
* ++f2(r2, r1);  r2{5} r1{16} f2(r2, r1) ile r2{21} r1{16} ++ r2{22} r1{16}
* std::cout << x << " " << y << "\n";  16 22

# FUNCTION OVERLOADING
```cpp
#include <iostream>

void display(char const* ptr)
{
    std::cout << 1;
}

void display(unsigned int uval)
{
    std::cout << 2;
}

int main()
{
    display("abc");
    display(0);
    display('A');
}
```
Çıktı: syntax hatası
* display("abc"); ile "abc" türü const char [4] array to pointer conversion exact match olur 1 yazardı
* display(0); ile 0 int türünde char* ve unsigned inte dönüşüm standard conversion seçilebilirlik yok ambiguity syntax hatası
* display('A'); ile 'A' char dolayısıyla char* dönüşüm yok unsigned int standard conversion 2 yazardı


# SINIFLAR
```cpp
#include <iostream>

class Myclass {
public:
	Myclass()
	{
		static int x{};
		std::cout << x++ << " ";
	}
	
};

int main()
{
	Myclass a[100];
}
```
Çıktı: 0 1 2 3 4 5 .. 98 99
* a arrayi Myclass türünden 100 adet nesne oluşturacak. Static int x{} ile x 0 değeri ile hayata başlıyor 
x++ olduğundan önce x yazılacak sonra değer artacak 0den 99 kadar yazar eğer ++x olsaydı 1den 100e kadar yazardı
```cpp
#include <iostream>
struct Nec {
	Nec() { std::cout << "1"; }
	Nec(const Nec &a) { std::cout << "2"; }
	void func() { std::cout << "3"; }
};
int main() {
	Nec a[2];
	for (auto n : a) {
		n.func();
	}
}
```
Çıktı: 112323
```cpp
#include <iostream>
 
class Nec {
public:
	Nec() { std::cout << "A"; }
	Nec(const Nec&) { std::cout << "B"; }
	Nec(Nec&&) { std::cout << "C"; }
	~Nec() { std::cout << "D"; }
};
 
Nec func()
{
	return Nec{};
}
 
int main()
{
	func();
}
```
Çıktı: AD yazar
```cpp
#include <iostream>
 
struct A {
	A() 
	{
		std::cout << "1";
	}
 
	A(const A &x) 
	{
		std::cout << "2";
	}
	
	const A &operator=(const A &x)
	{
		std::cout << "3";
		return *this;
	}
};
 
int main()
{
	A x;
	A y(x);
	A z = y;
	z = x;
}
```
Çıktı: 1223
* A x; ile A(); 1 yazar
* A y(x); ile A(const A &x) ile 2
* A z = y; ile A(const A &x) ile 2
* z = x; ile const A &operator=(const A &x) ile 3
```cpp
#include <iostream>
#include <vector>
struct A {
	A(){	std::cout << "d";}
	A(const A&){std::cout << "c";}
};
 
int main()
{ 
	std::vector<A> avec(4);
}
```
Çıktı: dddd
```cpp
#include <iostream>
struct A {
	A() { std::cout << "a"; }
	~A() { std::cout << "A"; }
};
struct B {
	B() { std::cout << "b"; }
	~B() { std::cout << "B"; }
};
struct C {
	C() { std::cout << "c"; }
	~C() { std::cout << "C"; }
};
struct D {
	D() { std::cout << "d"; }
	~D() { std::cout << "D"; }
};
A a;
void f1() { static C c; }
void f2() { D d; }
int main()
{
	B b;
	f1();
	f2();
}
```
Çıktı: abcdDBCA
* A a; ile a
* B b; ile b
* f1(); ile c
* f2(); ile d
* nesneler yıkılırken DB C ve A global scope önce hayata gelen C en son A
```cpp
#include <iostream>
using namespace std;
struct Member1 {
	Member1(){ std::cout << "M1";}
};
 
struct Member2 {
	Member2(){std::cout << "M2";}
};
 
class Owner{
public:
	Owner() :m1(), m2() {}
private:
	Member2 m2;
	Member1 m1;
};
 
int main() 
{
	Owner x;
}
```
Çıktı: M2M1
* bildirim sırasına göre ilk değer verilecek M2M1
```cpp
#include <iostream>
struct Nec
{
	Nec() { std::cout << "1"; }
	Nec(const Nec&) { std::cout << "2"; }
	~Nec() { std::cout << "3"; }
};
Nec func() { return Nec(); }
int main() 
{ 
	func(); 
}
```
Çıktı: 13
* Copy elisiondan dolayı 1 ve 3 13
```cpp
#include <iostream>
#include <utility>
struct Nec {
	Nec() { std::cout << "1"; }
	Nec(Nec &) { std::cout << "2"; }
	Nec(const Nec &) { std::cout << "3"; }
	Nec(Nec &&) { std::cout << "4"; }
	~Nec() { std::cout << "5"; }
};
struct A {
	mutable Nec x;
	A() = default;
	A(const A &) = default;
};
int main() 
{
	A a1;
	A a2 = std::move(a1);
}
```
Çıktı: 1255
* A a1 ile A() çağrılır Nec x için 1 yazar
* A a2 = std::move(a1); ile kopyalama burada ifade const olmadığı için 2  
* a1 ve a2 için ~Nec() iki kez çağrılır 55 
* eğer Nec(Nec &) { std::cout << "2"; } olmasaydı  1355
```cpp
#include <iostream>
class A {
public:
	static int x;
	static int foo() {
		return 1;
	}
};
int foo() {
	return 2;
}
int A::x = foo();
int main()
{
	std::cout << A::foo();
	A::x = foo();
	std::cout << A::x;
}
```
Çıktı: 12
* A sınıfı x değişkeni ve foo metodu statik yani nesneden bağımsız tanımlanmış. int A::x =foo(); x statik olmasaydı syntax hatası olur. 
* x isminin başındaki int önemli, ayrıca A::x ile qualified yapılarak foo() fonksiyonunun Adaki foo() fonksiyonu olması sağlanıyor. 
* Böylelikle A::x = 1 değeri atanıyor. Global foo fonksiyonu tanımlanıyor. std::cout << A::foo();  1
* A::x = foo();  buradaki foo() global foo() fonksiyonu A::x = 2 oluyor. std::cout << A::x;  ile 2 yazar

```cpp
#include <iostream>
#include <utility>

struct A
{
	A() { std::cout << "1"; }
	A(const A&) { std::cout << "2"; }
	A(A&&) { std::cout << "3"; }
};

struct B
{
	A a;
	B() { std::cout << "4"; }
	B(const B& b) : a(b.a) { std::cout << "5"; }
	B(B&& b) : a(std::move(b.a)) { std::cout << "6"; }
};

int main()
{
	B b1;
	B b2 = std::move(b1);
}
```
Çıktı: 1436
* B b1; ile b nesnesi içerisindeki önce A nesnesi A() ile hayata gelir 1 sonra parantez içi 4
* B b2 = std::move(b1); move constr a(std::move(b.a)) ifadesi move constr 3 6
```cpp
#include <iostream>
class C {
public:
  C(int i) : i(i) { std::cout << i; }
  ~C() { std::cout << i + 5; }

private:
  int i;
};

int main() {
  const C &c = C(1);
  C(2);
  C(3);
}
```
Çıktı: 127386
* const C&c = C(1); ile C(1) geçici nesnesinin hayatı uzar life extension ekrana 1 yazar
* C(2) ile geçici nesne hayata gelir ve destruct edilir 27
* C(3) ile geçici nesne hayata gelir ve destruct edilir 38
* hayatı uzayan C(1) için destructor çağrılır ve ekrana 6 yazar


# KALITIM
```cpp
#include <iostream>

struct Base1 {
    Base1() { std::cout << "B1"; }
};

struct Base2 {
    Base2() { std::cout << "B2"; }
};

struct Der : Base2, Base1 {
    Der() { std::cout << "D"; }
};

struct Member {
    Member() { std::cout << "M"; }
};

struct A : Der {
    A()
            :m(), Der() { std::cout << "A"; }

    Member m;
};

int main()
{
    A a;
}
```
Çıktı: B2B1DMA
* Önce taban sınıf sonra memberlar hayata gelir. Taban sınıf hayata gelme sırası bildirime göredir.
* A sınıfı için önce Der nesnesi oluşmalı onun içinde önce Base2 sonra Base1 oluşmalı
```cpp
#include <iostream>

struct Base {
    virtual void func() const
    {
        std::cout << "B";
    }
};

struct Der : public Base {
    void func() const override
    {
        std::cout << "D";
    }
};

void display(const Base& x)
{
    x.func();
}

int main()
{
    Base a[1];
    Der der1;
    a[0] = der1;
    display(der1);
    display(a[0]);
}
```
Çıktı: DB

* display(der1); ile const Base& x = der1; ile x Der türünden nesneye bağlanır virtual dispatch olur D 
* display(a[0]); ile const Base& x = der1; ile x Base türünden nesneye bağlanır B yazar
