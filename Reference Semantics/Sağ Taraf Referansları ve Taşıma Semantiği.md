# R VALUE REFERANS
Sağ taraf referansları C++11 standartlarıyla C++ diline eklenmiş en önemli araçlardan biridir. X bir tür olmak üzere, X&& türüne X‘e sağ taraf referansı denir. Sağ taraf referanslarına sağ taraf değerleri (PR value expression) bağlanabilir.  
R value referanslar için [inceleyiniz](http://plepa.com/2016/10/04/sag-taraf-referanslari-1/).

Standart move işlevi (işlev şablonu) sol taraf değerini sağ taraf değerine dönüştürüyor. Yani x bir sol taraf değeri olsa da move işlevinin geri dönüş değeri bir sağ taraf değeridir. ismi move olduğuna göre bu fonksiyon move işlemi yapıyor gibi düşünülebilir ama değil.
Bu bir tür dönüşümü yapıyor. Lvalue exp i Rvalue exp e dönüştürüyor.Rvalue exp ise yine Rvalue exp olarak dönüyor std::move() bunun oluşturduğu ifade bir rvalue exp.
```cpp
  std::move(x)
  static_cast<X&&>(x)
```
# MOVE SEMANTICS
Aşağıdaki örnekte y'nin biraz sonra hayatının biteceğini ya da tekrar kullanılmayacağını varsayınız. Dilin kuralı gereği x nesnesi hayata gelirken
copy constructor çağrılacaktık.

```cpp
  A x = y;
```
Yine kaynağı kopyalarız(hayatı bitecek nesne yani) ve yeni bir kaynak elde ederiz. C++ 11 den önce compiler özel optimizasyon yapmazsa böyle durumlara çok rastlanıyordu. Yani nesne ölecek buna rağmen nesneyi kopyalıyoruz ve sonrada destructor kaynağı geri veriyor. Burada nasıl kod çalışırsa yüksek verim elde edilir ? 
Gereksiz kopyalama engellenirse. NASIL? Nesnenin hayatı bitiyor eminiz. başka hiçbir kod bunu kullanamayacak bundan da eminiz. O zaman bu kaynağı iade etmek yerine hayata gelen nesne bu kaynağı çalsın.  
C++ 11 den önce compiler bunu anlayamıyordu, kaynak kopyalıyordu.Dilin araçları compile time da bunun hayatını biteceğini anlayıp 
alternatif bir kod çalıştırmaya yeterli değildi. Sentaks izin vermiyordu. Bunu yapabilmek için dile eklenen sentaks aracı SAĞ TARAF REFERANSIdır. Eğer R value exp ise, hayatı bitecek başka kodun bunu kullanma ihtimali yok. O yüzden kaynağı çalınabilir.
```cpp
class Myclass() { }
void func(const Myclass&); // const sol taraf referansı
void func(Myclass && r); // sağ taraf referansı.
func(lval) 1. çalışır
func(rval) 1 - 2 viable ama 2. çalışır
```

Taşıma semantiği için [izleyiniz](https://www.youtube.com/watch?v=Bt3zcJZIalk)
