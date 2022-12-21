# Reference Qualifiers
Statik olmayan bir üye fonksiyonun kodunun yazımında eğer o üye fonksiyonu çağıracak nesnenin değer kategorisine göre üye fonksiyonun
implementasyonunda verimsel açıdan farklar oluşacaksa değer kategorisine göre fonksiyonumuzu overload etmemiz gerekmektedir. C++11 ile dile eklenen
reference qualifiers bu amaca hizmet etmektedir. Reference qualifiers const gibi non static üye fonksiyonlarında bulunan gizli *this nesnesini nitelemektedir.

```cpp
class Nec {
public:
    void foo() &;

    void foo() const &;
    
    void foo() &&;
};
int main()
{
	Nec ax;
	const Nec ca;

	ax.foo(); // Nec::foo()&
	ca.foo(); // Nec::foo() const &
	Nec{}.foo(); // Nec::foo()&&
	std::move(ax).foo(); // Nec::foo()&&
	
}

class StringBuilder
{
public:
  std::string get() const& { return m_str; }
  std::string get() && { return std::move(m_str); }

private:
  std::string m_str;
};

std::string s = buildString().get();   //gereksiz kopyalama olmuyor

class Nec {
public:
	void foo()&;
	void foo() const; // gecersiz
	//reference qualified fonksiyon reference qualified olmayan fonksiyon ile yüklenemez.
};
```
