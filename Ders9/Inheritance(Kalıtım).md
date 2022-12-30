# KALITIM
Sınıflar arası **is a** relationship ilişkisini vurguluyor. Örneğin, her mercedes bir arabadır. Her aslan bir hayvandır. Dolayısıyla bir türden nesnenin başka bir türden kullanılabildiğini söylüyor. Is a relationship compositiona **has a** alternatif olarak düşünülebilir. Composition ile yapılabiliyorsa, composition daha avantajlı çünkü daha az bağımlılık oluşturuyor. 

Kalıtımda kaynak olarak kullanılan sınıf base class (taban sınıf), elde edilen ise derived class / Türemiş sınıf
  
OOP açısından kalıtımı neden kullanıyoruz?  

1. Code Reuse. Kodun yeniden kullanımı.  
Kodu tekrar yazmak yerine varolan kodun kulanımı. Türemiş sınıfın sınıfının public interface ine, Base sınıfının public interface indeki fonksiyonlar türler elemanlar dahil edilmektedir. Kalıtım yoluyla varolan bir taban sınıfı, onun bütün işlevselliğini alıp genişleterek yeni türemiş sınıf veya sınıflar oluşturabiliyorum.
 
2. Eski kodların yeni kodları kullanması (runtime polymorphism çalışma zamanı çok biçimliliği) (virtual dispatch).  
Mesela, tetris oyununu yazsak. Tetristeki elemanların şekli ve yetenekleri / dönme şekilleri belli. Bir genel bir sınıf yazsak, diğer tüm objeleri de bu sınıftan türetsek. Sonra müşteriden talep geldi. Eskiden olmayan yeni bir şekil istendi. Biz bu yeni şekli de taban sınıfımızdan türetirsek taban sınıfın kodları ile yeni yazdığımız kodları kullanabileceğiz. 

Kalıtımın OOP deki ile C++ taki anlamı farklı. C++ ta public private protected kalıtımlar var. C++taki public kalıtımı, OOP deki kalıtım olarak isimlendiriliyor.  

Mercedes -------> Car Burada car sınıfı taban sınıf, mercedes türemiş derived class.  
S500 --------> Mercedes -------> Car      **multi-level inheritance**.     

FaxModem  ----->  Modem ve Fax    **Multiple inheritance**
          	  
Name Lookup (isim arama): BLOK TÜREMIŞ SINIF .... TABAN SINIF NAMESPACE.  
Access kontrol türemiş sınıflar taban sınıfın public ve protected kısmına erişebilir.  
```cpp
class Base {
public:
    void func(int);

    void foo(int);

    class Nested {
    };

protected:
    void protectedFoo();

private:
    int mx;
};

class Der : public Base {
public:
    void func(int, int);

private:
    void foo()
    {
        foo(12);        //sentaks hatası namelookup Der sınıfı foo()
        Base::foo(12);
        protectedFoo(); //protected kısma türemiş sınıf ulaşır
        mx = 12;        //private bölüme türemiş sınıf bile ulaşamaz
    }

};

int main()
{
    Der::Nested nertedDer;  //Der sınıfı Base sınıfının public ögelerini publicine ekliyor.

    Base mybase;
    mybase.protectedFoo(); //geçersiz protected kısma client kod erişemez

    Der myder;
    myder.func(12);  //function overloading değil Sentaks hatası context control

    Der* p = &myder;
    p->Base::func(12);
}
```

## TABAN SINIF İLE TÜREMİŞ SINIF ARASINDAKİ TÜR DÖNÜŞÜMLERİ
Modelleme dillerinde kalıtım ilişkisi türemiş sınıftan taban sınıfa doğru çizin okla çizildiği için, türemiş sınıftan taban sınıfa doğru yapılan dönüşümlere UPCASTING deniyor. Bu dönüşümü sadece pointer ve referanslar için kullanmalıyız. (Der*(Der&)  ------> Base*(Base&))

**mybase = myder;**
Türemiş sınıf nesnesi içinde fiziksel olarak taban sınıf nesnesi vardır. Taban sınıfı türden nesneye türemiş sınıf nesnesini atayınca, fiilen türemiş sınıf nesnesi içerisindeki taban sınıf nesnesi kopyalamış oluruz. Türemiş sınıfın diğer veri elemanlarını kullanmamış oluruz. Bu eğer türemiş sınıf nesnesinin taban sınıfı nesnesine dönüşümü şeklindeyse dil izin verse de yanlıştır buna object slicing (Nesne dilimlenmesi) denir.  


## RUNTIME POLYMORPHISM / ÇALIŞMA ZAMANI ÇOKBİÇİMLİLİĞİ
Kalıtımda Airplane isimli taban sınıfımız olsun. Taban sınıfın interface indeki funcionlar 3'e ayrılabilir.
1. Hem bir arayüz / interface, hemde bir kod / implementation veren. (normal fonksiyonlar)
2. Hem bir arayüz / interface, hemde bir kod / **Default** implementation veren. İsteyen değiştirebilir. (virtual function)
3. bir arayüz / interface veriyor ama kod / implementation vermeyen. Benden türemiş sınıflar bu özelliği sağlamalı ve kodlarını kendileri implemente etmeliler. (pure virtual function)

