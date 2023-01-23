# SINIFLAR (CLASSES)
Sınıf (class) nesne yönelimli programlama tekniğinin uygulanmasına olanak sağlayan, C dilinde olmayan yeni bir
yazılımsal birimdir. Sınıflar, C'deki yapılara benzetilebilir. Ancak C'deki yapılar yalnızca eleman (member)
içerirken, C++'da sınıflar yapılardan fazla olarak hem veri elemanı hem de üye işlevleri (member function) içerir.
Sınıflar, yapılara göre ek bir çok özelliğe sahiptir. Bu özelliklerin çoğu Nesne Yönelimli Programlama Tekniği'ni
destekleme amacıyla eklenmiştir.  
Nasıl bir yapı (struct) türü programcı tarafından tanımlanmış bir tür (user defined type) ise, sınıflar(classes) da programcının
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
1- **Data members(veri elemanları)**  static ya da nonstatic  
2- **Member function(üye fonksiyon)** static ya da nonstatic  
3- **Member Type - Type Member - Nested Type(Tür elemanları)**   
```cpp
class Nec {
public:
    int m_x; // nonstatic data member
    static int m_y; // static data member.
    void func123(int, int);  // nonstatic member function
    // static member function sınıfın içinde inline olarak tanımlanmış
    static void foo(int)
    {
    
    }
    using value_type = int; //type member 
    value_type m_Int = 5; // nonstatic data member
    class Iterator {  // Nested type
    };
};

//sınıfın member fonksiyonu tanımlanırken fonksiyon isminin önüne <sınıf_ismi> :: konulmalı
// Çözünürlük operatörü (::) bir ismin nerede aranacağını belirtmek için kullanılır.

void Nec::func123(int x, int y) 
{

}

int main()
{
    Nec n1;   // instantiate nesne oluşturmaya karşılık gelen terim
    n1.m_x;
    n1.func123(1,2);
    Nec::m_y;
    Nec::foo(3);
    Nec::Iterator myNecIter;
    std::cout << sizeof (Nec);    // m_Int ve m_x değişkenleri toplam 8 byte
    std::cout << sizeof (Nec::Iterator);  // empty class 1 byte
}
```
Nonstatic data memberlar sınıf boyutunu (sizeof) artırıyor. fiziksel olarak class içinde yer alıyorlar. Fakat static data memberlar sınıf sizeofuna girmiyor. Member functionlar sınıfın içinde bildiriliyor ama içinde yer kaplamıyor.  

```cpp
// Geçici Nesneler(Temporary Objects)
/*
Öyle bir nesne ki kaynak kodda bir isme sahip değil ama yine de o bir nesne.
Geçici nesneler bilerek isteyerek özel bir sentaks ile oluşturulabiliyorlar.
Sentaks:
SınıfTürü( Ctora gönderilecek argüman veya argümanlar ) 
SınıfTürü{ Ctora gönderilecek argüman veya argümanlar }
Nec ();
Nec {};*/

//GEÇICI NESNELER PR VALUE EXPRESSIONDUR
void f1(Myclass);
void f2(const Myclass&);
void f3(Myclass&&);
void f4(Myclass&);
int main()
{
	f1(Myclass{});   //geçerli
	f2(Myclass{});   //geçerli
	f3(Myclass{});	 //geçerli
	f4(Myclass{});   //BURASI SENTAKS HATASI. sol taraf referansına sağ taraf değeri bağlanamaz.
}

// Daha etkin kod ve scope leakage engellemek için kullanılırlar
void f1(Myclass);
int main()
{
	Myclass m{12};
	f1(m);
    //Yukarıda m main bitene kadar yaşıyor. Scope leakage var. Doğrusu
    f1(Myclass{12});
}

```
## ACCESS CONTROL - ERİŞİM KONTROLÜ
Sınıfın herhangi bir üyesi erişim kontrolü açısından 3 kategoriden birine ait olmalıdır.  
a - Public members: Herkese açık kodlar  
b - Private members: Sadece sınıfın kendisinin kullanacağı kodlar.   
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
Class için varsayılan erişim kontrolü private iken struct için publictir. Ayrıca public private protected sıralaması önemli değil. İstenilen sırada yazılır. Tercih edilen ise public yukarıda private aşağıda. 
Sınıfın public private veya protected bölümleri ayrı scopelar oluşturmaz. sadece erişim kontolü olarak kullanılır.
```cpp
class Myclass {
public:
    int x;
private:
    int x;  // sentaks hatası aynı scope aynı isimli değişken tanımlanamaz
};
```
```cpp
class Myclass {
    void func(int x); //1
};

void func(int x); //2
```

func fonksiyonlarının farkları nedir?  

1- Scope farklı 1 numaralı fonksiyon Myclass scope içerisinde (class scope) 2 numaralı fonksiyon namespace scope (global) 
Fonksiyon yüklenmesi var mıdır? Kesinlikle HAYIR!!! (Scope farklı)    
2- Parametre sayısı. 2 numaralı fonksiyonun sadece 1 adet int parametresi varken sınıfın nonstatic üye fonksiyonlarının sınıf türünden pointer olan (Myclass*) gizli bir parametre değişkeni vardır. Aslında void func(Myclass * p, int x); yani bu fonksiyonu sınıf nesnesi olmadan kullanamayız. Sınıf nesnesinin adresi ile arka planda bu fonksiyona erişeceğiz.
```cpp
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
```
Name lookup 	    1. adım  
Context control		2. adım  
Access control  	3. adım  
C++'da isimler **nitelenmiş(qualified)** ve **nitelenmemiş(unqualified) name** bu ikisinin arama kuralları farklıdır.    
Nitelenmiş isimler çözünürlük operatörün (::) sağ tarafında görülen isimlerdir. Çözünürlük operatörü unary ya da binary olarak kullanılabilir.
Çözünürlük operatörü binary olduğunda sol operandi bir değişken ismi olamaz!! Sadece namespace, class ya da enum ismi olur. Arama işlemi de öncelikle varsa sol operand (Nec) bulunacak sonra **onun scopunda** sağ operand(x) aranacak.
```cpp
::x;  //bu direk global Namespace scopeta aranır.
Nec::x; // Nec ya namespace ya class ya da enum.
```
Nitelenmemiş isimler olduğunda normalde isim nasıl aranırdı blok onu kapsayan blok ... namespace'e bakılırdı. İşin içine sınıfla ilgili bir arama geldiğinde blok onu kapsayan blok ... **CLASS scope** ve Namespace'e bakılır.
```cpp
class Nec {
public:
    void foo();
    int x;
};

int x = 87;

void Nec::foo()
{
    int x{};    //ÖNEMLİ !!!
    x = 10;     //bu x local x, Eğer local scopeta Bulamazsa class scope a bakacak. Bulamazsa Namespace scope
    ::x;        //Bu ise Namespace yani global x
    Nec::x = x + ::x;  //Sınıfın veri elemanı x = local x + global x
}
```
```cpp
class Nec
{
public:
    void foo();
private:
    int x;
};
Nec gnec;
void Nec::foo()
{
    Nec a;

    gnec.x = 10; 	//Geçerli.Farklı obje bile olsa private bölümüne erişir.

    a.x = 20;	    //Geçerli.Farklı obje bile olsa private bölümüne erişir.
    x = 20;         //fonksiyonu hangi nesne çağırırsa onun x değişkeni.
}

int main()
{
    Nec mynec;
    mynec.foo();
}
```
