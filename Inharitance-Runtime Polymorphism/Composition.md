# COMPOSITION
Nesne yönelimli programlama, problem domainindeki varlıkları sınıflar ile temsil etmeye deniyor.
Prosedürel programlama paradigmasında(C) ayrıştırma functionlara yönelikken nesne yönelimlide ayrıştırma classlara/sınıflara yöneliktir. 
Bunlar sınıflar arasındaki ilişkileri betimleyen bazı terimler var.  
Association : Sistemdeki 2 sınıf birbiriyle işbirliği halinde kullanılıyorsa bu sınıflar arasında association vardır.  
Aggregation : Eğer bu ilişki içindeki sınıflardan biri, diğerinin sahibi olarak onu kulanıyorsa, buna aggregation deniyor. 
Her aggregation bir association.  
Composition : Yine bir nesne diğerinin sahibi fakat sahip olan ile olunan nesne arasında ömürsel birliktelik varsa yani Sahip hayata gelince, 
olunan da geliyor sahip ölünce olunan ölüyorsa buna composition deniyor. Composition bir interface edinme ilişkisi değil. Bir sınıf başka sınıf türden 
bir veri elemanına sahip olunca o veri elemanının interface ini kendi interface ine katmıyor.
```cpp
class A {
public:
    void foo();

private:
    void func();

};

class B {
public:
    void g()
    {
        ma.foo();  // geçerli
        ma.func(); //Burası hata. Private bölüme erişim hakkı verilmedi

    }

private:
    A ma;
};

int main()
{
    B bx;
    bx.foo(); //BURASI HATA. İNTERFACE DEVRALINMAZ. KALITIMDA INTERFACE DEVRALINIR.
}
```
destructor ana bloğundaki kodlar çağrılıyor. Sonrasında hayata gelmesiyle ters sırada elemanlarında destructoru çağrılıyor.
```cpp
#include <iostream>

class Member {
public:
    Member()
    {
        std::cout << "Member Default ctor\n";
    }

    ~Member()
    {
        std::cout << "Member Destructor\n";
    }
};

class Owner {
public:
    Owner() // burada Member için default ctor çağrılacak.
    {
        std::cout << "Owner Default Ctor\n";
    }

    ~Owner()
    {
        std::cout << "Owner Destructor\n";
    }

private:
    Member mx;
};

int main()
{
    Owner ox;
}
/*ÇIKTI:
Member Default ctor
Owner Default Ctor
Owner Destructor
Member Destructor*/
```

```cpp
#include <algorithm>
#include <iostream>

class Member {
public:
    Member() = default;

    ~Member() = default;

    Member(const Member&)
    {
        std::cout << "Member copy ctor\n";
    }

    Member& operator=(const Member&)
    {
        std::cout << "Member copy assignment\n";
        return *this;
    }

    Member(Member&&)
    {
        std::cout << "Member move ctor\n";
    }

    Member& operator=(Member&&)
    {
        std::cout << "Member move assignment\n";
        return *this;
    }
};

class Owner {
public:
    Owner() = default;

    ~Owner() = default;

    Owner(const Owner& other)
            :mx(other.mx)
    {
        std::cout << "Owner copy ctor\n";
    }

    //COPY ASSIGNMENT
    Owner& operator=(const Owner& other)
    {
        std::cout << "Owner copy assigment\n";
        mx = other.mx;
        return *this;
    }

    //MOVE CONSTRUCTOR
    Owner(Owner&& other)
            :mx(std::move(other.mx))
    {
        std::cout << "Owner move constructor\n";
    }

    //MOVE ASSIGNMENT
    Owner& operator=(Owner&& other)
    {
        std::cout << "Owner move assigment\n";
        mx = std::move(other.mx);
        return *this;
    }

private:
    Member mx;
};

int main()
{
    Owner a, b;
    Owner c = a;
    b = a;
    Owner d = std::move(a);
    Owner e;
    e = std::move(b);
}
/*ÇIKTI:
Member copy ctor
Owner copy ctor
Owner copy assigment
Member copy assignment
Member move ctor
Owner move constructor
Owner move assigment
Member move assignment*/
```
