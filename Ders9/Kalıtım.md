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

TABAN SINIF İLE TÜREMİŞ SINIF ARASINDAKİ TÜR DÖNÜŞÜMLERİ

Modelleme dillerinde kalıtım ilişkisi türemiş sınıftan taban sınıfa doğru çizin okla çizildiği için, türemiş sınıftan taban sınıfa doğru yapılan dönüşümlere UPCASTING deniyor. Bu dönüşümü sadece pointer ve referanslar için kullanmalıyız. (Der*(Der&)  ------> Base*(Base&))

**mybase = myder;**
Türemiş sınıf nesnesi içinde fiziksel olarak taban sınıf nesnesi vardır. Taban sınıfı türden nesneye türemiş sınıf nesnesini atayınca, fiilen türemiş sınıf nesnesi içerisindeki taban sınıf nesnesi kopyalamış oluruz. Türemiş sınıfın diğer veri elemanlarını kullanmamış oluruz. Bu eğer türemiş sınıf nesnesinin taban sınıfı nesnesine dönüşümü şeklindeyse dil izin verse de yanlıştır buna object slicing (Nesne dilimlenmesi) denir.  


RUNTIME POLYMORPHISM / ÇALIŞMA ZAMANI ÇOKBİÇİMLİLİĞİ
Kalıtımda Airplane isimli taban sınıfımız olsun. Taban sınıfın interface indeki funcionlar 3'e ayrılabilir.
1. Hem bir arayüz / interface, hemde bir kod / implementation veren. (normal fonksiyonlar)
2. Hem bir arayüz / interface, hemde bir kod / **Default** implementation veren. İsteyen değiştirebilir. (virtual function)
3. bir arayüz / interface veriyor ama kod / implementation vermeyen. Benden türemiş sınıflar bu özelliği sağlamalı ve kodlarını kendileri implemente etmeliler. (pure virtual function)

2. KATEGORIDEN EN AZ BIR FONKSIYONA SAHIPSE BÖYLE SINIFLARA POLIMORPHIC SINIF DENIYOR.
HEM BÖYLE SINIFLARA HEMDE BU SINIFLARDAN KALITIM YOLUYLA ELDE EDILEN SINIFLARA DENIYOR.
3. KATEGORIN EN AZ BIR FONKSIYON VARSA BÖYLE SINIFLARADA ABSTRACT / SOYUT CLASS DENIYOR. NESNE OLUŞTURMAK SENTAKS HATASI OLUYOR AMA BU SINIFI POINTER VEYA REFERANS SEMANTIĞI ILE KULLANABILIYORUZ.
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
	virtual void fly() = 0; //Pure virtual function Override etmek gerekir. Yoksa soyut sınıf olur ve nesne üretilemez.
};

int main()
{
	Airplane ax; //SENTAKS HATASI.Çünkü Abstract class türden nesne oluşturulamaz.
}
```
