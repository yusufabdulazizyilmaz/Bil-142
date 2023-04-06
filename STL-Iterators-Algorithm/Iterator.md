# ITERATOR
Pointer like bir interface e sahip dolayısı ile bunların sınıf türünden nesneler olması durumunda yine pointer gibi 
kullanılmasını sağlayan operator overloading mekanizması. Bir iteratörün hangi işlemlerde kullanılabileceğini belirleyen iteratörün kategorisi.
Bu kategorilere isimler verilmiş. Her iteratörün bir kategorisi olmak zorunda.
* Output iterator
* Input iterator
* Forward iterator
* Bidirectional iterator
* Random access iterator
* Contiguous iterator (C++17)

![Screenshot 2023-01-08 at 10 36 55](https://user-images.githubusercontent.com/92329809/211185533-cd6014c3-c7ea-45cf-9a05-969b91657192.png)

Bütün iteratorlerin iterator_category isimli bir nested type ı var. iterator kategorisinin ne olduğunu anlamanın yolu, iterator sınıfının iterator category
nested type ının ne olduğuna bakmak. **vector<int>::iterator::iterator_category** 
  
| 		ITERATOR KATEGORİLERİ		  |						OPERASYONLAR						      |													  |
|-------------------------------------------------|-------------------------------------------------------|-------------------------------|
|						      |	Copy constructible				  |		    		      |	
|	 OUTPUT ITERATOR	  		  |	++it	it++	=				  |	   	 ostream_iterator    		      |
|						  |	*it		it->  (sol taraf değeri)	  |  ostreambuf_iterator						      |
|						  |							  |						      |
|						  |	Copy constructible			  	  |						      |
|						  |	++it	it++	=		  	  	  |		 istream_iterator     		      |
|	  INPUT ITERATOR	  		  |	*it		it->  (sağ taraf değeri)	  |	istreambuf_iterator	      		      |
|						  |	it1 == it2		it1 != it2		  |						      |
|						  |							  |						      |
|						  |	Copy constructible - Default Constructible	  |		 				      |
|						  |	++it	it++	=				  |	forward_list		    		      |
|	FORWARD ITERATOR	  		  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	unordered_set		unordered_multiset    |
|						  |	it1 == it2		it1 != it2		  |	unordered_map		unordered_multimap    |
|						  |							  |						      |
|						  |	Copy constructible - Default Constructible	  |						      |
|		BIDIRECTIONAL				  |	++it	it++	--it	it--		=	  |	list					      |
|	 	ITERATOR	 		  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	set		multiset		      |
|	    		  		  |	it1 == it2		it1 != it2		  |	map		multimap		      |
|						  |							  |						      |
|						  |							  |						      |
|						  |	Copy constructible - Default Constructible        |						      |
|						  |	++it	it++		--it	it--	=	  |	vector			      		      |
|						  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	deque			      		      |
|	  RANDOM ACCESS		  		  |	it1 == it2		it1 != it2		  |	array			      		      |
|	    ITERATOR		  		  |	it + n		n + it		it - n		  |	string			      		      |
|	(Pointer Interface )  			  |	it+=n		it-=n				  |	C array			      		      |
|						  |	it1 - it2					  |						      |
|						  |	it[n]						  |						      |
|						  |	it1 < it2   it1 <= it2   it1 > it2   it1 >= it2   |						      |

```cpp
template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
    while (first!=last) {
        *d_first++ = *first++;
    }
    return d_first;
}
```
Bu algoritma ile bir bağlı listeden bir dinamik dinamik diziye kopyalama yapılabilir mi?
Çünkü bağlı listenin iteratörleri Bidirectional (inputu kapsıyor), Vectorunkide Random access zaten.  
NESNEYE SALT OKUMA AMAÇLI ERIŞIM ISTERSEK NE YAPACAĞIZ ++iter olmalı veya iter +2 olmalı, *iter yine olmalı 
*iter = 54; BU SENTAKS HATASI OLMALI. 
Modern C++ auto type deduction gelmesiyle containerlara cbegin ve cend funclarıda eklendi.
begin() return değeri vectorun<int>::iterator ise cbegin() return değeri vectorun<int>::const_iterator türüdür.
## ITERATOR ADAPTÖRLERİ
Iteratörleri eleman olarak ya da kalıtımla alıp onların interfaceini değiştiren sınıflara ITERATOR ADAPTÖRÜ deniyor.
  
```cpp
int main()
{
    using namespace std;
    std::vector<int> x{3, 5, 6, 7, 8};
    std::vector<int> y;
    std::copy(x.cbegin(), x.cend(), y.begin());
    // UNDEFINED BEHAVIOR. x'ten yazılacak öğe sayısı kadar y'de yer olmalı.
    std::copy(x.cbegin(), x.cend(), back_inserter(y));
}
```
OutputIt öyle bir tür olsunki d_first * ve ++ nın operandı yapınca d_first elde edelim.
Yani OutputIt öyle bir tür olsun ki, *d_first = d_first veya ++d_first = d_first olmalı !!!
Aynı zamanda copy asisgnment yazmamız lazım, bu atama operator fonksiyonu containera push_back yapacak.

```cpp
template<typename C>
class BackInsertIterator {
public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    BackInsertIterator(C& c)
            :mc{c} { }
    BackInsertIterator& operator*() { return *this; }      // *destbeg ile destbeg aynı olması için
    BackInsertIterator& operator++() { return *this; }     // ++destbeg ile destbeg aynı olması için
    BackInsertIterator& operator++(int) { return *this; }  // destbeg++ ile destbeg aynı olması için
    
    //value_type tür bilgisi. C ye bağlı tür olduğundan typename geldi. 
    // push edilecek değer int. C ise vector<int>. C::value_type ile int türüne erişebildik
    BackInsertIterator& operator=(const typename C::value_type& val)
    {                                    
        mc.push_back(val);                 
        return *this;
    }
  
    BackInsertIterator& operator=(typename C::value_type&& val)
    {                                    
        mc.push_back(std::move(val));                 
        return *this;
    }

private:
    C& mc;
    // Bu sınıf türden nesne bir containerı referans tutuyor olacak. Bu sınıfın kodları mc yi kullandığında,
    // referans yoluyla bağlanan containerı kullanmış olacak.
};

template<typename C>
BackInsertIterator<C> BackInserter(C& x)
{
    return BackInsertIterator<C>{x};
}
```
BACK INSERTER, SONDAN EKLEME YAPIYOR FRONT INSERTER, BAŞTAN EKLEME YAPIYOR(LİSTTE VAR VECTORDE YOK) INSERTER, BENİM VERDİĞİM KONUMDAN EKLEME YAPIYOR.

```cpp
#include <iostream>
#include <iterator>
#include <vector>

template<typename Iter>
void print(Iter first, Iter last)
{
    while (first!=last)
        std::cout << *first++ << " ";
    std::cout << "\n";
}

int main()
{
    std::vector<int> ivec{1, 4, 5, 7, 9, 4};
    print(ivec.begin(), ivec.end()); // BAŞTAN SONA YAZIYOR
    print(ivec.rbegin(), ivec.rend()); // SONDAN BAŞA YAZDIRDI
}
/* CIKTI:
1 4 5 7 9 4 
4 9 7 5 4 1 */ 
```
Sınıfların iterator türü dışında bir de reverse iterator isimli nested typeı var. Mesela vector sınıfının reverse_iteratör sınıfı türünden bir nesne oluşturabiliriz. **std::vector<int>::reverse_iterator iter = ivec.rbegin();**
![Screenshot 2023-01-08 at 12 33 49](https://user-images.githubusercontent.com/92329809/211189252-9009dc86-4dac-4d6a-b9d0-90db502d60d9.png)

++Iter yapınca aslında tam tersi -- işlemi yapıyor. Normal iteratörün tam tersi gibi davranıyor. * ile bir önceki nesneye eriştiriyor. 

Reverse iteratör, iter konumunu tuttuğunda fiziksel olarak, * functionu ondan bir önceki nesnenin konumuna eriştiriyor. Yani rbegin gerçek olarak containerdaki end konumunu tutuyor ama * / içerik / dereference / indirection operatörü o konumdaki nesneye değil o konumdan bir önceki nesneye eriştiriyor. Rend gerçek olarak containerdaki begin konumunu tutuyor.

Sinifin implementasyonunda reverse iteratör sinifi, normal iteratör sinifindan kalitimla elde ediliyor. Sinifa base isimli bir func koymuşlar, bu func reverse iteratörün sarmaladiği gerçek iteratörü döndürüyor.yani dereference edince bir tane geri gelip dereference etmiyor. Tuttuğu yeri döndürüyor. Bildiğimiz gerçek iteratör artik bu.
  
```cpp
int main()
{
    std::vector<int> ivec{10,20,30,40,50};
    auto riter = ivec.rbegin(); // end i tutuyor
    ++riter;	// dizinin son öğesinde şuanda
    std::cout << *riter<< "\n"; // bir önceki öğeye gelip dereference eder.Yani 40
    auto iter = riter.base(); // Halen gerçek konumu 50 nin konumu
    std::cout << *iter<< "\n"; // bu konumu dereference ederse 50 yazar.Reverse iteratordeki gibi bir önceye gelip dereference etmiyor.
}  
```
MÜLAKAT SORUSU 
Verilen değerden en sonuncusunu vectorden sil.
```cpp
int main()
{
    std::vector<int> ivec{2, 4, 5, 7, 8, 4, 5, 6, 2, 4};
    int ival = 2; // 2 yi containerdan sil
    auto iter = find(ivec.rbegin(), ivec.rend(), ival); // buradaki return değerde reverse iterator
    if (iter!=ivec.rend()) {
        // ivec.erase(iter); // BURASI SENTAKS HATASI. ERASE VECTÖRÜN ITERATOR TÜRÜNDEN, REVERSE İTERATÖR TÜRÜNDEN DEĞİL.

        // DEREFERENCE EDİNCE O BİR ÖNCEKİNİ gösterdiği için şu an gerçek konumu 4 üzerinde. 
        //ivec.erase(iter.base()); // 4 sileriz

        ivec.erase(iter.base()-1); // Doğrusu.
        print(ivec.begin(), ivec.end());

    }
}
```
Container con olsun
 * con.begin ->					return değeri : container::iterator
 * con.cbegin -> const iterator			return değeri : container::const_iterator
 * con.rbegin -> Reverse itetator			return değeri : container::reverse_iterator
 * con.crbegin -> const reverse iterator		return değeri : container::const_reverse_iterator

## ITERATORLER ÜZERİNDE İŞLEM YAPAN ALGORİTMALAR
  
 * advance
 * distance
 * next
 * prev
 * iter_swap 
 ```cpp

#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto vi = v.begin();
    std::advance(vi, 5);
    std::cout << "advance(v.begin(), 5) = " << *vi << '\n';

    vi = v.end();
    std::advance(vi, -6);
    std::cout << "advance(v.end(), -6) = " << *vi << '\n';

    auto nx = std::next(vi);
    std::cout << "next(vi) = " << *nx << '\n';
    nx = std::next(vi, 2);
    std::cout << "next(vi,2) = " << *nx << '\n';

    auto pv = std::prev(vi);
    std::cout << "prev(vi) = " << *pv << '\n';
    pv = std::prev(vi, 2);
    std::cout << "prev(vi,2) = " << *pv << '\n';

    std::cout << "distance(pv,nx) = " << std::distance(pv, nx) << '\n';
  
    // Iter_swap doesnt swap iterators. İterator konumundaki 2 nesneyi swap ediyor.
    std::iter_swap(v.begin(), prev(v.end()));

    std::cout << "v.begin() = " << *v.begin() << '\n';
    std::cout << "prev(v.end()) = " << *prev(v.end()) << '\n';
}
 ```
  
