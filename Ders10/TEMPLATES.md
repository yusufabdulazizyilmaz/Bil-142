# GENERIC PROGRAMMING - TEMPLATES

Generic demek türden bağımsız anlamında. Öyle kod var ki farklı veri türleri için kullanılabilir. Programlamanın çok önemli alanlarından biri. 
C++ ın en güçlü olduğu alan belki de bu. C++ terminolojisinde derleyicinin compile time da bizim için kod yazmasına dayanıyor. 
Derleyiciye kod yazdıran kodlara template deniyor. Temel kategorilere ayrılıyor.  
Function Templates   
Class Templates   
Alias Template		C++11 ile geldi   
Variable Template		C++11 ile geldi   
Concept Template		C++20 ile geldi  

Standart Template Library(STL) derleyici bu templatelerden kodları oluşturuyor ve sonra derliyor. Standart kütüphanenin %98-99 oranında şablonlardan oluşuyor.

Ortada bir template varsa keyword olarakta template olmak zorunda.Derleyici buradan anlıyor template olduğunu. Template den sonra açısal parantez <> var. Açısal parantez içinde bildirilen varlıklara template parametreleri deniyor. Template parametreleri,   
	a - Type/Tür parametresi olabilir  
        template < typename T, typename U > ya da template < class T >   
	b - non-type parameter olabilir.(sabit parametre)   
        template < int x >   
	c - template template parameter olabilir. Bu ders kapsamında değil.


## FONKSIYON VE SINIF ŞABLONLARI