İKİNCİ KATEGORIDEN EN AZ BIR FONKSIYONA SAHIPSE BÖYLE SINIFLARA POLIMORPHIC SINIF DENIYOR.
HEM BÖYLE SINIFLARA HEMDE BU SINIFLARDAN KALITIM YOLUYLA ELDE EDILEN SINIFLARA DENIYOR.
ÜÇÜNCÜ KATEGORIDEN EN AZ BIR FONKSIYON VARSA BÖYLE SINIFLARADA ABSTRACT / SOYUT CLASS DENIYOR. NESNE OLUŞTURMAK SENTAKS HATASI OLUYOR AMA BU SINIFI POINTER VEYA REFERANS SEMANTIĞI ILE KULLANABILIYORUZ.

```cpp
class Airplane {
public:
	//Nonvirtual function. Buna dokunmamak lazım
	void takeoff()
	{
		//kodlar
	} 		
	
	// Virtual Function Bunu ister override et, istersen de verileni kullan
	virtual void land()
	{
		//kodlar
	} 	
	//Pure virtual function Override etmek gerekir. Yoksa soyut sınıf olur ve nesne üretilemez.
	virtual void fly() = 0; 
};

int main()
{
	Airplane ax; //SENTAKS HATASI.Çünkü Abstract class türden nesne oluşturulamaz.
}
```
## VIRTUAL - POLYMORPHIC DISPATCH / SANAL GÖNDERİM

 Araba yarışı düşünelim şimdi. Car sınıfı kalıtımda kullanılacak taban sınıf olsun. Aşağıdaki fonksiyonda Car türünden kalıtımla elde edilmiş tüm sınıf nesnelerini aşağıdaki fonksiyona gönderebilirim. Burada arabaya özgü start run ... kodların çalıştığını düşünelim. Burada hangi fonksiyonun çağrılacağı runtime da belli oluyor. Eski kodların yeni kodları kullanması olayı bu. Eskiden olmayan bir skoda sınıfını Car sınıfından kalıtım yoluyla elde edersem, game koduna skoda nesnesi gönderilirse, skodanın nesnesinin fonksiyonu çağrılabilir. Buna runtime polymorphism deniyor.

```cpp
void game(Car &carref)
{
    car.start();
    car.run();
    car.accelerate();
    car.stop();
}
```
Statik tür, değişkenlerin türü çevirici program tarafından koda bakarak anlaşılıyorsa buna statik tür denir. Dinamik tür, türün ne olduğunun programın runtime da belli olmasıdır. carref statik türü Car& iken dinamik türü Mercedes olabilir.
Peki bunu nasıl gerçekleştireceğiz. Upcasting + virtual dispatch

```cpp
class Car {
public:
    virtual void start() 
    {
        std::cout << "Car has started\n";
    }
};

class Audi : public Car {
public:
    void start() override
    {
        std::cout << "Audi has started\n";
    }
    //int start(); virtual fonksiyonun geri dönüş değeri farklı olamaz. sentaks hatası
    
    void start (int) 
};

void car_game(Car& car)
{
    car.start();
}

int main()
{
    Audi myaudi;
    car_game(myaudi); //Myaudi& den Car& upcasting
    return 0;
}
/*
ÇIKTI : 
Car has started (virtual olmazsa) early/static binding   compile time
Audi has started (virtual + override)	 late/dynamic binding    run time
*/
```

