# REFERANSLAR
C++ dilinde pointer kullanımı C ye göre çok çok daha az. Pointerlar C++ ta maalesef generic programlama tarafındaki araçlarla çok uyum sağlamıyor. Bunun yerine  Referans Semantiği ve Smart Pointer kullanılıyor. 
Referans Modern C++ tan önce 1 taneydi. Şimdi 2 ayrı referans kategorisi oldu. 
* R Value reference (Taşıma/Move Semantics ve Mükemmel gönderim / Perfect forwarding)
* L Value reference (Nesnenin yerine geçen bir isim)

## L Value Referans
L value referanslar için [inceleyiniz](https://necatiergin2019.medium.com/referanslar-references-1-8770705b8673).  
Referans bir nesnenin yerine geçen bir isim olarak düşünülebilir. Öyle ki biz referans olan ismi kullandığımızda aslında o ismin bağlandığı (yerine geçtiği) nesneyi kullanmış oluyoruz.
Referanslar & atomu (declarator) ile tanımlanır. T bir tür olmak üzere 
```cpp
T x{};  //x T türünden bir nesne
T &r = x;  //r, x'e bağlanmış bir referans
```
r isminin ne olduğunu şu biçimlerde ifade edebiliriz: 
r, x”in yerine geçen bir referanstır. 
r, x’e bağlanmış bir referanstır. 

1- referanslara ilk değer vermek (initialize) zorunludur.
```cpp
int& r; //SENTAKS HATASI
int x = 10;
int&r = x;  //veya int&r(x); veya int& r{x}; hepsi aynı.
```
2- Bir referansın aynı türden bir nesneye bağlanması zorunludur. 
```cpp
int x = 10;
double& r = x;  //SENTAKS HATASI
double y = 2.0;
double &r = y; //burası legal
```
3- LVALUE REFERANS BİR LVALUE EXPRESSİONA BAĞLANMAK ZORUNDADIR.
```cpp
int& r1 = 10; //sentaks hatası.
int x{};
int& r2 = x++; //sentaks hatası
int& r3 = ++x; 
```
4- Bir referans const anahtar sözcüğü ile tanımlanabilir. const anahtar sözcüğü „&‟ atomundan önce yazılır. Bu
şekilde tanımlanmış bir referans değişkeninin yerine geçtiği nesne, referans yoluyla değiştirilemez. 

!!!!OKUMA AMAÇLI ERİŞİM!!!!
```cpp
int x = 10;
const int& r = x; // const reference
int const & r = x; // const reference. aynısı.
r = 20; ////sentaks hatası r yoluyla x değiştirilemez sadece x'i ben okumak için bağlandım.
```

5- Const L Value referans her şeye bağlanabilir. (Sağ taraf değerine ve farklı türe) 
```cpp
double dval = 1.2;
const int &r = dval;
/*
int temp_val = dval;
const int &r = temp_val;
referans derleyicinin oluşturduğu temp değişkenin refere etti.Onun yerine geçti */
  
const int& r2 = 10;
/*
int temp_val{10};
cosnt int &r = temp_val; */

```
const olmayan bir sol taraf referansı const bir nesneye bağlanamaz. const nesne ancak const referansa bağlanabilir. 
```cpp
const int x = 10;
int &r1 = x; //geçersiz!
const int &r2 = x; //geçerli
```
 6- **Referansların Parametre Değişkeni Olarak Kullanılması**  
 Parametre değişkeni referans olan işlevler, aynı türden bir nesne ile çağrılmalıdır. Böyle bir çağrı sonucunda parametre değişkeni olan referans argüman olan nesnenin yerine
geçer:

 Fonksiyon çağrılarında öncelikle
 * **void foo(T& arg);** const olmayan L value ile çağrılır.
 * **void func(const T& arg);** bu fonksiyon Lvalue hem de PRvalue expr ile yani her şeyle çağrılır.
 ```cpp
 int x{};
 foo(x); // x L value olabilir
 foo(10); //10 PR value geçersiz
 foo(x*x); //x*x PR value geçersiz
 const int y = 10;
 foo(y); //y const oldugu icin gecersiz. int& arg = y; sentaks hatasi
 ```
 **void access(const T &r);**  
access isimli işlev, T türünden bir nesne üzerinde işlem yapabilir, ama söz konusu nesneyi değiştiremez. access işlevi T türünden bir nesnenin 
yalnızca değerinden faydalanır. access isimli işlev T türünden bir nesneye salt okuma (read/get/access) amaçlı erişim talep etmektedir. 
Böyle fonksiyonlara İngilizcede getter/accessor/get function gibi terimler yakıştırıldığını hatırlayalım. 
const T& biçiminde tanımlanan parametrelere “input paramete” de denmektedir. 

 **void mutate(T &r);**  
Ancak mutate isimli işlev de T türünden bir nesne üzerinde işlem yapar ve büyük ihtimal söz konusu nesneyi değiştirecektir.
mutate isimli işlev T türünden bir nesneye değiştirme (write/set/mutate) amaçlı erişim talep etmektedir.
Yine böyle fonksiyonlara İngilizcede setter/mutator/set function gibi terimler yakıştırıldığını hatırlayalım. 
T& biçiminde tanımlanan parametrelere “output parameter” de denmektedir.
Sözdizim kuralları açısından bakıldığında şüphesiz mutate işlevinin kendisine gelen T türünden nesneyi
değiştirmesi konusunda bir zorunluluk yoktur. Ancak böyle bir işlevin kendisine gelen nesneyi değiştireceği
kabul edilmelidir. Eğer nesneyi değiştirmeseydi işlevin parametresi const olarak seçilirdi.
 
## Yapı Nesnelerinin Referans Yoluyla İşlevlere Geçirilmesi 
1. Yapı nesnesinin değerinin geçirilmesi durumu (call by value). Bu durumda işlevin parametre değişkeni
bir yapı değişkenidir. İşlev başka bir yapı değişkenin kendisi ile çağrılır. Aynı türden iki yapı değişkeni
birbirine atanabildiğine göre, bu çağrı biçimi de geçerlidir.
 ```cpp
 #include <iostream>

struct Person {
    char name[30];
    int no;
};

void display_person(Person y)
{
    std::cout << y.name << '\n' << y.no << std::endl;
}

int main()
{
    Person per = {"Yusuf Yılmaz", 123};
    display_person(per);
    return 0;
}
 ```
 Bu tür bir aktarımda, yapının karşılıklı elemanları birbirlerine blok olarak kopyalandığı için göreli bir zaman
kaybı söz konusudur. Bu nedenle bu tür aktarım biçimi C dilinde kötü bir teknik olarak kabul edilir ve pek
kullanılmaz. Tabii çok küçük yapı nesnelerinin bu biçimde aktarılması söz konusu olabilir. İşlev değerle çağrıldığı
için, yani işlev çağrı ifadesindeki argüman olan yapı nesnesi işlevin parametre değişkenine kopyalanarak
aktarıldığı için, bu yolla argüman olan yapı nesnesinin işlev tarafından değiştirilebilmesi olası değildir. 

2. Yapı nesnesinin adresinin işleve geçirilmesi durumu (call by reference). Bu durumda işlev yapı değişkenin
adresi ile çağrılır. İşlevin parametre değişkeni de aynı türden bir yapı göstericisi olur. Bu aktarım biçiminde yapı
nesnesi ne kadar büyük olursa olsun gerçekte aktarılan tek bir adres bilgisidir. İşlev tanımı içinde adresi alınan
yapı nesnesinin elemanlarına erişmek için parametre değişkeni olan gösterici -> işlecinin terimi olur. Yapı
değişkenleri çoğunlukla işlevlere bu biçimde geçirilir.
 ```cpp
#include <iostream>

struct Person {
    char name[30];
    int no;
};

void display_person(const Person *ptr)
{
    std::cout << ptr->name << '\n' << ptr->no << std::endl;
}

int main()
{
    Person per = {"Yusuf Yılmaz", 123};
    display_person(&per);
    return 0;
}
 ```
Madem C++ dilinde referanslar bir çeşit göstericidir, o halde yapıların da verimli bir biçimde referans
yöntemiyle aktarımları da söz konusu olabilir. Böyle bir aktarım biçiminde, işlev yapı nesnesinin kendisiyle
çağrılır. İşlevin parametre değişkeni aynı yapı türünden bir referans olur. Böyle bir çağrıda işlevin parametre
değişkeni olan referans, işleve argüman olarak gönderilen yapı nesnesinin yerine geçer. Peki işlev içinde yapı
nesnesinin elemanlarına nasıl erişilir? Nokta işleci ile mi, ok işleci ile mi? Evet nokta işleci ile. Çünkü artık yapı
referansı kullanıldığında, referans dışarıdan gönderilen nesnenin yerine geçeceğine göre parametre olan
referans dışarıdan gönderilen yapı nesnesinin yerine geçer. Yani referansın kullanımı bir adres belirtmez. O
nedenle yapı referansı ile yapı elemanlarına erişimde nokta işleci kullanılır.
```cpp
#include <iostream>

struct Person {
    char name[30];
    int no;
};

void display_person(const Person &r)
{
    std::cout << r.name << '\n' << r.no << std::endl;
}

int main()
{
    Person per = {"Yusuf Yılmaz", 123};
    display_person(per);
    return 0;
}
```
**İşlevin Parametre Değişkeni Gösterici mi Referans mı Olmalı** 

Nesne yönelimli programlama söz konusu olduğunda, gösterici kullanmak yerine mümkün olduğu kadar referans kullanmak
gerektiği söylenebilir. Bir çok programcı şu ilkeyi benimser:  
"Kullanabildiğin her yerde referans kullan, ancak zorunlu olduğun yerde gösterici kullan!" (use references
wherever you can, use pointers when you have to!).  
C++‟da, a bir nesne olmak üzere aşağıdaki gibi bir işlev çağrısının yapıldığını düşünelim:  
func(a);  
Argüman olan ifadede a nesnesinin ismi yazılmıştır. Bu durumda iki olasılık söz konusudur:   
* İşlevin parametre değişkeni aynı türden bir nesnedir. (call by value) Bu durumda derleyici argüman olan nesnenin değerini parametre değişkenine kopyalayacak bir kod üretir.  
* İşlevin parametre değişkeni aynı türden bir referanstır. (call by value) Bu durumda gizli bir adres aktarımı söz
konusudur. Yani derleyici, çağrı ifadesinde argüman olarak kullanılan nesnenin adresini çağrılan işlevin
referans parametresine kopyalayacak bir kod üretir. 
Hangisi olduğunu bilmemiz için bildirimi görmemiz gerekmektedir.  

**Referansa Geri Dönen İşlevler**

İşlevlerin geri dönüş değerlerinin derleyici tarafından önce geçici bir bölgeye alındığını, buradan çekilerek kullanıldığını anımsayın.   
x = func();  
temp = return ifadesi;  
x = temp;  

İşlevin geri dönüş değerinin referans olması geçici bölgenin referans olması anlamına gelir. Bu durumda
return ifadesi bir referansa ilk değerini verir, değil mi?
```cpp
#include <iostream>

int x = 10;

int& func()
{
    return x;
}

int main()
{
    func() = 20;
    std::cout << "x = " << x << std::endl;
    ++func();
    std::cout << "x = " << x << std::endl;
    return 0;
}
```
Geri dönüş değeri bir referans olan işlevlerin, kendilerini çağıran kod parçasına, doğrudan bir nesnenin
kendisini ilettiğini düşünebilirsiniz.  
Bir fonksiyonun referans yolu ile aldığı nesneyi yine referans yolu ile geri döndürmesi tipik bir durumdur:  
```cpp
int &func(int &r)
{
    //...
    r = 777;
    return r;
}
```
Referans döndüren işlevler  
. Statik ömürlü bir nesneyi (global bir değişkeni ya da statik bir yerel değişkeni)  
. Dinamik ömürlü bir nesneyi  
. Kendisini çağıran koddan yine referans yoluyla ile aldığı bir nesneyi döndürebilir.  

ASLA AMA ASLA otomatik ömürlü bir nesne adresi döndürmemelidir.
