# SINIFLAR (CLASSES)
Sınıf (class) nesne yönelimli programlama tekniğinin uygulanmasına olanak sağlayan, C dilinde olmayan yeni bir
yazılımsal birimdir. Sınıflar, C‟deki yapılara benzetilebilir. Ancak C‟deki yapılar yalnızca eleman (member)
içerirken, C++‟da sınıflar yapılardan fazla olarak hem veri elemanı hem de üye işlevleri (member function) içerir.
Sınıflar, yapılara göre ek bir çok özelliğe sahiptir. Bu özelliklerin çoğu Nesne Yönelimli Programlama Tekniği‟ni
destekleme amacıyla eklenmiştir.  
Nasıl bir "yapı" türü programcı tarafından tanımlanmış bir tür (user defined type) ise, sınıflar da programcının
tanımlamış olduğu türdür. Programcı, önce yeni bir türü derleyiciye tanıtır, daha sonra bu yeni türden nesne,
gösterici, referans tanımlayabilir. Sınıfları kullanabilmek için ilk yapılması gereken işlem, bir sınıfın tanımını
yapmaktır. Bir sınıfın tanımını yapmak, bu sınıf hakkında derleyiciye bilgi vermek anlamına gelir.
Derleyici aldığı bilginin sonucunda, bu sınıf türünden bir nesne tanımlanması durumunda, hem bellekte ne
kadar yer ayıracağını bilir, hem de programcının yazmış olduğu koda ilişkin bazı kontrol işlemlerini yapma
olanağına kavuşur. 
```cpp
class Nec {
};
```
classları yukarıdaki gibi boş şekilde tanımlarsak empty class olur. Empty class türden nesneler memory de 1 byte yer kaplar.
Küme parantezi içerisinde(Declerative Region) bildirilen varlıklara sınıfın elemanları deniyor. Bu memberlar 3 kategoriye ayrılır.
1- Data members(veri elemanları)
  a - static
  b - nonstatic
2- Member function(üye fonksiyon)
  a - static
  b - nonstatic
3 - Member Type - Type Member - Nested Type(Tür elemanları)
```cpp
class Nec {
    int mx; // nonstatic data member
    static int y; // static data member.
    void func123(int, int);  // nonstatic member function
    static void foo(int); // static member function
    using value_type = int; //type member 
    value_type myInt = 5; // nonstatic data member
    class Iterator{  // Nested type
    };
};
```
Nonstatic data memberlar sınıf boyutunu (sizeof) artırıyor. fiziksel olarak class içinde yer alıyorlar. Fakat static data memberlar sınıf sizeofuna girmiyor.  
Member functionlar sınıfın içinde bildiriliyor ama içinde yer kaplamıyor.
Sınıf türden yeni bir nesne yaratılınca bu sınıf türden instance yaratılmış oluyor. **Nec n1; // instantiate nesne oluşturmaya karşılık gelen terim.**
```cpp
class Point {
    double mx, my, mz;
};

int main()
{
    Point a, b, c;
}
```
## ACCESS CONTROL - ERİŞİM KONTROLÜ
Sınıfın herhangi bir üyesi erişim kontrolü açısından 3 kategoriden birine ait olmalıdır.
a - Public members: Herkese açık kodlar
b - Private members: Sadece sınıfın kendisinin kullanacağı kodlar
c - Protected members: Inheritance konusunda görülecek. Clientlara yasak ama kalıtım yoluyla elde edilen sınıflara açık.
```cpp
class Myclass {
public:
    int a;
    int b;
    int c;

    int foo(int);
    //buraya kadar public
private:
    int d;
    typedef int Word;
    //buraya kadar private
protected:
    void f();
    //buraya kadar protected.
};
```
Class için varsayılan erişim kontrolü private iken struct için publictir. Ayrıca public private protected sıralaması önemli değil. İstenilen sırada yazılır. Tercih edilen public yukarıda private aşağıda 
Sınıfın public private veya protected bölümleri ayrı scopelar oluşturmaz. sadece erişim kontolü olarak kullanılır.
``cpp
class Myclass {
public:
    int x;
private:
    int x;  // sentaks hatası aynı scope aynı isimli değişken tanımlanamaz
};
``
``cpp
class Myclass {
    void func(int x); //1
};

void func(int x); //2
``
func fonksiyonlarının farkları nedir?
  1- Scope farklı 1 numaralı fonksiyon Myclass scope içerisinde (class scope) 2 numaralı fonksiyon namespace scope (global) Fonksiyon yüklenmesi var mıdır?  
  2- Parametre sayısı. 2 numaralı fonksiyonun sadece 1 adet int parametresi varken sınıfın nonstatic üye fonksiyonlarının sınıf türünden pointer olan (Myclas*) 
  gizli bir parametre değişkeni vardır. Aslında void func(Myclass * p, int x); yani bu fonksiyonu sınıf nesnesi olmadan kullanamayız. 
  Sınıf nesnesinin adresi ile arka planda bu fonksiyona erişeceğiz.
``cpp
class Fighter {
public:
    void func();
    void kill(Fighter&);
};
int main()
{
    Fighter myfighter;
    Fighter enemy_fighter; 
    myfighter.func(); // burada Fighter* türden bir nesne argüman olarak gönderiliyor.
    myfighter.kill(enemy_fighter);
    /* artık kimin kimi öldürdüğü belli :D
    C de iki tane adres döndermek gerekiyordu. C++ bu adres gönderme işini
    gizli bir şekilde yapıyor zaten.*/
}
``
Name lookup 	    1. adım
Context control		2. adım
Access control  	3. adım
C++'da isimler **nitelenmiş(qualified)** ve **nitelenmemiş(unqualified) name** bu ikisinin arama kuralları farklı  
Nitelenmiş isimler çözünürlük operatörün (::) sağ tarafında görülen isimlerdir. Çözünürlük operatörü unary ya da binary olarak kullanılabilir.
Çözünürlük operatörü binary olduğunda nün sol operandi bir değişken ismi olamaz!! Sadece namespace, class ya da enum ismi olur.
``cpp
::x;  //bu direk Namespace scopeta aranır.
Nec::x; // Nec ya namespace ya class ya da enum.
``
Arama işlemi de öncelikle varsa sol operand (Nec) bulunacak sonra onun scopunda sağ operand(x) aranacak.
Normalde isim nasıl aranırdı blok onu kapsayan blok ... namespace'e bakılırdı
```cpp
class Data {
public:
    int mx;
    void func();
};

int main()
{
    mx = 5; // burada sentaks hatası var.
    Data mydata;
		mydata.mx;  // Data class scopeta arandı. Hata yok
    Data* ptr = &mydata;
    ptr->mx;  // Data class scopeta arandı. Hata yok
}
```
