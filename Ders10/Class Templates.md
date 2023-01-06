# CLASS TEMPLATES / SINIF ŞABLONLARI
Burada oluşturacağımız şablondan hareketle amaç derleyiciye bir sınıfın kodunu yazdırmak.
```cpp
#include <iostream>
#include <vector>
/*class Myclass<int> {
    int f(int x);
    int foo(const int&);
private:
    int mx;
};*/

template<typename T>
class Myclass {
public:
    Myclass()
    {
        std::cout << typeid(*this).name() << "\n";
    }

    //  T int ise int f(int x );
    Myclass f(T x);

    T foo(const T& arg)
    {
        f(arg);
        return mx;
    }

    // EĞER FUNC IÇINDE SINIFIN ISMINI DOĞRUDAN KULLANIRSAK HANGI AÇILIMSA O AÇILIMI KULLANMIŞ OLURUZ.
    void func(T)
    {
        Myclass x; // Myclass <T> x;
        Myclass<T> y;
    }

private:
    T mx;
};

// buradan başlıyor tanım
template<typename T>
Myclass<T> Myclass<T>::f(T x)
{
    Myclass a; // Myclass<T> a;
}

int main()
{
    Myclass<int> x;
    Myclass<double> y;

    //x = y; // bu atama yapılamaz çünkü aynı sınıf türünden değil.

    // NOT : SINIFIN ÜYE FONKSIYONLARI ÇAĞRILMADIĞI SÜRECE YAZILMAYACAK !!!!!!!!!!!!
    Myclass<float> mz;  // şuan da foo func veya f kodu yazılmayacak
    mz.foo(12.f); // Artık burada sadece foo functionu yazılacak f ve func yazılmayacak.

    // std::vector<double> bir sınıf yani tür olduğu için T yerine kullanılabilir
    Myclass<std::vector<double>> w1;

    std::vector<Myclass<int>>w2;
}
```

```cpp
```

```cpp
```

```cpp
```

```cpp
```

```cpp
```

```cpp
```
