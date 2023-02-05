template<typename T>
struct ValCat {
	static constexpr const char* p = "PR value";
};

template <typename T>
struct ValCat <T&> {
	static constexpr const char* p = "L value";
};

template <typename T>
struct ValCat <T&&> {
	static constexpr const char* p = "X value";
};

#include <iostream>

#define  print_val_cat(expr)   std::cout << "value category of expr '" #expr "' is : " << ValCat<decltype((expr))>::p << '\n'

class Nec{  int mx; };

Nec f1();
Nec& f2();
Nec&& f3();
Nec* f4();
Nec** f5();


int main()
{
  int x = 10;  
  int y = 20;  
  int a[5]{};  
  int* ptr{ a }; 
  int& r = x; 
  int&& rr = 10;
  print_val_cat(x);
  print_val_cat(&x);
  print_val_cat(+x);
  print_val_cat(x + 5);
  print_val_cat(++x);
  print_val_cat(y--);
  print_val_cat(a[3]);
  print_val_cat(r);
  print_val_cat(rr);
  print_val_cat(*ptr);
  print_val_cat(&ptr);
  print_val_cat(ptr);
  print_val_cat(y += x);
  print_val_cat(y == x);
  print_val_cat('A');
  print_val_cat("a");
  print_val_cat(nullptr);
  
  print_val_cat(static_cast<double>(x));
  print_val_cat(static_cast<int&>(x));
  print_val_cat(static_cast<int&&>(x));
  print_val_cat((r, *ptr));
  print_val_cat((r, &ptr));
  
  print_val_cat(f1);
  print_val_cat(f1());
  print_val_cat(f2());
  print_val_cat(f3());
  print_val_cat(f4());
  print_val_cat(f5());
  print_val_cat(*f5());
  print_val_cat(**f5());
}
/*
value category of expr 'x' is : L value
value category of expr '&x' is : PR value
value category of expr '+x' is : PR value
value category of expr 'x + 5' is : PR value
value category of expr '++x' is : L value
value category of expr 'y--' is : PR value
value category of expr 'a[3]' is : L value
value category of expr 'r' is : L value
value category of expr 'rr' is : L value
value category of expr '*ptr' is : L value
value category of expr '&ptr' is : PR value
value category of expr 'ptr' is : L value
value category of expr 'y += x' is : L value
value category of expr 'y == x' is : PR value
value category of expr ''A'' is : PR value
value category of expr '"a"' is : L value
value category of expr 'nullptr' is : PR value
value category of expr 'static_cast<double>(x)' is : PR value
value category of expr 'static_cast<int&>(x)' is : L value
value category of expr 'static_cast<int&&>(x)' is : X value
value category of expr '(r, *ptr)' is : L value
value category of expr '(r, &ptr)' is : PR value
value category of expr 'f1' is : L value
value category of expr 'f1()' is : PR value
value category of expr 'f2()' is : L value
value category of expr 'f3()' is : X value
value category of expr 'f4()' is : PR value
value category of expr 'f5()' is : PR value
value category of expr '*f5()' is : L value
value category of expr '**f5()' is : L value
*/
