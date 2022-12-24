# DİNAMİK ÖMÜRLÜ NESNELER
Hayata istenildiği zaman getirilip istenildiği zaman bitirilen nesneler dinamik ömürlü nesnelerdir. Zorunda değilsen dinamik ömürlü nesne oluşturma. Normalde otomatik ömürlü kullanırız, mecbur kalırsak dinamik ömürlü kullanırız. Neden?    
1 - Dinamik ömürlüler çok daha yüksek maliyetli.  
2 - Kullanımı otomatik ömürlüye göre daha zor, hata yapmak daha kolay.  
3 - Test-Debug-Değişiklik daha zor.  

C++'ta Dinamik ömürlü nesne oluşturan new operatörleri ve nesnenin hayatını sonlandıran delete operatörleri vardır.  
  
```cpp 
/*
new Myclass(); derleyici ne yapıyor
Derleyici ismi operator new olan fonksiyonuna çağrı yapıyor, bu fonkisyona argüman olarak sizeof Myclass
gönderiyor ve bu fonksiyonun geri dönüş değeri olan void * türünden adresi Myclass * türüne dönüştürerek ve bunu this adresi olarak kullanıp,
sınıfın ilgili Constructoruna çağrı yapıyor

new ifadesi = operator new() --> constructor
delete ifadesi = destructor --> operator delete()
//void * operator new(size_t n); C++ ın global functionu. overload yapılabiliyor
*/

#include <iostream>

class Myclass {
public:
    Myclass()
    {
        std::cout << "Myclass def ctor called this = " << this << "\n";
    }

    ~Myclass()
    {
        std::cout << "Myclass destructor called this = " << this << "\n";
    }

private:
    char buffer[1024]{};
};

// operator new func overload ediliyor.
void* operator new(std::size_t n)
{
    std::cout << "Operator new called n = " << n << "\n";
    void* vp = std::malloc(n);
    if (!vp) {
        throw std::bad_alloc{};
    }
    std::cout << "the address of the allocated block = " << vp << "\n";
    return vp;
}

void operator delete(void* vp)
{
    if (!vp)
        return;
    std::cout << "operator delete called... vp = " << vp << "\n";
    std::free(vp);
}

int main()
{
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << "\n";
    Myclass* p = new Myclass;
    std::cout << "p = " << p << "\n";
    delete p;
}
```
