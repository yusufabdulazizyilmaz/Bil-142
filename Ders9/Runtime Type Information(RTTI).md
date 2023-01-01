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
## DYNAMIC CAST
Base classtan derived classa dönüşüm var mı yok mu ona bakıyor. Programın çalışma zamanında bir down-casting in güvenli olarak yapılıp yapılamadığını test ediyor.

**dynamic_cast<target type>(expr);**.  
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
    if (Fiat*p = dynamic_cast<Fiat*>(carptr)) {
        p->activate_aebs();    //Arabanın Fiattan kalıtım yoluyla elde edilen sınıflarıda kapsıyor. Yani Fiat124 olsa da içerisine girecek.
    }
    carptr->run();
    carptr->stop();
}

```
