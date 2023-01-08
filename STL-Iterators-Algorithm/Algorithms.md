# ALGORITHMS
STL de predicate return değeri bool olan callablelara deniyor. Callable demek, fonksiyon, fonksiyon pointerı, functor class nesnesi ya da lambda 
ifadesi demektir. Eğer bu functionlar 1 parametreli ise unary predicate, İki parametreli ise binary predicate olarak adlandırılır.
```cpp
template<class InputIt, class T>
constexpr InputIt find(InputIt first, InputIt last, const T& value)
{
    for (; first != last; ++first)
        if (*first == value)
            return first;
 
    return last;
}

template<class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first)
        if (p(*first))
            return first;
 
    return last;
}

bool is_len_5(const std::string& str)
{
    return str.length()==5;
}

using namespace std;

int main()
{
    vector<string> svec;
    rfill(svec, 10, rtown);
    print(svec);
    // Burada bizim yazdığımız fonksiyona vectordeki stringler gönderilecek.
    // Ne zaman true olursa return edecek
    find_if(svec.begin(), svec.end(), is_len_5); //function
    find_if(svec.begin(), svec.end(), &is_len_5); //function pointer

    if (auto iter = find_if(svec.begin(), svec.end(), is_len_5); iter!=svec.end()) {
        std::cout << "bulundu ..." << iter-svec.begin() << " indisli oge " << *iter << "\n";
    }
    else {
        std::cout << "bulunamadi\n";
    }
}
/* ÇIKTI:
sakarya mus burdur tekirdag agri trabzon erzurum manisa zonguldak adana 
-----------------------------------------------------------------------------
bulundu ...9 indisli oge adana
*/
```
BUNU HERHANGIBIR UZUNLUĞU KONTROL EDECEK ŞEKILDE YAZMAMIZ GEREKIR.
```cpp
class LenPred {
public:
    LenPred(size_t len)
            :mlen{len} { }

    bool operator()(const std::string& s)
    {
        return s.size()==mlen;
    }

private:
    size_t mlen;
};

using namespace std;

int main()
{
    vector<string> svec;
    rfill(svec, 10, rtown);
    print(svec);

    size_t len;
    cout << "uzunluk kac olan bulunsun : ";
    cin >> len;

    if (auto iter = find_if(svec.begin(), svec.end(), LenPred{len}); iter!=svec.end()) {
        std::cout << "bulundu ..." << iter-svec.begin() << " indisli oge " << *iter << "\n";
    }
    else {
        std::cout << "bulunamadi\n";
    }
}
/* ÇIKTI:
bitlis manisa kirsehir denizli sinop bingol nevsehir tekirdag trabzon gumushane 
-----------------------------------------------------------------------------
uzunluk kac olan bulunsun : 8
bulundu ...2 indisli oge kirsehir
*/
```
LenPred{len} burada geçici nesne bizim tarafımızdan değeri verilmiş bit tamsayı ile construct ediliyor.
Daha sonra algoritma bunu callable olarak kullanacak.Her bir string değeri için uzunluk uyuşuyor mu diye bakacak.
Bizim yazdığımız find_if ten koduna bakılırsa nasıl bir şekilde callable olarak kullandığı görülür.
func call operatörünü overload eden sınıflara functor veya function object sınıfları deniyor.
Bunlar özellikle STL algoritmalarında algoritmanın predicate veya callable parametresine argüman olarak gönderiliyor
ve çok daha esnek bir yapı sağlanıyor.
```cpp
using namespace std;

int main()
{
    vector<string> svec;
    rfill(svec, 10, rtown);
    print(svec);
    size_t len;
    cout << "uzunluk kac olan bulunsun : ";
    cin >> len;
    if (auto iter = find_if(svec.begin(), svec.end(),
                [len](const string& s) { return s.size()==len; }); iter!=svec.end()) {
        std::cout << "bulundu ..." << iter-svec.begin() << " indisli oge " << *iter << "\n";
    }
    else {
        std::cout << "bulunamadi\n";
    }
}
/* ÇIKTI:
sakarya van aksaray bitlis bitlis bartin sirnak igdir eskisehir mugla 
-----------------------------------------------------------------------------
uzunluk kac olan bulunsun : 5
bulundu ...7 indisli oge igdir
*/
```
[len] (const string &s){return s.size() == len;} -> Burada derleyici bir sınıf yazacak ve bunu o sınıf türünden bir geçici nesne ifadesine döüştürecek
Bu derleyicinin yazdığı sınıf türden nesne olduğu için find_if algoritmasının ikinci tempalte tür parametresi bu sınıf türünden nesne olacak.
Bu nesne func call operatörünün operandı olacak için algoritma içinde.
* Lambdaları daha detaylı anlayabilmek ve öğrenebilmek için mutlaka [inceleyiniz.](https://www.youtube.com/watch?v=ZIPNFcw6V9o)
* Algoritmaları daha detaylı anlayabilmek ve öğrenebilmek için mutlaka [inceleyiniz.](https://www.fluentcpp.com/getthemap/)
