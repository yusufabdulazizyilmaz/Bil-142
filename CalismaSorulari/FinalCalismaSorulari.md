```cpp
#include <iostream>
#include <utility>

struct X {
    X() { std::cout << "1"; }

    X(const X&) { std::cout << "2"; }

    X(X&&) { std::cout << "3"; }

    ~X() { std::cout << "4"; }
};

struct Y {
    X x;

    Y() = default;

    Y(const Y&) = default;
};

int main()
{
    Y y1;
    Y y2 = std::move(y1);
}
```
Çıktı: 1244
```cpp
#include <iostream>
#include <map>
using namespace std;

bool default_constructed = false;
bool constructed = false;
bool assigned = false;

class C {
public:
    C() { default_constructed = true; }
    C(int) { constructed = true; }
    C& operator=(const C&) { assigned = true; return *this;}
};

int main() {
    map<int, C> m;
    m[7] = C(1);

    cout << default_constructed << constructed << assigned;
}
```
Çıktı: 111

```cpp
#include <iostream>

int a = 1;

int main() {
    auto f = [](int b) { return a + b; };

    std::cout << f(4);
}
```
Çıktı: 5

```cpp
#include <iostream>
#include <type_traits>

using namespace std;

template<typename T, typename U>
void f(T, U) {
    cout << is_same_v<T, U>;
}

int main() {
    int i = 0;
    double d = 0.0;
    f(i, d); 
    f<int>(i, d); 
    f<double>(i, d); 
}
```
Çıktı: 001
```cpp
#include <iostream>
#include <type_traits>

void g(int&) { std::cout << 'L'; }
void g(int&&) { std::cout << 'R'; }

template<typename T>
void f(T&& t) {
    if (std::is_same_v<T, int>) { std::cout << 1; } 
    if (std::is_same_v<T, int&>) { std::cout << 2; } 
    if (std::is_same_v<T, int&&>) { std::cout << 3; } 
    g(std::forward<T>(t));
}

int main() {
    f(42);
    int i = 0;
    f(i);
}
```
Çıktı: 1R2L
```cpp
#include <iostream>

template<class T>
void f(T) { std::cout << 1; }

template<>
void f<>(int*) { std::cout << 2; }

template<class T>
void f(T*) { std::cout << 3; }

int main() {
    int *p = nullptr; 
    f( p );
}
```
Çıktı: 3

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
	B(B&& b) : a(b.a) { std::cout << "6"; }
};

int main()
{
	B b1;
	B b2 = std::move(b1);
}
```
Çıktı: 1426

```cpp
#include <iostream>

class A {
public:
  A() { std::cout << "a"; }
  ~A() { std::cout << "A"; }
};

class B {
public:
  B() { std::cout << "b"; }
  ~B() { std::cout << "B"; }
};

class C {
public:
  C() { std::cout << "c"; }
  ~C() { std::cout << "C"; }
};

A a;
void foo() { static C c; }
int main() {
  B b;
  foo();
}
```
Çıktı: abcBCA

```cpp
#include <iostream>

int main()
{
    int a[]{1, 4, 7, 2};
    int* x{a};
    decltype(++x) y{x};
    decltype(y++) z{y};
    std::cout << *x+*y+*z;
}
```
Çıktı: 3

```cpp
#include <iostream>

struct Base {
    virtual int f() { return 1; };
};

struct Derived : Base {
    int f() override { return 2; };
};

int main()
{
    Derived object;
    std::cout << object.f();
    std::cout << ((Base&) object).f();
    std::cout << ((Base*) &object)->f();
    std::cout << object.Base::f();
}
```
Çıktı: 2221
```cpp
#include <iostream>

template <typename T> void f() {
  static int stat = 0;
  std::cout << stat++;
}

int main() {
  f<int>();
  f<int>();
  f<const int>();
}
```
Çıktı: 010
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
```cpp
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_same_v<
        void(int),
        void(const int)>;

    std::cout << std::is_same_v<
        void(int&),
        void(const int&)>;
}
```
Çıktı: 01
```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v1(1, 2);
  std::vector<int> v2{ 1, 2 };
  std::cout << v1.size() << v2.size();
}

```
Çıktı: 12
```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, int> m;
    std::cout << m[42];
}

```
Çıktı: 0

Lambda ifadelerinin avantajları nelerdir?  
* Daha iyi okunabilir ve anlaşılabilir kodlar
* Çağrılan kodu görmek için aşağı yukarı hareket etmeye gerek yok
* İnline olarak açılabildikleri için function pointerlara göre daha verimli kod. 
* Fonksiyon çağrısı için bir değişken oluşturmaya gerek yok. (IIFE)
* Bir fonksiyondan geri dönüş değeri olarak alabiliriz.
* std::function yoluyla başka bir fonksiyona argüman olarak geçebiliriz.

İki nesneyi değiştirmek nasıl yapılabilir? 
* Referans yoluyla :    std::swap(x,y);
* Pointer yoluyla  :	std::iter_swap(&x, &y);
