// FUNCTION CALL OPERATOR OVERLOADING
class Functor{
public:
	void operator()(int x = 0)
	{
		std::cout << "Functor::operator()() this = " << this << " x = " << x << "\n";
	}
};

int main()
{
	Functor object;
	std:cout << "&object = "<< &object << "\n";
	object(12); // 12 yazar
	object(); // 0 yazar default arg tan ötürü.
}