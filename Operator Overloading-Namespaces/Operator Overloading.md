# OPERATOR OVERLOADING
Operator overloading function çağırmanın bir başka yolu aslında. Bir **sınıf nesnesi** bir operatörün operandı yapıldığında, derleyici operatörün operandı olmuş sınıf nesnesini bir fonksiyon çağrısına dönüştürüyor. Buradaki temel fikir programcıların işini kolaylaştırmak. Daha kolay daha anlaşılır kod yazmasını sağlamak. Örneğin s1 ve s2 string ve karşılaştırma yapacakken  s1.is_greater(s2) bu mu kolay s1 > s2 bu mu?   
EN ÇOK SORULANLAR?  
1 - Geri dönüş değeri türü neye göre seçilmeli?  
* Dilin kuralları bunu kendisi belirlemiyor. Kolay kullanımları seç, doğal yapıyı taklit et. Burada değer kategorilerini de göz önüne al. **++m;** için geri dönüş değeri Myclass& olmalı. **m1 + m2** için Myclass olmalı

2 - Operator functionlarıyla const doğruluğu arasındaki ilişki nedir?   
3 - Member function mı olsun global function mi olsun?
