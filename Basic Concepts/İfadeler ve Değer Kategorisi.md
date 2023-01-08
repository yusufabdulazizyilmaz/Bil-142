# İfade (Expression)

Değişken, işleç ve değişmezlerin bileşimlerine ifade (expression) denir. Örneğin: a + b / 2, a, foo(), 30.  Tekbaşına bir değişken ve sabit ifade belirtir, fakat tek başına bir operatör ifade belirtmez. Derleyicinin derleme zamanında değerlerini bilme ya da hesaplama garantisi olan ifadelere sabit ifadesi (constant expression) denir.

İfadenin 2 önemli niteliği vardır. Bunlar:
* Türü (Data Type)
* Değer kategorisi (value category)

Hemen her araç değer kategorisiyle / value category ilgili hale geliyor C++ dilinde.
İfadenin değer kategorisi, o ifadenin dilin kurallarına göre nerelerde kullanılabileceğini ve kullanımlarının ne ifade edeceğini belirliyor.
Bir ifadenin değer kategorisi 3 farklı kategoriden birine ait olmak zorunda. Bunlara primary value categories deniyor.
* Lvalue Expression 
* PrValue Expression 
* Xvalue Expression. 

Bunlardan ikisine birden ait olamaz.

lvalue  : bu ifade bir nesneye ya da bir kimliğe karşılık geliyor mu ve kaynağı güvenli olarak çalınamayan ifadeler.

prvalue : bir ifadenin değerini hesaplamak veya bir nesneyi initialize etmek için kullanılıyor. kaynağı çalınabilir güvenli şekilde.

xvalue  : Taşıma semantiği ile eklendi. Öyle bir nesne ki kaynakları tekrar kullanılabilir anlamında. expiring value.

Lvalue Expression
-----------------
The following expressions are lvalue expressions:

* the name of a variable, a function, a template parameter object (since C++20), or a data member, regardless of type, such as std::cin or std::endl.
* a string literal, such as "Hello, world!";
* a = b, a += b, a %= b, and all other built-in assignment and compound assignment expressions;
* ++a and --a, the built-in pre-increment and pre-decrement expressions;
* *p, the built-in indirection expression;
* a[n] and p[n], the built-in subscript expressions, where one operand in a[n] is an array lvalue (since C++11);
* a.m, the member of object expression,
* p->m, the built-in member of pointer expression, except where m is a member enumerator or a non-static member function;

Properties of L value:  
* Address of an lvalue may be taken by built-in address-of operator: &++i[1] and &std::endl are valid expressions.
* A modifiable lvalue may be used as the left-hand operand of the built-in assignment and compound assignment operators.
* An lvalue may be used to initialize an lvalue reference; this associates a new name with the object identified by the expression.

Lvalue detaylar için http://plepa.com/2017/01/05/ifade-deger-kategorileri/ bakılabilir.

PRVALUE Expression
-------

* a literal (except for string literal), such as 42, true or nullptr;
* the this pointer;
* Sınıf geçici nesnesi   Myclass{}
* Operators execpt  [], * , = , prefix ++, prefix --
* a++ and a--, the built-in post-increment and post-decrement expressions;
* a + b, a % b, a & b, a << b, and all other built-in arithmetic expressions;
* a && b, a || b, !a, the built-in logical expressions;
* a < b, a == b, a >= b, and all other built-in comparison expressions;
* &a, the built-in address-of expression;


Özel durumlar

* , virgül operatörünün sağ operandı lvalue expr ise bunun ürettiği değer lvalue expr prvalue expr ise bunun ürettiği değer PRvalue expr. 
* a ? b : c, ternary operatörünün b ve c ksımı Lvalue expr ise bunun ürettiği değer Lvalue yoksa PR value

* a cast expression to type, such as static_cast<int>(x)  PR value
* a cast expression to lvalue reference type, such as static_cast<int&>(x)    L value
* a cast expression to rvalue reference type, such as static_cast<int&&>(x)    X value
* a function call, whose return type is type,   PR value  int foo();    foo() PRvalue
* a function call, whose return type is lvalue reference,  L value   int& foo();    foo() Lvalue
* a function call, whose return type is rvalue reference,  X value  int&& foo();    foo() Xvalue
