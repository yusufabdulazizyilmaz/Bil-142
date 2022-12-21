# SPECIAL MEMBER FUNCTIONS
Bu fonksiyonlar dilin kuralları tarafından garanti altına alınmış, belirli koşullar sağlandığında derleyici tarafından yazılabilen fonksiyonlara
Special Member Functions denir. Buna derleyicinin bu kodu default etmesi deniyor.   
DEFAULT CONSTRUCTOR.   
DESTRUCTOR.   
COPY CONSTRUCTOR.  
COPY ASSIGNMENT OPERATOR FUNCTION.  
MOVE CONSTRUCTOR C++11.
MOVE ASSIGNMENT OPERATOR FUNCTION C++11. 
```cpp
class A {
public:
	A(); //varsayılan kurucu işlev (default constructor)
	~A(); //sonlandırıcı işlev (destructor)
	A(const A &); //kopyalayan kurucu işlev (copy constructor)
	A &operator=(const A &); //kopyalayan atama işlevi (copy assignment operator function)
	A(A &&); //taşıyan kurucu işlev (move constructor)
	A &operator=(A &&); //taşıyan atama işlevi (move assignment operator function)
};
```
