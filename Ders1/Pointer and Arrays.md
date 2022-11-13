# GÖSTERİCİLER
Her nesne bellekte yer kapladığına göre belirli bir adrese sahiptir. Nesnelerin adresleri,
sistemlerin çoğunda, derleyici ve programı yükleyen işletim sistemi tarafından ortaklaşa
belirlenir. Nesnelerin adresleri program yüklenmeden önce kesin olarak bilinemez ve
programcı tarafından da önceden saptanamaz. Programcı nesnelerin adreslerini ancak
programın çalışması sırasında (run time) öğrenebilir.

Adres bilgilerinin saklanması için kullanılan nesnelere gösterici (pointer) denir. Bir adres bilgisi C'de int, long
türlerde tutulamaz. Ancak gösterici denilen türlerde tutulabilir. Benzer biçimde göstericiler de adi birer int, long
türleri tutamazlar. Ancak adres tıtarlar. Gösterici bildiriminin genel biçimi şöyledir:

<tür> *<gösterici ismi>;
```cpp
int *p;
long *t;
double *d;
```
Bir gösterici her türden adres bilgisini tutamaz. Yalnızca tür bileşeni belirli olan olan adres bilgilerini tutar. Genel
olarak: T *p; gibi bir bildirimde p göstericisi tür bileşeni T olan adresleri tutabilir.
```cpp
char s;   //s, char türden bir değişken
char *ps; //ps, char türden bir göstericidir, yani türü char * olan bir nesnedir yani bellekte bir yer kaplar.
```
Bir gösterici nesnesinin tanımı ile karşılaşan derleyici –diğer tanımlamalarda yaptığı gibi-
bellekte o gösterici değişkeni için yer ayırır. Derleyicilerin göstericiler için ayırdıkları
yerlerin uzunluğu donanıma bağlı olup sistemden sisteme değişebilir. Göstericilerin uzunlukları türlerinden bağımsızdır.
UNIX işletim sisteminde 4 byte değerindedir.

## & (Address Of) Operatörü

& operatörü operand olarak bir nesne alır. Operatör bize nesnenin bellekteki yerleşim adresini verir. T x; olmak üzere &x ifadesinin türü T* türüdür.
Bir gösterici değişkeni, içinde bir adres bilgisi tutan bir nesne olduğuna göre, bir gösterici
değişkene adres işlecinin ürettiği bir adres bilgisi atanabilir.
```cpp
int x = 20;
int *ptr = &x;
```
Adres işleci ile elde edilen adres, aynı türden bir gösterici değişkene atanmalıdır.

## * İçerik (Indirection) Operatörü
İçerik işlecinin terimi bir adres bilgisi olmalıdır. Bir adres ifadesi, * işlecinin terimi olduğunda, elde edilen ifade bellekte o adreste bulunan,
nesneyi temsil eder. T* ptr; olmak üzere *ptr ifadesinin türü T türüdür.
```cpp
int x = 20;
int *ptr = &x;
*ptr = 100;   //x değişkenine 100 değeri atanmıştır.
```
C ve C++ dilinde bir adres bilgisi bir tamsayı ile toplanabilir, bir adres bilgisinden bir tamsayı
çıkartılabilir. Böyle bir ifade toplanan ya da çıkartılan adres türündendir. Örneğin int
türden bir nesnenin adresi(int*) ile 1 tamsayısı toplanırsa yine int türden bir nesnenin adresi bilgisi(int*) elde edilir.

## [] Köşeli Ayraç Operatörü
Bir adres bilgisine 1 toplandığında, adresin sayısal bileşeni adrese sahip nesnenin türünün uzunluğu kadar artar.Bu durumda örneğin DOS işletim sisteminde char türden
bir göstericinin değeri, 1 artırıldığında adresin sayısal bileşeni 1, int türden bir gösterici 1 artırıldığında ise adresin sayısal bileşeni 2 artar, 
double türden bir gösterici 1 artırıldığında ise adresin sayısal bileşeni 8 artar. Bir gösterici değişkenin bellekte bir nesneyi gösterdiğini düşünelim. Bu gösterici
değişkenin değeri 1 artırılırsa bu kez gösterici değişkeni, gösterdiği nesneden bir sonraki nesneyi gösterir duruma gelir.

İşlecin birinci terimi köşeli ayraçtan önce yer alır. Bu terim bir adres bilgisi olur. İkinci terim ise köşeli ayraç içine yazılacak tam sayı türünden bir ifade olur.
p[n] ifadesi ile *(p + n) tamamen eşdeğer ifadelerdir. Yani köşeli ayraç işleci, bir adresten n ilerideki nesneye erişmek için kullanılır.

Dizi isimleri dizilerin başlangıç adresini belirttiği için dizi elemanlarına köşeli parantez operatörü ile erişilebilmektedir.
```cpp
int a[3] = {10, 20, 30};
// a[2] ifadesi a adresinden 2 ilerinin (yani 2 * sizeof(*a) kadar byte ilerinin) içeriği anlamına gelir. Yani a[2] ile *(a + 2) aynı anlamdadır 30.
```
```cpp
#include <stdio.h>
int main()
{
int a[5] = {1, 2, 3, 4, 5};
int *ptr = a + 2;
printf("%d\n", ptr[-1]);
printf("%d\n", ptr[0]);
printf("%d\n", ptr[1]);
}
```

# DİZİLER


