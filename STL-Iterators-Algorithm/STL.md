# STL - STANDART TEMPLATE LIBRARY
STL bir acronim. Burada kastedilen aslında dilin standart kütüphanesinin template olan bileşenleri. Burada kodlar template, derleyici kodları yazıp 
sonra derleyecek. Günümüzde STL dendiğinde C++ ı standart kütüphanesinin tamamını kastediyor ama STD library nin template olmayan bileşenleride var. 
C den gelen funclar veya trigonometri functionları. Standart kütüphanemizin %95 ini belki de STL oluşturuyor. 
Template in en büyük dezavantajı hata mesajlarının çok açık olmaması. Çok basit bir hatada 200-300 satır hata alabiliriz.  
Bu kütüphanede neler var?   
En önemlileri = CONTAINERS, ITERATORS, ALGORITHMS.   
Diğerleri = Container Adapters, Iterator Adapters, Function Adapters, Function Objects.   

CONTAINERS = Veri yapılarını implemente eden sınıf şablonları. Ör: vector dinamik dizi veri yapısını implemente ediyor.

ITERATORS = Pointer benzeri arayüze sahip ve nesneleri pointer gibi kullanılabilen sınıf şablonları. Varlık sebebi Containerda bulunan
öğelerin konumunu tutmak. Containerda tutulan öğelere iterator denen nesneler yoluyla erişebiliriz. Bir pointerı * operatörünün operandı 
yapınca o adresteki nesneye erişiyorsa, iterator bir sınıf nesnesi ise, o sınıfın operator*() fonksiyonu, bizi o konumdaki nesneye eriştirecek.

ALGORITHMS = Algoritmaları implemente eden fonksiyon şablonları. sort, find, reverse ... 
Containerda bulunan veriler üzerinde birtakım işlemler yapılmasını sağlarlar. Algoritmalarla containerları birbirine bağlıyan ise iterator. 
Algoritmalar iteratorleri kullanarak containerlar üzerinde birtakım işlemler yapan functionlar.

SEQUENCE CONTAINERS
-------------------
Ekleme silme işlemleri konumla yapılıyor. İstediğim konuma istediğim öğeyi ekleyebiliyorum.
* std::vector			-> Dinamik dizi. En çok kullanılan STL containerı
* std::deque			-> double ended queue. Baştan ve sondan ekleme yapabileceğimiz veri yapısı
* std::list			-> doubly linked list
* std::forward_list		-> (C++ 11 de geldi)  singly linled list
* std::string			-> Yazı tutuyor.Gördük bunu.Bu da containers.Bunu daha çok STL algoritmalarıyla kullanacağız.
* std::array			-> (C++ 11 de geldi) array container

ASSOCIATIVE CONTAINERS
----------------------
İkili arama ağacı veri yapısı kullanılıyor. Ekleme işlemi belirli bir konum değil değerle yapılıyor. Değerin ne olduğuna bağlı olarak ekleneceği yer belirleniyor.
* std::set	-> Sadece anahtar tutuyor.Tamsayıların setini oluşturursak 17 nin sette olup olmadığını sorgulayabiliriz.Bir anahtardan bir tane var.
* std::multiset	-> Bir anahtardan birden fazla olabilir.Tamsayıların setinde 1 tane 12 olabilir.multisetinde 3,4,5,6 tane 12 olabilir.
* std::map	-> Anahtarın değerle eşlendiği veri yapısı.Anahtarla erişiyoruz yine ama anahtar karşılığı bir değere erişiyoruz.Buradakiler pair gibi anahtar değer çifti
* std::multimap	-> Bir anahtardan birden fazla olabilir.

UNORDERED ASSOCIATIVE CONTAINERS
--------------------------------
Diğer dillerdeki adı hash tablosu denen veri yapısını implemente eden sınıflar.
Neden diğer dillerden farklı olarak böyle tuhaf isimler almışlar. Görece olarak geç dile eklenmesi.
* std::unordered_set		-> (C++ 11 de geldi) Sadece anahtar tutuyor.Bir anahtardan bir tane var.
* std::unordered_multiset		-> (C++ 11 de geldi) Bir anahtardan birden fazla olabilir.
* std::unordered_map		-> (C++ 11 de geldi) Anahtarın değerle eşlendiği veri yapısı.Buradakiler pair gibi anahtar değer çifti
* std::unordered_multimap		-> (C++ 11 de geldi) Bir anahtardan birden fazla olabilir.

stack queue priority_queue bunlar kesinlikle container değil. Böyle veri yapılarına Abstract Data Type (ADT) denir. 
Bunlar STL de containerları eleman olarak (composition ilişkisi ile) aldığı containerın interface ini bu soyut veriyapısına adapte eden yardımcı sınıflar.
      
RANGE: İki konumun oluşturduğu birime range denir. Birinci konumu artırdığımda bir süre sonra ikinci konuma eşitlenmeli. Range sözkonusu olduğunda konum1 
dahil ama konum2 dahil değil. [konum1,konum2).     ] Öge sayısı konum2-konum1 kadardır.

```cpp
#include <vector>
#include <string>
#include <iostream>

// val değeri range'de aranacak bulursa konumu bulamazsa end konumunu döndürülecek.
template<typename Iter, typename T>
Iter Find(Iter beg, Iter end, const T& val)
{
    while (beg!=end) {
        if (*beg==val)
            return beg;
        ++beg;
    }
    return end;
}
/*Algoritmanın gücü : Birkaç satırlık func şablonu bu.Bu şablondan yazılacak function, bir int dizide int te arayabilir
bir bağlı listede tarihte arayabilir, oyun programındaki fighter sınıf türünden nesneler tutan dizide
bir fighterda arayabilir.Derleyici bu template ten kodu gönderdiğimiz türe göre yazacak.*/

// Iter sınıfının != * ++ operatörlerini overload etmesi lazım.
int main()
{

    std::vector<std::string> svec{"dogus", "necati", "ayse", "gizem", "can", "umut"};
    std::string name = "gizem";
    if (std::vector<std::string>::iterator iter = Find(svec.begin(), svec.end(), name);
            iter!=svec.end()) // end değilse öğeyi bulmuştur.
    {
        std::cout << "bulundu ... " << *iter << "\n"; // bulduysa değer yazılacak.
    }
    else {
        std::cout << "bulunamadi\n";
    }
}

namespace std {
    template<typename T, typename Allocator = std::allocator<T>>
    class Vector {
    public:
        //bunun iterator gibi nesned typeları var
        class iterator {
        public:
            bool operator!=(const iterator&);

            iterator& operator*();

            iterator& operator++();
        };

        iterator begin(); //konumları tutuyorlar. ilk öğenin konumunu tutuyor
        iterator end();    // bu son öğeden bir sonraki konumu döndürüyor.
    };
}

```
