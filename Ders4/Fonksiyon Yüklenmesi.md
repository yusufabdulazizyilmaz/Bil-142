# Fonksiyon Yüklenmesi (function Overloading)
C++ in en önemli özelli̇klerinden biri. kodları birbirinden farkli birden fazla fonksi̇yon isimlerinin aynı seçilmesine deniyor. 
Amaç aynı işi yapan fonksi̇yonların ayni ismi alarak programcıya rahat kod yazma imkani vermek. aynı bilinirlik alanı içinde aynı isimli fakat farklı imzaya sahip işlevlerin
bir arada bulunması durumu. Dikkat edelim fonksiyon yüklenmesi olması için 2 koşul vardır. 1- aynı scope 2- farklı fonksiyon imzaları 
bir fonksi̇yonun geri dönüş değeri türü dışındaki parametrik yapısına o fonksiyonun imzasi denir.
```cpp
// imzaları aynı sentaks hatası
int func(long);
double func(long);

// fonksiyon yüklenmesi değil redecleration
int foo(int);
int foo(int);

// fonksiyon yüklenmesi değil scope farklı
int func();
int main()
{
    int func(double);
}

// fonksiyon yüklenmesi değil redecleration burada constluk ihmal ediliyor
int func(int);
int func(const int);

// fonksiyon yüklenmesi const yüklemesi diyeceğiz en sık kullanılan fonksiyon yüklenmesi
int func(int&);
int func(const int&);

// fonksiyon yüklenmesi
void func(int&);
void func(const int&);
void func(int&&);
```
Önemli mesele fonksiyon yüklenmesi olduğu zaman fonksiyon çağrısında hangi fonksiyonun çağrılacağıdır. Buna FUNCTION OVERLOAD RESOLUTION
yüklenmiş işlevin çözümlenmesi denmektedir.  
Bu süreç 2 farklı şekilde sonuçlanır.  
geçerli kod oluşur ve hangi fonksi̇yonun çağrıldığını anlar ve programı o koda bağlar  
sentaks hatası olur. ya NO MATCH: uygun fonksiyon olmaması durumu sentaks hatasıdır. ya da AMBIGUITY(çift anlamlılık):öncelik verilemiyor.
function overload resolution süreci̇ 3 aşamada ele alınıyor.  
1 - Candidate functions: function çağrı aşamasinda görülebilir olan ayni isimdeki tüm functionlari bir listeye koyuyor.   
2 - Viable functions: bu fonksiyon tek başina olsaydi bu çağri legal olur muydu ? evet i̇se bu viable function nasil olacak bu  
	a - function çağrısında kullanılan argüman sayısı ile
	function parametre sayisi uyumlu olacak. default argument dahil.
	veri̇kaybi da olabilir sorun deği̇l.  
	b - her argümandan her parametreye geçerli bi̇r tür dönüşümü olacak.  
  SORU : HANGİSİ VIABLE ?
