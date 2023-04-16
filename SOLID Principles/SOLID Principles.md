# Design Patterns (Tasarım Kalıpları)
* Analiz uygulama geliştireceğimiz konuyu anlama, parçalara ayrılma sürecidir. Tasarım ise çözümünün kavramsal tanımıdır. ve 
Analizde ne yapmamız gerektiğini araştırıyoruz. Tasarımda onun nasıl yapmamız gerektiğini araştırıyoruz ve tasarım implementasyon değildir 
daha sonra implementasyona dönüştürülür.  
* Yazılım geliştirmede değişkenlik çok önemli. Yazılımlar doğası gereği sürekli değişim içindeler.
Değişim normal.Yeni talepler olabilir, programın başka bir donanıma taşınması, bug fixing, performans iyileştirmeleri... 
Kötü bir tasarım sözkonusu ise değiştirmek artık imkansız hale geliyor.
* **Rigidity(Katılık)** Kodun değişime karşı direnç göstermesi.
* **Fragility(Kırılganlık)** Değişiklik yaptığımızda o değişikliğin başka yerlerde de etkilerinin oluşması.
* **Immobility(Taşınmazlık)** Projenin belirli parçalarının bağımlılıklar yüzünden başka yerde kullanılmasının zorlaşması.
* **Viscosity(Akışkanlık)** Tasarıma uygun iyi çözüm, tasarıma uygun olmayan bir çözüme göre çok daha zor hale gelmesi. 
* **Needless Complexity(Gereksiz Karmaşıklık)** Fayda sağlamayan öğelerin bulunup ve giderek artması.
* **Needless Repetition(Gereksiz Tekrar)** Aynı kodun sürekli tekrar etmesi.
* **Opacity(Anlaşılmazlık)** Kodları okumak ve anlamak zor.

TASARIMLA İLGİLİ ÇOK ÖNEMLİ 2 KAVRAM COHESION VE COUPLING'ten önce MODÜLARİTEDEN bahsetmeliyiz.
* **MODÜLARITE** Yazılım programı tipik olarak modüler bir yapıda. Modüllerin de kendi bileşenleri var ve biz bunları ayrı varlıklar olarak ele alıyoruz.
* **COHESION** Bir modülün elemanlarının birbirine bağlılığının ne kadar güçlü ve ne kadar zayıf olduğunun bir ölçüsü.
* **COUPLING** Programı oluşturan modüllerin birbirleri arasındaki ilişkilerin kalitesini niteleyen ölçü.  
**İstediğimiz couplingin düşük cohesionun yüksek olması.**
# SOLID Principles

[S]ingle Responsibility Principle (SRP)  
[O]pen Closed Principle (OCP)  
[L]iskov Substitution Principle(LSP)   
[I]nterface Segreagation Principle(ISP)   
[D]ependancy Inversion Principle(DIP)   

## Single Responsibility Principle(SRP)
Bir modül sadece ve sadece tek bir nedenden ötürü değişmeli. Bir modül sadece tek bir aktöre karşı sorumluluk taşımalıdır. Aktör  = User + Stakeholders  
Burada modül derken neler kastediliyor.En kısa tanımla, modül kaynak dosyadır.
## Open Closed Principle (OCP)
Modüller değişikliğe karşı kapalı ama genişletmeye karşı açık olmalıdır. Bir değişiklik implemente etmek için varolan kodu değiştirmek yerine yeni kod yazmak.
Varolanı değiştirme, kod ekle.
## Liskov Substitution Principle(LSP) 
Polimorfizmin güvenli kullanımına ilişkin bir ilke. Taban sınıf nesnesinin kullanıldığı yerde onun yerine türemiş sınıf nesnesi de kullanılabilmelidir.
* Preconditions : İşlemden önce sağlanması gereken şartlar. Preconditionlar daha sıkı hale getirilmemeli ama daha gevşek hale getirilebilir.
* Postconditions : Func işini yaptıktan sonra sağlanması gereken şartlar. Function çalıştıktan sonra nesnenin herhangibir değerinin spesifik bir değer olması gibi...
* Variantlar : Sınıfın değişmezleri.

LSP NİN ÇİĞNENDİĞİ NASIL ANLAŞILIR  
- Taban sınıfın bir metodunu override eden türemiş sınıf funcının tamamen yeni davranış sergilemesi.
- Türemiş sınıfın taban sınıfın funcını override ediyor ama override edilmiş funcın kodu boş.
- Taban sınıftan alınan bir func için bir dökümantasyon yapılmış."Clientlar tarafından bu func çağrılmasın"
## Interface Segregation Prensibi(ISP)
Client kodlar kullanmadıkları arayüzlere bağımlı olmaya zorlanmamalıdır. Sorumlulukların hepsini tek bir arayüze toplamak yerine daha özelleştirilmiş birden fazla arayüz oluşturmayı tercih etmemizi söyleyen prensiptir.

## Dependancy Inversion Principle(DIP)
Yüksek seviyeli modüller daha aşağı seviyedeki modüllere bağlı olmamalı. İkisi de soyutlamalara bağlı olmalı.  
Üst Seviye Sınıflar -> Soyutlama Katmanı -> Düşük Seviye Sınıfları

* Uygulamada kimlik doğrulama için farklı sınıflar olduğunu düşünelim. Bir kod yazacağız ve bu kod onlardan birini seçecek. Eğer böyle yaparsak üst seviyedeki modüller daha alt seviyedekilere bağımlı hale geliyor.

Bu ilkeye göre yapılması gereken authentication hizmeti için bir soyutlama yapmak.
Authentication bir abstract class olacak onlarda authentication sınıfından kalıtımla elde edilecek.
Böylece daha üst seviyedeki katman doğrudan authentication interfaceini kullanacak.
Oraya authentication interfaceinden kalıtım yoluyla gelen sınıf türünden nesne dışarıdan gönderilecek.
Bu kural kodun esnekliğini koruyor ve tekrar kullanılabilirliğini sağlıyor.
