#include <iostream>

int main()
{
	int a[] = { 0, 1, 2, 3, 4, 5 };
	auto r1 = a;
	auto &r2 = a;

	++r2[3];
	std::cout << (r1[3] == r2[3]) << "\n";
}
