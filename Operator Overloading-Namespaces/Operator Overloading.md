# OPERATOR OVERLOADING
Operator overloading function çağırmanın bir başka yolu aslında. Bir **sınıf nesnesi** bir operatörün operandı yapıldığında, derleyici operatörün operandı olmuş sınıf nesnesini bir fonksiyon çağrısına dönüştürüyor. Buradaki temel fikir programcıların işini kolaylaştırmak. Daha kolay daha anlaşılır kod yazmasını sağlamak. Örneğin s1 ve s2 string ve karşılaştırma yapacakken  s1.is_greater(s2) bu mu kolay s1 > s2 bu mu?   
EN ÇOK SORULANLAR?  
1 - Geri dönüş değeri türü neye göre seçilmeli?  
* Dilin kuralları bunu kendisi belirlemiyor. Kolay kullanımları seç, doğal yapıyı taklit et. Burada değer kategorilerini de göz önüne al. **++m;** için değer kategorisi L value o yüzden geri dönüş değeri Myclass& olmalı. **m1 + m2** için değer kategorisi PR value o yüzden Myclass olmalı

2 - Operator functionlarıyla const doğruluğu arasındaki ilişki nedir?   
* Global fonksiyonsa **Myclass operator+(const Myclass&, const Myclass &);** m1+m2 demek operator+(m1,m2) demek dolayısıyla ikisi de değişmediğinden 2 parametremiz de const & olmalı.   
* member function ise **Myclass& operator+=(const Myclass&);** += operatörünün değer kategorisi L o yüzden Myclass& geri dönüş değeri olmalı. m1+=m2; (m1.operator+=(m2) demek) ifadesinde m2 değişmeyeceği için parametremiz const & olmalı m1 değiştiği için üye fonksiyonumuz const olmamalı.

3 - Member function mı olsun global function mi olsun?
* Simertic binary operatorlerin global operator func olarak tercih ediliyor a > b ile b > a aynı anlamdaysa yani mantıklıysa buna simetric operator deniyor.
* Sınıf nesnesini değiştiren/yan etkisi olan operator functionların member operator function olması tercih ediliyor. 
