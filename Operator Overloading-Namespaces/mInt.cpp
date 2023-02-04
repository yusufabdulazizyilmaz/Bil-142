#include "mInt.h"
#include <ostream>
#include <istream>
#include <stdexcept>

Mint::Mint(int x)
        :mval{x} { }

std::ostream& operator<<(std::ostream& os, const Mint& m)
{
    return os << "(" << m.mval << ")";
    // burada çağrılanlar ostream sınıfının member funcları ya da global functionlar.
    //buradan çağrılan en son functionda os i referans yoluyla döndürdüğü için bunu return edebiliriz.
}

std::istream& operator>>(std::istream& is, Mint& m)
{
    return is >> m.mval;
}

Mint& Mint::operator+=(const Mint& r)
{
    mval += r.mval;
    return *this;
    // -= operatörünün değer kategorisi L value
    // kendisine atama yapılan nesneyi ref semantiği ile döndürdü
}

Mint& Mint::operator-=(const Mint& r)
{
    mval -= r.mval;
    return *this;
    // -= operatörünün değer kategorisi L value
    // kendisine atama yapılan nesneyi ref semantiği ile döndürdü

}

Mint& Mint::operator*=(const Mint& r)
{
    mval *= r.mval;
    return *this;
    // *= operatörünün değer kategorisi L value
    // kendisine atama yapılan nesneyi ref semantiği ile döndürdü
}

Mint& Mint::operator/=(const Mint& r)
{
    if (r.mval==0)
        throw std::runtime_error("Sifira bolme hatasi\n");

    mval /= r.mval;
    return *this;
    // /= operatörünün değer kategorisi L value
    // kendisine atama yapılan nesneyi ref semantiği ile döndürdü
}

// operatör + sign
// return değeri sağ taraf değeri olduğundan referans yapmadık
Mint Mint::operator+() const
{
    return *this;
}

// operatör - sign
// return değeri sağ taraf değeri olduğundan referans yapmadık
Mint Mint::operator-() const
{
    return Mint{-mval};
    // Mint türünden geçici nesne ama bunu mval değil -mval ile oluşturup return ettik.
}

//prefix ++ değer kategorisi L value
Mint& Mint::operator++() //prefix
{
    ++mval;
    return *this;
}

// postfix ++ dummy int. biz değil derleyici kullanacak
Mint Mint::operator++(int) //postfix. dummy int. biz değil derleyici kullanacak
{
    // nesneyi temp isimli değişkende sakladı yani kopyasını çıkardı
    Mint temp{*this};

    ++*this;
    // *this Mint türünden bir nesne dolayısıyla operatör overloading devreye girecek.
    //this->operator++(); yani prefix ++ çağrılacak bu da aynı şey bir üstteki ile.

    return temp; // ama kopyayı return et. klasik x++;
}

//prefix -- değer kategorisi L value
Mint& Mint::operator--()
{
    --mval;
    return *this;
}

//postfix. dummy int. biz değil derleyici kullanacak
Mint Mint::operator--(int)
{
    Mint temp{*this}; // bir kopyasını al

    --*this;
    // kendisini bir azalt. this->operator--(); //prefix -- fonksiyonunu çağıracak.

    return temp; // ama kopyayı return et. klasik x--;
}

bool operator>=(const Mint& x, const Mint& y)
{
    return !(x<y);
    //return !operator<(x, y);
}

bool operator>(const Mint& x, const Mint& y)
{
    return y<x;
    //return operator<(y,x);
}

bool operator<=(const Mint& x, const Mint& y)
{
    return !(y<x);
    //return !operator<(y, x);
}

bool operator!=(const Mint& x, const Mint& y)
{
    return !(x==y);
    //return !operator(x,y); böylede olur.
}

Mint operator-(Mint left, const Mint& right)
{
    return left -= right;
    //left.operator-=(right);
}

Mint operator*(Mint left, const Mint& right)
{
    return left *= right;
    //left.operator*=(right);
}

Mint operator/(Mint left, const Mint& right)
{
    return left /= right;
    //left.operator/=(right);
}
