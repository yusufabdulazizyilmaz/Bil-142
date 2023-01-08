# Runtime Type Information (RTTI)
Runtime polimorfizminin(virtual dispatch) hayatımıza girmesiyle static tür kavramının dışında bir de dinamik tür kavramıyla tanıştık. C++ ta bir nesnenin 
run time türünü öğrenmek büyük ihtimalle kötü bir tasarımın sonucu olabilir. Virtual dispatch zaten bunu bilmeden kullanması olanağını sağlıyor. 
Runtime polimorfizminin sağladığı temel avantaj bu. Yukarıdaki kodlar aşağıdakilere bağımlı hale gelmemiş oluyor. Ama öyle durumlar var ki nesnenin dinamik
türünü sorgulamamız gerekiyor. Ya tasarımsal durum ya da belirli kodların bize sunulmamış olmasından ötürü olabilir. İstediğimizi yapmak için başka bir 
araç olmayabilir.

C++ ta nesnelerin türlerinin çalışma zamanında anlaşılmasına yönelik 3 adet araç seti var.  
dynamic_cast -> tür dönüştürme operatorü.  
typeid -> bir operator.  
typeinfo -> bu da bir sınıf. 
## DYNAMIC_CAST Tür Dönüştürme Operatörü
Base classtan derived classa dönüşüm var mı yok mu ona bakıyor. Programın çalışma zamanında bir down-casting in güvenli olarak yapılıp yapılamadığını test ediyor.

**dynamic_cast<target type>(expr);** 
Burada expression polymorphic sınıf türünden olamlıdır (virtual functiona sahip olmalı). Aksi takdirde sentaks hatası. Polymorphic sınıf türünden olmadığını görürse compile time da sentaks hatası verir.    
```cpp
Mercedes *p = dynamic_cast<Mercedes *>(carptr);
```
Runtime da bu kod çalıştığında 2 ihtimal var.  
1 - Carptr nin değeri Fiat ve Fiat124 gibi Fiat taban sınıfından üretilmiş Fiat124 gibi bir nesnesinin adresiyse dynamic cast operatörü başarılı olacak 
  ve bize Fiat nesnesinin adresini üretecek. ve p yi bir Fiat olarak kullanabileceğiz.  
2 - Diyelim ki buraya gelen araba Skoda olsun, burada dynamic_cast başarısız olacak ve nullptr geri döndürecek.
Aşağıdakini yazabiliriz yani.  
```cpp
//İdiyom
if(Fiat *p = dynamic_cast<Fiat *>(carptr))
{
// Fiat ise buraya girecek
}
/*
Fiat *p = dynamic_cast<Fiat *>(carptr)
if (!p).   //(p != nullptr)
{
}
*/
void car_game(Car* carptr)
{
    carptr->start();
    //Arabanın Fiattan kalıtım yoluyla elde edilen sınıfları da kapsıyor. Yani Fiat124 olsa da içerisine girecek.
    if (Fiat*p = dynamic_cast<Fiat*>(carptr)) {
        p->activate_aebs();
    }
    carptr->run();
    carptr->stop();
}

```
## TYPEID Operatörü ve TYPEINFO Sınıfı

<typeinfo> başlık dosyasında bulunuyor. Bu operatörün operandı ya bir ifade olacak ya da bir tür olacak. 
typeid(x) --> bu typeinfo header file da tanımlanan typeinfo isimli sınıf türünden bir nesneye const referans. TYPEINFO ÖYLE BİR SINIFKİ BU TÜRDEN NESNE OLUŞTURMAK DOĞRUDAN MÜMKÜN DEĞİL. ÇÜNKÜ BU SINIFIN DEFAULT CTORU YOK COPY CTORU DELETE EDİLMİŞ. TYPEINFO SINIFINI KULLANMANIN YOLU TYPEID İLE BİR İFADE OLUŞTURMAK.   
```cpp
#include <typeinfo>
#include <iostream>

int main()
{
    int x = 45;
    typeid(std::string); //Herhangi bir tür olabilir.
    std::cout << typeid(x).name() << "\n";  //int
    typeid(x)==typeid(int); //ifadelerin türleri aynıysa o zaman boolean true döndürecek
    std::cout << typeid(x++).name() << "\n"; //Unevaluated Contex
    std::cout << "x = " << x << "\n";  // 45 çıktı. İşlem kodu üretmiyor
}
```
typeid polimorfik türler için kullanma mecburiyeti yok. Polimorfik olmayan türler için typeid operatörü tamamen static tür bilgisine yönelik bir typeinfo nesnesi döndürüyor. Polymorphic türler sözkonusu olunca typeid operatörün eriştiği typeinfo bilgisi dinamik türe ilişkin.
```cpp 
void car_game(Car* carptr)
{
    carptr->start();
    // burada runtime da if in içine, *ptr a gelen araba sadece Fiat ise girecek. Fiat124 ise girmeyecek
    if(typeid(*carptr) == typeid(Fiat)) {			
        static_cast<Fiat *>(carptr)->activate_aebs();
    carptr->run();
    carptr->stop();
}
```
DYNAMIC CAST İLE CİDDİ FARK VAR. FİATTAN TÜREMİŞ OLAN FIAT124 GELDİĞİNDE VE BUNU TYPEID NİN OPERATÖRÜ YAPTIĞIMIZDA FİAT İLE KARŞILAŞTIRINCA TRUE DÖNDÜRMÜYOR
