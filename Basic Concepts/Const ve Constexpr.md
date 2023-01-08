# Constexpr
constexpr kabuk değiştirmiş C++’ın en önemli anahtar sözcüklerinden birisidir ve her standartta önemi daha da artmaktadır. 
constexpr anahtar sözcüğü “constant expression” (sabit ifadesi) sözcüklerinden uydurulmuş. 
constexpr anahtar sözcüğüyle tanıtılan bir varlık kod içinde sabit ifadesi olarak kullanılabiliyor. 
Derleyicinin derleme zamanında değerlerini bilme ya da hesaplama garantisi olan ifadelere sabit ifadesi dendiğini hatırlayın.
constexpr anahtar sözcüğü hem bir değişkenin hem de bir işlevin tanımında  kullanılabiliyor. Bu değişkenlere sabit ifadesi ile ilk değer verilmelidir.
```cpp
constexpr int x = 10;
int foo();
constexpr int x = foo();  //sentaks hatası
constexpr int y = x * 5;  //OK.Çünkü x te sabit
x = 100; // burada sentaks hatası var çünkü CONSTEXPR ILE VERILMIŞ DEĞERLER DEĞIŞTIRILEMEZ.
```
x değişkeni sabit ifadesi (constant expression) gereken her yerde kullanılabilir.  
x, değeri hiç değişmeyecek bir değişken. Yani hayatta olduğu sürece hep aynı değerde kalacak. 
Bu açıdan bakıldığında constexpr anahtar sözcüğü const anahtar sözcüğünün anlamını da içeriyor.  
Peki bu durumda const anahtar sözcüğü ile constexpr anahtar sözcüğü aynı anlama mı geliyor? Kesinlikle hayır. 
const anahtar sözcüğü ile tanımlanan bir değişkene bir sabit ifadesi ile ilk değer vermek zorunlu değil. 
Bir const değişken ancak bir sabit ifadesi ile ilk değerini aldığında sabit ifadesi olarak kullanılabiliyor. 
Ancak constexpr değişkenlere sabit ifadesi olmayan ifadeler ile ilk değer verilemiyor ve constexpr değişkenler her zaman sabit ifadesi olarak 
kullanılabiliyor.
```cpp
int func();

int main()
{
    const int x1 = func(); //geçerli
    const int x2 = 10; //geçerli
    constexpr int cx1 = x1; //geçersiz. x1 sabit ifadesi değil
    constexpr int cx2 = x2; //geçerli, x2 sabit ifadesi
    constexpr int cx3 = func(); //geçersiz, func() sabit ifadesi değil

    int a[x1]; //geçersiz, dizi boyutu sabit ifadesi değil
    int b[x2]; //geçerli, dizi boyutu sabit ifadesi.
    int c[cx3]; //geçerli, dizi boyutu sabit ifadesi.

    return 0;
}
```
Sonuç olarak const sentaks bileşeni. ifadenin değişmeyeceğini söylüyor. eğer biz insanların masum bakışları ile değeri biliniyorsa da const değişkenler
sabit ifadesi olarak kullanılabilir. constexpr ise ifadenin bir sabit ifadesine eşitleneceğini söylüyor. Bir ifadenin sabit ifadesi olup olmadığını anlamanın en kolay yolu onu constexpr bir değişkene ilk değer vermede kullanmaktır.

Costexpr değişkenler için [inceleyiniz](http://plepa.com/2016/08/23/constexpr_1/)  

**CONSTEXPR Fonksiyonlar**  

```cpp
constexpr int square(int x)
{
	return x * x;
}
```
Eğer bir constexpr fonksiyona gönderilen tüm argümanlar constant expr ise bu durumda fonksiyonun geri dönüş değeri COMPILE TIME DA ELDE EDILIYOR. 
Bu da şu demek fonksiyona yapilan çağrı ifadesi bir constant expr oluşturuyor. Ayrıca constexpr fonksiyonu sabit ifadesi ile çağırmak zorunlu değil.  
**square(5);** burası bir sabit ifadesi oldu. Return değeri compile time da hesaplanacak
Square(x + 5) burası sabit ifadesi değil. Return degeri runtime da hesaplanacak.

```cpp
constexpr int sum_square(int x, int y)
{
	return x * x + y * y;
}
constexpr int a = 54;
constexpr int b = 66;
sum_square(a, b);
int c = 54;
int d = 66;
sum_square(c, d); // sentaks hatası yok sabit ifadesi değil 
```
```cpp
constexpr bool isprime(int val)
{
	if (val == 1 || val == 0)
		return false;
	if (val % 2 == 0)
		return val % 2 == 0;
	if (val % 3 == 0)
		return val % 3 == 0;
	if (val % 5 == 0)
		return val % 5 == 0;
	for (size_t i = 7; i * i < val; i+=2) // buradaki koşul matematiksel olarak biliyor yoksa hepsine bakılırdı.
	{
		if (val % i == 0)
			return false;
	}
	return true;
}
constexpr bool b = isprime(43);
```
C++'TA ASIL OLAN VERİM  
Bu durumda derleme zamanında hesaplanacak değerler için gereksiz yere runtimeda kaynak harcanmıyor. Ne kadar mükemmel. Bu dilin kuralı. Eksileri neler peki
C++ ta bazı kodların başlık dosyasında bulunması gerekiyor. Mesela constexpr bir fonksiyon var diyelim. compilerin bunu görmesi lazım. Buna göre compile time da hesaplama yapacak.
Yani function definition header fileda olmalı. Kodu göstermek istemiyorsak bu bir dezavantaj olabilir.

