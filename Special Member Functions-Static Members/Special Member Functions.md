# SPECIAL MEMBER FUNCTIONS
Bu fonksiyonlar dilin kuralları tarafından garanti altına alınmış, belirli koşullar sağlandığında derleyici tarafından yazılabilen fonksiyonlara
Special Member Functions denir. Buna derleyicinin bu kodu default etmesi deniyor.   
* DEFAULT CONSTRUCTOR   
* DESTRUCTOR   
* COPY CONSTRUCTOR 
* COPY ASSIGNMENT OPERATOR FUNCTION  
* MOVE CONSTRUCTOR C++11
* MOVE ASSIGNMENT OPERATOR FUNCTION C++11 
```cpp
class A {
public:
    A(); //varsayılan kurucu işlev (default constructor)
    ~A(); //sonlandırıcı işlev (destructor)
    A(const A&); //kopyalayan kurucu işlev (copy constructor)
    A& operator=(const A&); //kopyalayan atama işlevi (copy assignment operator function)
    A(A&&); //taşıyan kurucu işlev (move constructor)
    A& operator=(A&&); //taşıyan atama işlevi (move assignment operator function)
};
```
```cpp
#include <iostream>
class A {
};

class Myclass {
public:
    // default constructor
    Myclass()
    {
        std::cout << "Myclass default Ctor this = " << this << "\n";
    }

    // destructor
    ~Myclass()
    {
        ma.~A();	// A nesnesinin destructor
        std::cout << "Myclass destructor this = " << this << "\n";
    }

    // Copy constructor
    Myclass(const Myclass& other)
            :ma{other.ma}, mival{other.mival}
    {
        std::cout << "Myclass copy Ctor this = " << this << " &other = " << &other << "\n";
    }

    // COPY ASSIGNMENT FUNCTION
    Myclass& operator=(const Myclass& other)
    {
        if (this==&other) // self assignment
            return *this;
        ma = other.ma;
        mival = other.mival;
        std::cout << "Myclass copy operator function this = " << this << " &other = " << &other << "\n";
        return *this;
    }

    // Move constructor
    Myclass(Myclass&& other)
            :ma{std::move(other.ma)}, mival{other.mival}
    {
        std::cout << "Myclass move Ctor  this = " << this << " &other = " << &other << "\n";
    }

    // MOVE ASSIGNMENT FUNCTION
    Myclass& operator=(Myclass&& other)
    {
        ma = std::move(other.ma);
        mival = other.mival;
        std::cout << "Myclass move operator function this = " << this << " &other = " << &other << "\n";
        return *this;
    }

private:
    A ma;
    int mival{5};
};

int main()
{
    Myclass m1;
    Myclass copyM1 = m1;
    Myclass copyAssignM1;
    copyAssignM1 = m1;
    Myclass moveM1 = std::move(m1);
    Myclass moveAssignM1;
    moveAssignM1 = std::move(copyM1);
}

/* ÇIKTI =
Myclass default Ctor this = 0x16b45f7b8
Myclass copy Ctor this = 0x16b45f7b0 &other = 0x16b45f7b8
Myclass default Ctor this = 0x16b45f79c
Myclass copy operator function this = 0x16b45f79c &other = 0x16b45f7b8
Myclass move Ctor  this = 0x16b45f794 &other = 0x16b45f7b8
Myclass default Ctor this = 0x16b45f78c
Myclass move operator function this = 0x16b45f78c &other = 0x16b45f7b0
Myclass destructor this = 0x16b45f78c
Myclass destructor this = 0x16b45f794
Myclass destructor this = 0x16b45f79c
Myclass destructor this = 0x16b45f7b0
Myclass destructor this = 0x16b45f7b8 */
```

Rule of Zero : Özel üye fonksiyonların mümkünse hiç birisini programcı olarak sen yazma bırak senin yerine derleyici yazsın.  
Rule of Five : Özel üye fonksiyonlarından birisini yazdıysan geri kalan hepsini yaz.  
Rule of zero/five için [inceleyiniz](https://www.modernescpp.com/index.php/rule-of-zero-or-six) 

NE ZAMAN DERLEYİCİ BİZİM İÇİN SPECİAL MEMBER FUNCTİON FUNCTİON YAZAR NE ZAMAN YAZMAZ ?  
Özel üye fonksiyonların ne zaman yazıldığı ile ilgili [inceleyiniz](http://plepa.com/2017/03/15/siniflarin-ozel-islevlerinin-derleyici-tarafindan-yazilmasi/).  
Belirli koşullar oluştuğunda compiler special member functionların yazılmasını garanti ediyor.  
* NOT DECLARED (Yok - Bildirilmemiş)  
* IMPLICITLY DECLARED (Derleyicinin bu fonksiyonu kendisinin bildirmesi).  
** Defaulted (Derleyici durumdan vazife çıkarıp fonk. kodunu kendisinin yazması demek).   
** Deleted (Belirli durumlarda derleyici kurallar gereği bir özel fonksiyonu yazıyor / default ediyor ama)
		  (default ettiğinde dilin kurallarını çiğneyen bir sentaks hatası oluşunca, o fonksiyonu delete ediyor)   
* USER DECLARED (DEFINED/DEFAULTED/DELETED)
```cpp
class Myclass {
public:
    //Myclass(); Bu user declared (defined)
    //Myclass() = default; // Default ctor bildirilmiş ama derleyicinin default etmesi istenmiş. Yani kodunu derleyici yazacak.
    //Myclass() = deleted; // Fonksiyon var ama çağrı yapılırsa deleted edildiği için SENTAKS HATASI.
};
```

Özel Durumlar:  
1 - SINIFIN COPY CTORUNU VE COPY ASSIGN LARINI BİLEREK İSTEYEREK DELETE EDECEĞİZ. Böylece copy memberlar delete edildiği için sınıf türünden nesneler ne kopyalanabilir ne de taşınabilir. Copy memberlar için bildirim olması, move memberlar için not declared olmasına yetiyor.
```cpp
class Myclass {
public:
    Myclass(const Myclass&) = delete;

    Myclass& operator=(const Myclass&) = delete;
};
```
2 - AŞAĞIDAKI TÜRDEN CLASS OBJELERINI KOPYALAYAMAYIZ AMA TAŞIYABILIRIZ.
```cpp
class Myclass {
public:
    Myclass(const Myclass&) = delete;

    Myclass& operator=(const Myclass&) = delete;

    Myclass(Myclass&&);

    Myclass& operator=(Myclass&&);
};
```
