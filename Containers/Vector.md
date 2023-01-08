# VECTOR

Ögeler contigues şekilde dinamik olarak allocate edilmiş bir bellek bloğunda tutuluyorlar. Bu bellek bloğunda tutulan fiziksel öğe sayısı, vector size ı. 
Allocate edilmiş bellek bloğunda yeni bir bellek alanına ihtiyaç duymadan tutulabilecek öğe sayısı vectorun capacity si. Temel avantajı sondan ekleme 
ve indexle erişimin hızlı olması. En dikkat edilmesi gereken nokta, Size capacity ye eşit olduğunda bir insert işlemi yapılırsa, kapasite yetersiz olduğundan reallocation olacak,
reallocation yeni allocate edilmiş bir bellek alanına taşıyacak. Eski bellek bloğundaki öğeler yenisine kopyalanacaklar ya da taşınacaklar.
ilave maliyet bu. Ayrıca reallocation iteratörlerin invalid hale gelmesine neden olabilir.
```cpp
int main()
{
    std::vector<int> ivec1;
    //ivec.size --> 0
    bool isEmpty = ivec1.empty(); //true
    std::vector<int>::size_type n = ivec1.size();

    std::vector<int> ivec(4);
    ivec.push_back(2); //size = 11
    ivec.push_back(3); //size = 12
    ivec.push_back(7); //size = 13
    std::cout << "size = " << ivec.size() << "\n";
    std::cout << "cap = " << ivec.capacity() << "\n";
    ivec.push_back(5); //size = 14
    ivec.push_back(7); //size = 15. size capacity ile aynı oldu
    ivec.push_back(34); //Burada reallocation olacak artık. size16 capacity 22 oldu.
    std::cout << "size = " << ivec.size() << "\n";
    std::cout << "cap = " << ivec.capacity() << "\n"; //kapasite artı. Kapasite artma miktarı implementation defined.
}
```

```cpp
int main()
{
    std::vector<int> x; // default init
    std::vector<int> y{}; // value init Default ctor çağrılacak ikisinde de. Size 0 olacak empty true döndürecek.

    std::vector<int> z = x; // copy constructor

    std::vector<int> q = std::move(x);

    std::vector<int> sizeConstr(6547); //size_t parametreli constructor // Size 6547

    std::vector<int> initializerListConstr{10}; //initializer list constructor size=1

    std::vector<int> myvec{1, 2, 3, 4, 6, 8, 7, 5, 3};

    std::vector<double> dvec(myvec.begin(),myvec.end()); //range constructor
}
```
