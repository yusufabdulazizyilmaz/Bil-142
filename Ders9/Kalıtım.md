# KALITIM
Sınıflar arası is a relationship ilişkisini vurguluyor. Örneğin, her mercedes bir arabadır. Her aslan bir hayvandır. Dolayısıyla bir türden nesnenin başka bir türden kullanılabildiğini söylüyor. Is a relationship compositiona (has a) alternatif olarak düşünülebilir. Composition ile yapılabiliyorsa, composition daha avantajlı çünkü daha az bağımlılık oluşturuyor. 
  
OOP açısından kalıtımı neden kullanıyoruz?  
1. Eski kodların yeni kodları kullanması (runtime polymorphism çalışma zamanı çok biçimliliği)
Mesela, tetris oyununu yazsak. Tetristeki elemanların şekli ve yetenekleri / dönme şekilleri belli. Bir genel bir sınıf yazsak, diğer tüm objeleri de bu sınıftan türetsek. Sonra müşteriden talep geldi. Eskiden olmayan yeni bir şekil istendi. Biz bu yeni şekli de taban sınıfımızdan türetirsek taban sınıfın kodları ile yeni yazdığımız kodları kullanabileceğiz. 

2. Code Reuse. Kodun yeniden kullanımı.Kodu tekrar yazmak yerine varolan kodun kulanımı

Kalıtımın OOP deki ile C++ taki anlamı farklı. C++ ta public private protected kalıtımlar var.
C++taki public kalıtımı, OOP deki kalıtım olarak isimlendiriliyor.
Kalıtımda kaynak olarak kullanılan sınıf base class, elde edilen ise  derived class / Türemiş sınıf
Mercedes -------> Car Burada car sınıfı taban sınıf, mercedes türemiş derived class.
S500 --------> Mercedes -------> Car multi-level inheritance
          ----->	Modem
FaxModem                            Multiple inheritance
          ----->	Fax

Türemiş sınıf nesnesi içinde fiziksel olarak taban sınıf nesnesi
Name Lookup (isim arama): BLOK TÜREMIŞ SINIF .... TABAN SINIF NAMESPACE
Access kontrol türemiş sınıflar taban sınıfın public ve protected kısmına erişebilir.
cpp

class Base{
public: 
	void func(int);
};
class Der : public Base{
public: 
	void func(int,int);
};
int main()
{
	Der myder;
	//myder.func(12); 
}



TABAN SINIF İLE TÜREMİŞ SINIF ARASINDAKİ TÜR DÖNÜŞÜMLERİ

Modelleme dillerinde kalıtım ilişkisi türemiş sınıftan taban sınıfa doğru çizin okla çizildiği için, türemiş sınıftan taban sınıfa doğru yapılan dönüşümlere UPCASTING deniyor. Bu dönüşümü sadece pointer ve referanslar için kullanmalıyız. (Der*(Der&)  ------> Base*(Base&))

mybase = myder;
Taban sınıfı türden nesneye türemiş sınıf nesnesini atayınca, fiilen türemiş sınıf nesnesi içerisindeki taban sınıf nesnesi kopyalamış oluruz. Türemiş sınıfın diğer veri elemanlarını kullanmamış oluruz. Bu eğer türemiş sınıf nesnesinin taban sınıfı nesnesine dönüşümü şeklindeyse dil izin verse de yanlıştır buna object slicing (Nesne dilimlenmesi) denir.  
