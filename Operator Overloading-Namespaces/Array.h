#include <iostream>
#include "mint.h"

class Array {
public:
    explicit Array(std::size_t n)
            :msize{n}, mp{new Mint[msize]} { }

    ~Array() { delete[] mp; }
    // Rule of 5 copy constructor and copy assignment operator function yazılmalı

    Array(const Array& other)
            :msize{other.msize}, mp{new Mint{*(other.mp)}} { }

    Array& operator=(const Array& other)
    {
        if (this!=&other) {
            msize = other.msize;
            mp = new Mint(*(other.mp));
        }
        return *this;
    }

    std::size_t size() const { return msize; }

    Mint& operator[](std::size_t idx)
    {
        return mp[idx];
    }

    const Mint& operator[](std::size_t idx) const
    {
        return mp[idx];
    }

    friend std::ostream& operator<<(std::ostream& os, const Array& a)
    {
        os << "(";
        for (size_t i = 0; i<a.size()-1; ++i) {
            os << a[i] << ", ";
        }
        return os << a[a.size()-1] << ")"; // Son elemanın ayrı Return edilmesi gerekiyor
    }

private:
    std::size_t msize;
    Mint* mp;
};

/*
#include "Array.h"

int main()
{
    Array a(10);
    std::cout << a.size() << "\n";
    for (int i = 0; i<a.size(); i++)
        a[i] = Mint{i};
    std::cout << a;
}
 */