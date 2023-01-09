# TÜR DÖNÜŞÜMLERİ
Programcının bir kod yazmasına gerek duyulmaksızın otomatik olarak gerçekleşen dönüşümlere, otomatik tür dönüşümleri (implicit type conversions)
denilmektedir. Diğer taraftan C++ dili, programcıya herhangi bir ifadeyi, operatörler kullanarak başka bir türden ele alma olanağı da verir. Programcı tarafından yapılan böyle tür
dönüşümlerine bilinçli tür dönüşümleri (explicit type conversions/type casts) denilmektedir. 

Aşağıda belirtilen dört durumda mutlaka otomatik bir tür dönüşümü yapılır:

1. Aritmetik ya da mantıksal bir ifadenin terimleri aynı türden değilse: (işlem öncesi tür dönüşümleri)
2. Atama işleci kullanıldığında atama işlecinin sağ tarafındaki ifadenin türü ile sol tarafındaki ifadenin türü aynı değilse (atama tür dönüşümleri)
```cpp
double toplam;
long sayi1, sayi2;
toplam = sayi1 + sayi2;
```
3. Bir fonksiyon çağrısında fonksiyona gönderilen bir argümanın türü ile fonksiyonun ilgili parametre değişkeninin türü aynı değilse
```cpp
double sqrt (double val);
void func()
{
  int number;
  double result = sqrt(number);
}
```
4. Bir return ifadesinin türü ile ilgili işlevin geri dönüş değerinin türü aynı değilse:
```cpp
double func(int val)
{
/****/
  return val;
}
```
3 ve 4. maddeler de bir atama işlemi olarak düşünülebilir.
## İşlem Öncesi Aritmetik Tür Dönüşümleri
Bilgi kaybını engellemek için genel olarak daha küçük türden olan terim, daha büyük türde olan terimin türünde ifade edilir.

* İşleme giren operandlardan bir tanesi gerçek sayı türünden (float, double, long double), diğeri tamsayı türünden ise tamsayı türünden operand o gerçek sayı türüne dönüştürülerek işlem yapılmaktadır.

* İşleme giren operandlar tam sayı türlerindense: unsigned signed versiyonlardan üstündür. Özellikle, aritmetik operatörler int'den daha küçük türleri argüman olarak kabul etmezler. **integral promotion:** short int, unsigned short int, char, signed char, unsigned char ve kapsamlandırılmamış numaralandırma sabitlerinden (unscoped enumeration)türlerinden int türüne dönüşüm. **Floating-point promotion:** float türünden double türüne yapılan dönüşüm.

## Atama Tür Dönüşümleri
Bu tür dönüşümlerin çok basit bir kuralı vardır: Atama öncesinde, atama işlecinin sağ tarafındaki ifade, atama işlecinin sol tarafındaki nesnenin türünde ifade edilir: 

* Küçük türlerin büyük türlere dönüştürülmesinde bilgi kaybı söz konusu değildir.
* Büyük türün küçük türe dönüştürülmesi durumunda bilgi kaybı söz konusu olabilir. Eğer atama işlecinin her iki tarafı da tam sayı türlerinden ise Bilgi kaybı, yüksek anlamlı byte'ların kaybolması şeklinde ortaya çıkar. 
```cpp
#include <stdio.h>
int main()
{
  char ch;
  ch = 135;     // 1000 0111
  if (ch == 135)
    printf("dogru!\n");
  else
    printf("yanlış!\n");
  return 0;
}
```
* Atama işlecinin sağ terimi, bir gerçek sayı türünden ise(float, double, long double) ve sol terimi tam sayı türünden ise önce gerçek sayı değerinin ondalık kısmı kaybedilir.

```cpp
#include <iostream>
int main()
{
  double y = 234.12;
  int x;
  x = y;
  std::cout << "x = " << x; /* x değişkenine 234 değeri atanır*/
  y = 7689523345.347;
  x = y; /* Yanlış */
  std::cout << "x = " << x;
  return 0;
}
```

## İşlev Çağrılarında Tür Dönüşümü
Bir işleve gönderilen argümanlarla, bu argümanları tutacak işlevin parametre değişkenleri arasında tür farkı varsa 
otomatik tür dönüşümü gerçekleşir ve argümanların türü, parametre değişkenlerinin türlerine dönüştürülür.
```cpp
double func(double x, double y); // x ve y parametre
int main()
{
  int a, b;
  func(a, b);    // a ve b argüman
  return 0;
}
```
## Tür Dönüştürme Operatörleri
C tarzı tür dönüştürme operatörü, bir ayraç ve ayraç içine yazılan bir tür bilgisinden oluşur: (T)
```cpp
int ival = 10; 
double dval = (double) ival;
```
C++'da dönüşüm yapacağımız zaman aşağıdaki tür dönüştürme operatörlerini kullanacağız. C tarzı tür dönüştürme yapmamalıyız.
```cpp
// static_cast < new-type > ( expression )		
int n = static_cast<int>(3.14);
// const_cast < new-type > ( expression )
int i = 3;                 // i is not declared const
const int& rci = i; 
const_cast<int&>(rci) = 4; // OK: modifies i
// reinterpret_cast < new-type > ( expression )   pointer to any type
// dynamic_cast < new-type > ( expression )		   about inheritance
 ```

