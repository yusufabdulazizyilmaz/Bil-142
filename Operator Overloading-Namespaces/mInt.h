/*
 * İnt türünü veri elemanı olarak alan ve int türünde olmayan 0'a bölme durumunda hata verme işini
 * yaparak int türüne ekstra özellikler kazandıran Mint sınıfı wrapper sınıftır.
 */
#ifndef EXERCISE_MINT_H
#define EXERCISE_MINT_H

#include <iosfwd>
// Dikkat neden #include <ostream> #include <istream> yazılmadı da <iosfwd> include edildi


class Mint {
public:
    explicit Mint(int x = 0);

    // simetrik olanları glabal fonksiyon yap friend olması member function yapmaz!!!
    // friend olması private bölümü kullanması için verilmiş
    friend std::ostream& operator<<(std::ostream&, const Mint&);

    friend std::istream& operator>>(std::istream&, Mint&);

    // tartışmasız en önemli operatör
    // std::set std::map gibi STL containerlarında tutmak için sınıfımızda mutlaka olmalı
    [[nodiscard]]friend bool operator<(const Mint& x, const Mint& y)
    {
        return x.mval<y.mval;
    }

    [[nodiscard]]friend bool operator==(const Mint& x, const Mint& y)
    {
        return x.mval==y.mval;
    }

    //yan etkisi olanları sınıfın member fonksiyonu yap
    Mint& operator+=(const Mint& r);

    Mint& operator-=(const Mint& r);

    Mint& operator*=(const Mint& r);

    Mint& operator/=(const Mint& r);

    Mint& operator++();

    Mint operator++(int);

    Mint& operator--();

    Mint operator--(int);

    Mint operator+() const;

    Mint operator-() const;

private:
    int mval;
};

[[nodiscard]]bool operator>=(const Mint& x, const Mint& y);

[[nodiscard]]bool operator>(const Mint& x, const Mint& y);

[[nodiscard]]bool operator<=(const Mint& x, const Mint& y);

[[nodiscard]]bool operator!=(const Mint& x, const Mint& y);

/*inline Mint operator+(const Mint& left, const Mint& right)
{
    return Mint{left} += right;
    //return left += right; yazsaydık sentaks hatası oludu left değişmemeli çünkü
}*/

// dikkat neden Mint operator+(cons Mint& left, const Mint& right); değil
inline Mint operator+(Mint left, const Mint& right)
{
    return left += right;
    //left.operator+=(right);
}

// inline olmazsa ODR(one definition rule) ihlal edilmiş olur
inline Mint operator-(Mint left, const Mint& right);

Mint operator*(Mint left, const Mint& right);

Mint operator/(Mint left, const Mint& right);

#endif //EXERCISE_MINT_H
