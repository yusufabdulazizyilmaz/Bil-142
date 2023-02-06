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
		if(mp)
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
	}
	std::cout << "Kaynaklar geri verildi\n";
}