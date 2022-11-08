# Temel Kavramlar ve Terimler
## Atomlar ve Türleri
Bir programlama dilinde yazılmış kaynak dosyanın (program) anlamlı en küçük parçalarına "atom" (token) denir. Bir programlama dilinde yazılmış bir metin, atomlardan oluşur.
Atomlar aşağıdaki gibi gruplara ayrılabilir:
### 1. Anahtar Sözcükler (Keyword)
Anahtar sözcükler (keywords - reserved words) programlama dili tarafından önceden belirlenmiş anlamlara sahip atomlardır. Bu atomlar kaynak dosya içinde başka bir anlama gelecek biçimde kullanılamazlar. Örneğin bu atomların değişken ismi olarak kullanılmaları geçerli değildir.
https://en.cppreference.com/w/cpp/keyword adresinden C++ dili anahtar sözcükleri incelenebilir.
### 2. İsimler (İdentifiers)
Değişkenler, işlevler, makrolar, değişmezler gibi yazılımsal varlıklara programlama dili
tarafından belirlenmiş kurallara uyulmak koşuluyla isimler verilebilir. Yazılımsal bir varlığa
verilen isme ilişkin atomlar isimlerdir (identifier).
### 3. İşleçler (Operators)
İşleçler (operators) önceden tanımlanmış bir takım işlemleri yapan atomlardır.
https://en.cppreference.com/w/cpp/language/operator_precedence adresinden operatörler ve öncelik ilişkileri incelenebilir.
### 4. Değişmezler (Constants)
Değişmezler (constants) doğrudan işleme sokulan, değişken bilgi içermeyen atomlardır. sayac = son + 10 gibi bir ifadede 10 değişmezi doğrudan son isimli değişken ile işleme sokulur.
### 5. Dizgeler (String)
İki tırnak içindeki ifadelere "Dizge" (string / string litaerals) denir. Dizgeler programlama dillerinin çoğunda tek bir atom olarak alınır, daha fazla parçaya bölünemezler. "STRİNGLER DE BİRER ATOMDUR" ifadesi bir dizgedir.
### 6. 6. Ayraçlar, Noktalama İşaretleri
Yukarıda sayılan atom sınıflarının dışında kalan tüm atomlar bu gruba sokulabilir. Genellikle diğer atomları birbirinden ayırma amacıyla kullanıldıkları için ayraç (separators, punctuators, delimiters) olarak isimlendirilirler.
```cpp
# include <stdio.h>
int main()
{
  int number, k;
  int total = 0;
  printf("lütfen bir sayı girin\n");
  scanf("%d", &number);
  for(k = 1; k<= number; ++k)
    total += k;
  printf("toplam = %d\n", total);
  return 0;
}
```
Bu kaynak kod aşağıdaki gibi atomlarına ayrılabilir:

include         <     stdio.h     >   int    main    (     )      {     

int   number     ,     k     ;    int     total     =     0    ;

printf   (     "lütfen bir sayı girin\n"     )    ;    

scanf    (     "%d"     ,      &    number      )     ;

for     (    k    =    1    ;    k    <=    ;    ++    k   )

total     +=     k   ;

printf    (     "toplam = %d\n"     ,     toplam    )    ;   

return      0     ;    }

Keywords: include int for return

Identities: main k toplam printf scanf

Operators: = <= ++ +=

Constants: 0 1 0

String: "lütfen bir sayı girin\n" "%d" "toplam = %d\n"

Ayraçlar, noktalama işaretleri: < > ( ) , ; { }