```cpp
void func(long double); //1
void func(char); //2
void func(int, int); //3
void func(int*); //4
int main()
{
    func(21);
}
```
3- Best Match function: viableların içerisinden en uygun olanın seçilmesi 1 den fazla best match varsa arasında seçme yapamazsa Ambigiuty hatası olacak.
argümandan parametreye yapilan dönüşüm beli̇rli̇ kategori̇lere ayriliyor. bunlar daha i̇yi̇ veya daha kötü  
3.1- STANDART CONVERSION  
3.1.1 EXACT MATCH - TAM UYUM   
Argüman türü ile parametre türünün tamamen ayni olması durumu, const dönüşümü, array to pointer conversion, function to pointer conversion ve Referans semantiği
```cpp
void func(long double); //1
void func(char);  //2
int main()
{
    func(2.4L); // 2.4L long double türüdür. 1. fonksiyon ile EXACT MATCH VAR.
    func('A'); // 'A' char türündendir. 2. fonksiyon ile EXACT MATCH
}

void func(int (*)(int));
int foo(int);
func(foo); 
```
3.1.2 PROMOTION (YÜKSELME)  
Integral Promotion (Tam sayıya yükseltme) char, signed char, unsigned char, bool, short, unsigned short türlerinden int türüne yapılacak dönüşüm.  
Floating Point Promotion float türünün double türüne dönüştürülmesi
Bir numaralandırma (enum) türünden o numaralandırma türüne baz olan (underlying type) türe yapılan dönüşüm de yükseltme olarak değerlendirilir.  
```cpp
void func(int);
void foo(double);

enum Color
{
    Blue, Red, Green, Yellow
};
void f(int);

int main()
{
    func('A');    // yükseltme (integral promotion)
    func(true);    // yükseltme (integral promotion)
    foo(2.3f);    // yükseltme (float to double promotion)
    f(Blue);     // yükseltme  (enum to underlying type)
}
```
3.1.3 Diğer Standart Dönüşümler   
Dilin kurallarınca geçerli olan ve örtülü (implicit) olarak yapılabilen diğer dönüşümlerdir. 
Tam sayı türlerine ilişkin dönüşümler Bir tam sayı türünden ya da bir numaralandırma (enum) türünden başka bir tam sayı türüne yapılan dönüşümler.    
Gerçek sayı dönüşümleri Bir gerçek sayı türünden başka bir gerçek sayı türüne yapılan dönüşümler.  
Gerçek sayı türleri ile tam sayı türleri arasında yapılan dönüşümler.  
Adres türlerine ilişkin dönüşümler void türden olmayan herhangi bir adresin void türden bir adrese dönüştürülmesi. (T * ---> void *)
ve 0 tam sayı sabitinin herhangi türden bir adres türüne kopyalanması için nullptr sabitine dönüştürülmesi.  
bool türüne yapılan dönüşümler Herhangi bir tam sayı, gerçek sayı, numaralandırma ya da adres türünden bool türüne yapılan dönüşümler.
```cpp
void func(int);
void foo(long);
void f(float);
void pf(int *);
void vfunc(void *);
int main()
{
    int x = 10;
    foo(x);	//standart dönüşüm (int türden long türüne)
    foo('A');	//standart dönüşüm (char türden long türüne)
    func(20U);	//standart dönüşüm (unsigned int türünden int türüne)
    f(7.5);	//standart dönüşüm (double türden float türüne)
    pf(0);	//standart dönüşüm (0 tamsayı sabitinin bir göstericiye kopyalanması
    vfunc(&x)	//standart dönüşüm (int * türden void * türüne)
}
```
3.2- User-defined conversions 
Derleyici bildirilen bir fonksiyona çağrı yaparak bir dönüşümü gerçekleştirir. 
Yani dönüşümü gerçekleştiren aslında derleyicinin çağıracağı bir fonksiyondur. 
Böyle fonksiyonlara çağrı yapılması ile, sınıf türleri ile temel türler arasında ya da farklı sınıf türleri arasında tür dönüşümleri yapılabilir. 
Böyle dönüşümlerin yapılmasını sağlayan fonksiyonlar şunlardır:

Dönüştüren kurucu fonksiyon “(conversion constructor)  
Tür dönüştürme operatör fonksiyonları (type-cast operator functions)  
```cpp
struct Data {
    int x;

    Data(int);  //(conversion constructor) int'ten Data'ya conversion
    // operator int(); //(type-cast operator functions) Data'dan int'e conversion
};

int main()
{
    Data mydata;
    mydata = 10; // int'ten Data'ya conversion
    10+mydata; // Data'dan int'e conversion
}
```
```cpp
int foo(int);        //1
int foo(double);    //2
void foo(char);        //3
long foo(long);        //4
void foo(int, int);    //5
void foo(char*);    //6
void foo(int*);    //7
void func()
{
    foo(10);
    foo(3.4F);
    foo((double*) 0x1FC0);
    foo(6U);
}
```
foo(10); için  
1, 2, 3, 4, 5, 6, 7 numaralı fonksiyonlar adaydır.  
1, 2, 3, 4 numaralı fonksiyonlar uygundur.  
Tam uyum sağladığı için, 1 numaralı fonksiyon en uygun olanıdır.  
foo(3.4F) için  
1, 2, 3, 4, 5, 6, 7 numaralı fonksiyonlar adaydır.  
1, 2, 3, 4 numaralı fonksiyonlar uygundur.  
Yükseltme durumu olarak değerlendirildiğinden 2 numaralı fonksiyon en uygun olanıdır.  
foo((double *) 0x1FC0) için  
1, 2, 3, 4, 5, 6, 7 numaralı fonksiyonlar adaydır.
Uygun fonksiyon yoktur (no match). Fonksiyon çağrısı geçersizdir.  
foo(6U) için  
1, 2, 3, 4, 5, 6, 7 numaralı fonksiyonlar adaydır.  
1, 2, 3, 4 numaralı fonksiyonlar uygundur.  
1, 2, 3 ve 4 numaralı fonksiyonlar için standart dönüşüm uygulanabilir. Çift anlamlılık hatası (ambiguity) söz oluşur. Fonksiyon çağrısı geçersizdir.  
Fonksiyon yüklemesi için [inceleyiniz](https://necatiergin2019.medium.com/fonksiyon-y%C3%BCklemesi-function-overloading-388ec04e5e72).
