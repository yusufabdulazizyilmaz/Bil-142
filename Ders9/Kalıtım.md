# KALITIM
Bu aslında OOP de kullanılan genel terim. Sınıflar arası ilişki biçimini belirliyor. Is a relationship ilişkisini vurguluyor. Bu bir türden nesnenin başka bir türden kullanılabildiğini söylüyor. Is a relationship compositiona alternatif olarak düşünülebilir.Composition ile yapılabiliyorsa, composition daha avantajlı çünkü daha az bağımlılık oluşturuyor. 
Kalıtımın OOP deki ile C++ taki anlamı farklı. C++ ta public private protected kalıtımlar var.
C++taki public kalıtımı, OOP deki kalıtım olarak isimlendiriliyor.  
OOP açısından kalıtımı neden kullanıyoruz?  
1. Eski kodların yeni kodları kullanması (runtime polymorphism çalışma zamanı çok biçimliliği)
Mesela, tetris oyununu yazsak.Bunu C de yazmak istesek.Mantığınıda biliyoruz
bu oyunun.Bunları C de düşünsek Yer şekli ayrı ayrı structlar olarak düşünüp
herbirinin kodunu ayrı ayrı yazacağız.Sonra müşteriden talep geldi.Eskiden olmayan
yeni bir şekil istendi.biz kodun genelinde switch else if lerde değişiklik yapmak
zorunda kalırız.
OOP de kalıtımdan faydalansak.Tetris teki elemanların şekli ve yetenekleri / dönme şekilleri belli.
Bir genel bir sınıf yazsak, diğer tüm objeleride bu sınıftan türetsek nasıl olur.
Kalıtımda oluşturunca eskiden oluşturduğumuz if else switchlerde değişiklik yapmayacağız.

2. Code Reuse. Kodun yeniden kullanımı.Kodu tekrar yazmak yerine varolan kodun kulanımı