Override C++11 de dile eklenen contexual keyword. Yazmazsak sentaks hatası olmaz ama yazılmalı. Yoksa birtakım kötü hata senaryolar oluşabilir. 
Override anahtar sözcüğü için [inceleyiniz.](http://plepa.com/2016/07/27/override-baglamsal-anahtar-sozcugu/)

```cpp
class Base {
public:
    virtual void func(int, int);
};

class Der : public Base {
public:
    void func(int, int) override; // override mutlaka yazılmalı
    //int func(int, int);  //BURASI SENTAKS HATASI. Return değer farklı
    void func(int); // hata yok ama override değil function overloading
    //OVERRIDE OLMASI IÇIN HEM RETURN DEĞERI TÜRÜ HEMDE IMZASI AYNI FONKSIYON BILDIRMELIYIZ.

};
```
Türemiş sınıf, taban sınıfının virtual fonksiyonunu override ederek, virtual dispatch mekanizmasından faydalanma hakkını
elde etmektedir. Virtual Dispatch: Eğer taban sınıfın bir sanal foksiyonu, bir taban sınıf pointerı ya da bir
taban sınıf referansı ile çağrılırsa çalışma zamanında çağrılan fonksiyon o pointer yada referans 
hangi türden sınıf nesnesini gösteriyorsa, o sınıfın üye fonksiyonu olacak.

```cpp
#include <iostream>

class Base {
public:
    virtual void func()
    {
        std::cout << "Base::func()\n";
    }
};

class Der : public Base {
private:
    void func() override //private olsa bile virtual dispatch devreye girer
    {
        std::cout << "Der::func()\n";
    }
};

void gfooPointer(Base* p)
{
    p->func();
}

void gfooRef(Base& baseref)
{
    baseref.func();
}

int main()
{
    Der myder;
    Base mybase = myder; //object slicing
    mybase.func();      // Base:func() virtual dispatch olmaz çümkü referans ya da pointer değil
    Base* baseptr = &myder; // upcasting Der* ----> Base*
    baseptr->func(); // Der:func()

    Base& baseref = myder; //upcasting Der& ---->Base&
    baseref.func(); // Der:func()

    gfooPointer(new Der); // Der:func() upcasting new Der idafesi Der* -----> Base*
    gfooRef(myder); // Der:func() upcasting Der& ---->Base&

}
```
## NON-VIRTUAL INTERFACE (NVI)
Virtual fonksiyonlar implementasyonla ilgili olduğu interface alanında bulunması mantıklı değildir. virtual fonksiyonu çağıracak public kısımda
tanımlanan non-virtual fonksiyonlar ile bu idiyom gerçekleştirilir. Invariant, sınıf/func ın doğru çalışması için mutlaka sağlanması gereken koşullardır. Bu invariantlar sağlanmadıysa bir yanlışlık vardır. Çağırmadan önce ve sonra invariantları kontrol edebiliriz böylelikle.
**Virtual fonksiyonlar private bölümde olmalılar.**
```cpp
#include <iostream>

class Base {
public:

    // public kısımda virtual function yok.
    void foo()
    {
        //kod
	func();
	//kod
    }

    void pvfoo()
    {
        //kod
        pvfunc();
        //kod
    }

private:
    virtual void func()
    {
        std::cout << "Base::func()\n";
    }

    virtual void pvfunc() = 0; //pure virtual func
};

class Der : public Base {
private:
    void func() override
    {
        std::cout << "Der::func()\n";
    }

    void pvfunc() override
    {
        std::cout << "Der::pvfunc()\n";
    }
};

int main()
{
    Der myder;
    myder.foo(); // Der::func() çağrıldı. this parametresi.
    myder.pvfoo(); // Der::pvfunc() çağrıldı.
}
```
## Virtual Constructor ve Virtual Destructor

C++ ta constructor virtual olamaz. Virtual keywordü constructor için kullanılamaz. Bu yüzden run time da türü belli olan nesnemizin kopyasını çıkarmak için virtual constructor idiom ya da Clone idiom denilen tekniği kullanacağız.
```cpp
#include <iostream>

class Car {
public:
    virtual Car* clone() = 0;

    void start()
    {
        start_impl();
    }

    virtual ~Car() = default;  // destructor public virtual olmalı
private:
    virtual void start_impl() = 0;
};

class Mercedes : public Car {
private:
    Car* clone() override
    {
        // new operatorüyle dinamik ömürlü bir nesne copy constructor ile oluşturuldu.
        return new Mercedes(*this);
        // return new Mercedes(); kopyası olmazdı.
    }

    void start_impl() override
    {
        std::cout << "Mercedes has just started\n";
    }
};

class Fiat : public Car {
private:
    Car* clone() override
    {
        // new operatorüyle dinamik ömürlü bir nesne copy constructor ile oluşturuldu.
        return new Fiat(*this);
    }

    void start_impl() override
    {
        std::cout << "Fiat has just started\n";
    }
};

void car_game(Car* p)
{
    Car* newcar = p->clone();
    p->start();
    newcar->start();
    std::cout << "----------------------------------------\n";
    getchar();

}

Car* create_random_car()
{
    switch (rand()%2) {
    case 0:
        std::cout << "Mercedes Case\n";
        return new Mercedes;
    case 1:
        std::cout << "Fiat Case\n";
        return new Fiat;
    }

    return nullptr;
}

int main()
{
    for (;;) {
        auto c = create_random_car();
        car_game(c);
        delete c;
    }
}
```
Sınıf polimorfik ise mutlaka taban sınıfın destructorunu virtual yapmalıyız böylece türemiş sınıf nesneleri taban sınıf pointerı ile delete edildiğinde veya handle edildiğinde bir problem olmasın.
```cpp
#include <iostream>

class Base {
public:
    virtual ~Base()
    {
        std::cout << "Base destructor\n";
    }
};

class Der : public Base {
    //...
public:
    ~Der()
    {
        std::cout << "Der destructor\n";
    }
};

int main()
{
    Base* baseptr = new Der;

    delete baseptr;  //undefined behavior
}
/*
ÇIKTI (non-virtual destructor): 
Base destructor UB(undefined Behavior)
ÇIKTI (virtual destructor): 
Der destructor
Base destructor
*/
```
destructor ya public virtual ya da protected non-virtual [olmalıdır.](https://necatiergin2019.medium.com/destructor-ya-public-virtual-ya-da-protected-non-virtual-olmal%C4%B1-9bade0adc886)
