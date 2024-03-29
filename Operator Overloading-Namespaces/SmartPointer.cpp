class Mint;
class SmartPtr {
public:
	SmartPtr() : mp{ nullptr } { }  
	
	SmartPtr(Mint* p) : mp{ p } { }
	SmartPtr(const SmartPtr&) = delete; 
	SmartPtr& operator=(const SmartPtr&) = delete; 
	SmartPtr(SmartPtr&& other) : mp{ other.mp }
	{
		other.mp = nullptr;
	}
	~SmartPtr() 
	{
		if(mp != nullptr)
			delete mp;
	}
	Mint& operator*()
	{
		return *mp;
	}
	Mint* operator->()
	{
		return mp;
	}
	explicit operator bool()noexcept
	{
		return mp != nullptr;
	}
private:
	Mint* mp;
};

int main()
{
	{
		SmartPtr p1 = new Mint{15};
		SmartPtr p2 = new Mint{10};
		int ival = (*p1) + (*p2) ;
		p1->operator+();
		p1.operator->()->operator+(); // bununla yukarıdaki aynı.
		
		if(p2)
		{
			std::cout << "p2 bir nesneyi göstermektedir";
		}
	}
	std::cout << "Kaynaklar geri verildi\n";
}
