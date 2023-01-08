# Veri Türleri
Nesneler türü (type) derleyiciye o nesnenin nasıl yorumlanacağı hakkında bilgi verir. 
Bir nesnenin türü onun bellekteki uzunluğu hakkında da bilgi verir. Her türün bellekte 
ne kadar uzunlukta bir yer kapladığı programlama dillerinde önceden belirtilmiştir.  Bir
nesnenin türü, ayrıca o nesne üzerinde hangi işlemlerin yapılabileceği bilgisini de verir.  
Veri türleri için [inceleyiniz](https://en.cppreference.com/w/cpp/language/type)    
fundamental types: void; std::nullptr_t; arithmetic;  
compound types: function; array; pointer; pointer-to-member; reference; union; enumeration; class;  
arithmetic types: floating-point(float, double, long double); integral(bool, char, signed char, unsigned char, 
(unsigned) short int, (unsigned) int, (unsigned) long int, (unsigned) long long int);  
Hap bilgiler:  
1. en çok kullanılan veri türleri tamsayılar için int türüyken, gerçek sayılar için double veri türüdür.
2. char türü 1 byte uzunluğunda olmak zorundadır.
3. short <= int <= long (byte olarak)
4. float <= double <= long double
5. Gerçek sayılarla yapılan işlemler tam sayılarla yapılan işlemlere göre çok daha yavaştır.  
## Değişmezlerin Türleri
Değişmezler nesne olmayan, programcı tarafından doğrudan sayısal büyüklük olarak girilen verilerdir. Nesnelerin türleri olduğu gibi değişmezlerin de türleri vardır. Nesnelerin türleri bildirim yapılırken belirlenir. Değişmezlerin türlerini ise derleyici, belirli kurallara uyarak
değişmezlerin yazılış biçimlerinden saptar. Değişmezlerin türleri önemlidir, çünkü C++ dilinde değişmezler, değişkenler ve operatörler bir araya getirilerek ifadeler (expressions) oluşturulur. C++'da ifadelerin de türü vardır. İfadelerin türleri, içerdikleri değişmez ve değişkenlerin türlerinden elde edilir.  
**Tamsayı Değişmezleri** varsayılan yazım onluk sayı sistemidir. Onaltılık sayı sisteminde yazım: 0Xbbb.. ya da 0xbbb.. Sekizlik sayı sisteminde yazım: 0bbbb.. Bir tamsayı değişmezi, hangi sayı sisteminde yazılırsa yazılsın, u, U, l ya da L soneklerini alabilir. u ya da U sonekleri tamsayı değişmezinin işaretsiz tamsayı türünden olduğunu belirler. l ya da L sonekleri tamsayı değişmezinin long türden olduğunu belirler. Taşma olmaksızın ilgili değeri tutabilecek ilk tür, değişmezin türüdür. 
Sayı DOS  (int 2 byte) / Windows - Unix  (int 4 byte)  
456 signed int/signed int  
59654 signed long/signed int   
1245800U unsigned long/unsigned int   
0X130268U unsigned long/unsigned int  
**Karakter Değişmezleri** tipik olarak char türden nesnelere atanan değişmezlerdir. 'a' char türündendir.  
**Gerçek Sayı Değişmezleri** yalnızca onluk sayı sistemi kullanılarak yazılabilir. Sayı nokta içeriyorsa ve sayının sonunda hiçbir ek yoksa değişmez double türdendir (-24.5). Nokta içeriyorsa ve sayının sonunda küçük harf ya da büyük harf F varsa sabit float türdendir (1.31F). Sayı nokta içeriyorsa ve sonunda küçük harf ya da büyük harf L varsa sabit long double türdendir (10.2L).  
Özetle öncelikle ondalık sistemdeki sayıların nokta içerip içermediğine ve son eklerine bakacağız.
## Değişkenler
### Bildirim ve Tanımlama (Declaration & Definitions)
C, C++, C# ve Java gibi katı tür kontrolünün uygulandığı dillerde (strongly typed languages) bir değişken
kullanılmadan önce derleyiciye tanıtılmak zorundadır. Kullanılmadan önce değişkenlerin derleyiciye tanıtılması
işlemine bildirim (declaration) denilmektedir. Bir bildirim yapıldığında eğer derleyici bildirilen değişken için
bellekte bir yer ayırıyorsa o bildirim aynı zamanda bir tanımlama (definition) işlemidir. Yani tanımlama
derleyicinin yer ayırdığı bildirim işlemleridir. Bildirim daha geneldir. Her tanımlama bir bildirimdir fakat her
bildirim bir tanımlama değildir.  
**<tür> <değişken ismi> <;>** 
```cpp
int a; 
long b, c, d; 
double x, y;
```
Fonksiyon bildirimi, derleyiciye bir fonksiyon hakkında bilgi veren bir deyimdir. Derleyici, fonksiyon
çağrısına ilişkin kodu buradan aldığı bilgiye göre üretir. Ayrıca derleyici, aldığı bu bilgiyle,
bazı kontroller de yapabilir. Bir fonksiyon bildiriminin genel biçimi aşağıdaki gibidir:  
**<geri dönüş değeri türü> <fonksiyon ismi> <(> [ tür1, tür2..... ] <)> <;>**
```cpp
double get_val(double, double); //declaration
double get_val(double a, double b) //definition
{
    return a+b;
}
```
### ilk değer verme (Initialization)
Bir değişken tanımlandığında bu değişkene bir ilkdeğer verilebilir (initialize). int a = 20;  
**initialization is not an assigment.** 
```cpp
int x = 5; //(initialize) 
x = 10; //(assign)
```
C++ sentaksının en fazla zorluk içerdiği noktalardan biri ilk değer verme (initialization). Bu konuda dilin çok sayıda kuralı ve bu kurallara ilişkin kullanılan çok sayıda terim var. Bizim burada çok temel şeyleri açıklayacağız.  
**default initialization (varsayılan başlatım)**
```cpp 
int y; 
// statik ömürlü ise zero initialization boollar false ile, pointerlar nullptr ile değişkenler 0 ile başlatılıyor. 
// otomotik ömürlü ise garbage value kullanmak UB
```
**copy initializatin (kopyalamayla başlatım)** 
```cpp 
int x = 5;
```
**direct initialization (doğrudan başlatım)**  
```cpp 
int x(10);
```
**value initialization (değerle başlatım)**
```cpp 
int x{};
// otomotik veya static ömürlü olması farketmez
// zero initialization boollar false ile, pointerlar nullptr ile değişkenler 0 ile başlatılıyor.
```
**list (uniform - brace) initialization (listeyle başlatım)** 
```cpp
int x{10};
double dval = 3.987; // türe dikkat
int ival {dval}; //sentaks hatası
//narrowing conversion / daraltıcı dönüşüm izin verilmiyor
```
