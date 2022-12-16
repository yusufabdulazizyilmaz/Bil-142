### Nesnelerin Ömürleri (storage duration / lifespan)
Ömür (storage duration / lifespan), nesnelerin, programın çalışma zamanı içinde bellekte yer kapladığı süreyi anlatmak için kullanılan bir terimdir. 
Bir kaynak kod içinde tanımlanmış değişkenlerin hepsi, program çalışmaya başladığında aynı zamanda yaratılmaz. C++'da 4 çeşit ömür kategorisi vardır:  
Otomatik  
Statik  
Dinamik  
Thread_local  

Aşağıdaki örnekleri anlayabilmemiz için nesnelerimizin kurallarını açıklayalım.  
S object_1("First Name", "Last Name");  
S : The object’s Type    
object_1 : The object’s ID  
"First Name" : The object’s first name  (Hayata gelince ekrana yazacak ifade)  
"Last Name" : The object’s last name (Hayatı sonlanınca ekrana yazacak ifade)  
Her zaman geçerli bir kuralı ifade edelim öncelikle:  
**İLK HAYATA GELEN EN SON VEDA EDER.** ya da **İŞE EN SON GİREN İLK ATILIR.**    

**Otomatik ömürlü nesneler** programın çalışmasının belli bir zamanında yaratılan, belli süre etkinlik gösterdikten sonra yok olan, yani ömürlerini
tamamlayan nesnelerdir. Bu tür nesnelerin ömürleri, programın toplam çalışma süresinden kısadır. Yerel değişkenler, otomatik ömürlüdür. 
Programın çalışma zamanında tanımlandıkları bloğun çalışması başladığında yaratılırlar, bloğun çalışması bitince yok olurlar, yani ömürleri sona erer.
```cpp
void run() {
    S object_1("1", "2"); // 1 is printed
    S object_2("3", "4"); // 3 is printed
} // 4 is printed, object_2's lifetime ends first
// 2 is printed, object_1's lifetime ends second

// Answer: 1342

void run() {
    {
        S object_1("1", "2"); // 1 is printed
    } // 2 is printed
    S object_2("3", "4"); // 3 is printed
} // 4 is printed

// Answer: 1234

void run() {
    S object_1("w", "e");       // w
    S object_2("e", "l");       // e
    {
        S object_3("a", "k");   // a
    }                           // k
    S object_4("l", "b");       // l
    {
        S object_5("y", "_");   // y
    }                           // _
    {
        S object_6("i", "n");   // i
    }                           // n
    S object_7("c", "a");       // c
    {
        S object_8("r", "t");   // r
        {
            S object_9("e", "m");// e
        }                        // m
        S object_10("e", "n");   // e
    }                            // n
                                // t
}                               // a
                                // b
                                // l
                                // e

// Answer: weakly_incrementable

```

**Statik ömürlü varlıklar** (static duration – static storage class), otomatik ömürlü nesneler gibi programın kendilerine geldikleri zaman 
bellekte yerlerini alırlar, fakat programın çalışması  bitene kadar varlıklarını sürdürürler, yani bellekte yer kaplar. Scopeları bitince ölmezler.
global değişkenler dizgeler (çift tırnak içindeki yazılar) statik yerel değişkenler  
```cpp
void run() {
    {
        static S object_1("1", "2"); // 1
    }
    static S object_2("3", "4");
// 3
}
// Program ends
// object_2's lifetime ends: 4
// object_1's lifetime ends: 2

// Answer: 1342
```
