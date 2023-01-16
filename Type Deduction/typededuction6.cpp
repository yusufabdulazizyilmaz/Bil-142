#include <iostream>

int main()
{
	int x = 5;
	decltype((x)) y{ x };
	decltype(y *= 2) z = x;
	decltype(y--) t = x;
	int &rx{ x };
	auto ax{ rx };

	++y;
	z *= 2;
	t *= 5;
	ax += 10;

	std::cout << "x = " << x << "\n";
}
