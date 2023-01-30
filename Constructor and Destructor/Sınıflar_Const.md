# Sınıfların Const Üyeleri
Const doğruluğu kodun kalitesini birinci dereceden etkileyen bir konudur ve const olması gereken her şey const olmalıdır.
Const üye fonksiyonlar için const anahtar sözcüğünü hem fonksiyonunun bildiriminde hem de tanımında, parametre ayracının sağına yerleştirmek gerekir.  
* Const üye fonksiyonlar içinde sınıfın nonconst veri elemanlarını değiştiremeyiz ama erişebiliriz.  
* Const üye fonksiyonlar içinde sınıfın nonconst fonksiyonlarını çağıramayız.  
* Const sınıf nesneleri için sınıfın nonconst fonksiyonlarını çağıramayız.  
```cpp
class Nec {
public:
    void func(int x);

    void foo() const; // const member function bu fonksiyon accesser ve gizli parametre değişkeni const Nec*

private:
    int mx;
};

void Nec::foo()  //SENTAKS HATASI. Sonda const yok.
{
    mx = 20;   //SENTAKS HATASI. Elemanlar değiştirilemez.
    std::cout << mx << '\n';  // geçerli mx değiştirilemez ama erişilebilir
    Nec mynec;
    mynec.mx = 23 //geçerli çünkü gizli const Nec* nesnesi ile erişmedim
    func(12); //geçersiz nonconst fonksiyonu çağıramayız
}

void Nec::func(int x)
{
    mx = x; //geçerli
    foo();  // geçerli Nec* dan const Nec* a dönüşüm 
}
int main()
{
    const Nec cnstMynec{};

    // burada mynec const türden. mynec.func() ta ise gizli const Nec * türden nesne gönderiliyor
    // const gönderiyoruz ama class member func da const olarak bildirilmemiş. cont Nec * dan
    // Nec * a dönüşüm SENTAKS HATASI
    cnstMynec.func(12);
    // geçerli. const Nec* ile çağrılıyor ve class içinde const ile bildirilmiş.
    cnstMynec.foo();

    Nec mynec{};
     
    mynec.func(12); // geçerli

    mynec.foo(); // geçerli

}
```
sonuç olarak const üye fonksiyonlar const nesnelerin kullanabildiği fonksiyonlardır. print() fonksiyonunu düşünelim. Bu fonksiyon mutlaka const olmalı 
eğer const tanımlamazsak const bir nesne ile çağıramayız. Gidip const nesnemizden constluğu çıkarmamız gerekir. 1 yerde bile const olması gereken şeyi const
yapmazsak yavaş yavaş her yerden constluğu silmemiz gerekir. Bu yüzden const olması gereken tüm her şey const olmalıdır. Const olmayan nesneler 
için bir üye fonksiyonun const olup olmaması onun çağrılmasına engel değildir.    
CONST ÜYE FONKSİYON NE DEMEK ?  
YANLIŞ CEVAP : SINIFIN VERİ ELEMANLARINI DEĞİŞTİRMEME GARANTİSİ VEREN İŞLEVDİR.  
DOĞRU CEVAP : BU FONKSİYON NESNEYİ DEĞİŞTİRMEYECEK DEMEK. yani NESNENİN PROBLEM DOMAİNİ İÇİNDEKİ SOYUTLANMIŞ ANLAMINI DEĞİŞTİRMEYECEK.  
```cpp
class Fighter {
public:
    // const mu nonconst mu olmalı
    // Probleme göre değişir. belki shoot her çağrıldığında birşeyler değişecek. mermi azalacaksa nonconst
    void shoot();

    // const mu nonconst mu olmalı
    // Probleme göre değişir Yakın ihtimal const ama her tell_name() çağrıldığında bir can gidiyorsa her şey değişir.
    void tell_name();
};

int main()
{
    Fighter myfigher;
    myfigher.shoot();
}
```
Nesnenin problem domainninde anlamını değiştirmeyecek veri elemanları olabilir mi? olursa bunları const üye fonksiyonlarda kullanmamız en doğal hakkımız.
Bunu nasıl gerçekleştirebiliriz.
```cpp
class Fighter {
public:
    int get_age() const;

private:
    int debug_call_count{}; // kaç kere get_age() fonksiyonu çağrılmış onu hesaplıyor.
};

int Fighter::get_age() const
{
    ++debug_call_count; //sentaks hatası const üye fonksiyonda sınıfın veri elemanını değiştiremeyiz.
}
```
İşte tam burada **mutable** anahtar sözcüğü imdadımıza yetişiyor. Mutable keywordü ile bu değişkenin değişmesi problem domainindeki anlamını değiştirmiyor diyoruz derleyiciye. Dolayısıyla const üye fonksiyonlarda değeri değiştirilebilir oluyor.
```cpp
class Fighter {
public:
    int get_age() const;

private:
    mutable int debug_call_count{};
};

int Fighter::get_age() const
{
    ++debug_call_count; //geçerli çünkü debug_call_count mutable.
}
```
