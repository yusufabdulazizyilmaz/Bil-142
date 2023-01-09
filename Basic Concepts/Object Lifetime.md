### Nesnelerin Ömürleri (storage duration / lifespan)
Ömür (storage duration / lifespan), nesnelerin, programın çalışma zamanı içinde bellekte yer kapladığı süreyi anlatmak için kullanılan bir terimdir. 
Bir kaynak kod içinde tanımlanmış değişkenlerin hepsi, program çalışmaya başladığında aynı zamanda yaratılmaz. C++'da 4 çeşit ömür kategorisi vardır:  
* Otomatik  
* Statik  
* Dinamik  
* Thread_local  

Aşağıdaki örnekleri anlayabilmemiz için nesnelerimizin kurallarını açıklayalım.  
S object_1("First Name", "Last Name");  
S : The object’s Type    
object_1 : The object’s ID  
"First Name" : The object’s first name  (Hayata gelince ekrana yazacak ifade)  
"Last Name" : The object’s last name (Hayatı sonlanınca ekrana yazacak ifade)  
Her zaman geçerli bir kuralı ifade edelim öncelikle:  
**İLK HAYATA GELEN EN SON VEDA EDER.** ya da **İŞE EN SON GİREN İLK ATILIR.**    

* **Otomatik ömürlü nesneler** programın çalışmasının belli bir zamanında yaratılan, belli süre etkinlik gösterdikten sonra yok olan, yani ömürlerini
tamamlayan nesnelerdir. Bu tür nesnelerin ömürleri, programın toplam çalışma süresinden kısadır. Yerel değişkenler, otomatik ömürlüdür. 
Programın çalışma zamanında tanımlandıklarında yaratılırlar, bloğun çalışması bitince yok olurlar, yani ömürleri sona erer.
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

* **Statik ömürlü varlıklar** (static duration – static storage class), otomatik ömürlü nesneler gibi programın kendilerine geldikleri zaman 
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

void run()
{
    {
        {
            S object_1("c", "b");                   //c
            {
                static S object_2("t", "k");        //t
                S object_3("y", "p");               //y
            }                                       //p
            S object_4("e", "_");                   //e
        }                                           //_
                                                    //b
        S object_5("a", ":");                       //a
        static S object_6("s", "s");                //s
        S object_7("e", ":");                       //e
    }                                               //:
                                                    //:
    S object_8("m", "a");                           //m
}                                                   //a
// Program ends
// s
// k

// Answer: ctype_base::mask
```
* **Dinamik ömürlü varlıklar** ömürleri new ifadesi ile başlayıp, delete ifadesi ile biten nesnelerdir. Hayatlarının kontrolü tamamen
yazılımcıya aittir. Eğer öldürülmezse kaynak sızıntısına neden olur.

```cpp
void run() {
    S *object_1 = new S("l", "c");          //l
    S *object_2 = nullptr;
    object_2 = new S("o", "g");             //o
    delete object_1;                        //c
    S *object_3 = new S("k", "y");          //k
}
// Answer: lock

void run() {
    {
        S object_1("l", "c");               //l
        S *object_2 = new S("o", "q");      //o
        S *object_3 = nullptr;
    }                                       //c
    S *object_4 = new S("a", "q");          //a
    S object_5("l", "e");                   //l
    S *object_6 = nullptr;
}                                           //e
// Answer: locale

void run() {
    {
        S *object_1 = new S("n", "m");      //n
        static S object_2("u", "t");        //u
        {
            delete object_1;                //m
            S *object_3 = nullptr;
            object_3 = new S("p", "a");     //p
        }
        static S object_4("u", "c");        //u
    }
    S *object_5 = new S("n", "v");          //n
    S *object_6 = nullptr;
}
// Program ends
// c
// t

// Answer: numpunct

void run() {
    S object_1("i", "t");                   //i
    S object_2("n", "p");                   //n
    static S object_3("o", "t");            //o
    S *object_4 = new S("u", "y");          //u
    static S object_5("t", "_");            //t
    {
        static S object_6("_", "r");        //_
    }
}                                           //p
                                            //t
// Program ends
// r
// _
// t

// Answer: inout_ptr_t
```













