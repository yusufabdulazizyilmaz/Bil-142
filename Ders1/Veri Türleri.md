# Veri Türleri
Nesneler türü (type) derleyiciye o nesnenin nasıl yorumlanacağı hakkında bilgi verir. 
Bir nesnenin türü onun bellekteki uzunluğu hakkında da bilgi verir. Her türün bellekte 
ne kadar uzunlukta bir yer kapladığı programlama dillerinde önceden belirtilmiştir.  Bir
nesnenin türü, ayrıca o nesne üzerinde hangi işlemlerin yapılabileceği bilgisini de verir.

https://en.cppreference.com/w/cpp/language/type

fundamental types: void; std::nullptr_t; arithmetic;

compound types: function; array; pointer; pointer-to-member; reference; union; enumeration; class; 

arithmetic types: floating-point(float, double, long double); integral(bool, char, signed char, unsigned char, 
(unsigned) short int, (unsigned) int, (unsigned) long int, (unsigned) long long int);

Hap bilgiler:

1. en çok kullanılan veri türleri tamsayılar için int türüyken, gerçek sayılar için double veri türüdür.
2. char türü 1 byte uzunluğunda olmak zorundadır.
3. short <= int <= long (byte olarak)
4. Gerçek sayılarla yapılan işlemler tam sayılarla yapılan işlemlere göre çok daha yavaştır.
