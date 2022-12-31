# COMPOSITION
Nesne yönelimli programlama, problem domainindeki varlıkları sınıflar ile temsil etmeye deniyor.
Prosedürel programlama paradigmasında(C) ayrıştırma functionlara yönelikken nesne yönelimlide ayrıştırma classlara/sınıflara yöneliktir. 
Bunlar sınıflar arasındaki ilişkileri betimleyen bazı terimler var.  
Association : Sistemdeki 2 sınıf birbiriyle işbirliği halinde kullanılıyorsa bu sınıflar arasında association vardır.  
Aggregation : Eğer bu ilişki içindeki sınıflardan biri, diğerinin sahibi olarak onu kulanıyorsa, buna aggregation deniyor. Her aggregation bir association
Composition : Yine bir nesne diğerinin sahibi fakat sahip olan ile olunan nesne arasında ömürsel birliktelik varsa yani Sahip hayata gelince, 
olunan da geliyor sahip ölünce olunan ölüyorsa buna composition deniyor. Composition bir interface edinme ilişkisi değil. Bir sınıf başka sınıf türden 
bir veri elemanına sahip olunca o veri elemanının interface ini kendi interface ine katmıyor.

class A {
public:
    void foo();

private:
    void func();

};

class B {
public:
    void g()
    {
        ma.foo();  // geçerli
        ma.func(); //Burası hata. Private bölüme erişim hakkı verilmedi

    }

private:
    A ma;
};

int main()
{
    B bx;
    bx.foo(); //BURASI HATA. İNTERFACE DEVRALINMAZ. KALITIMDA INTERFACE DEVRALINIR.
}
