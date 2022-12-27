# Numaralandırma Sabitleri (ENUM)




```cpp
//C++20 using enum <enum_name>
enum class Days{Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

void func()
{
	using enum Days;

	auto d1 = Sunday;
	auto d2 = Monday; 
	auto d3 = Friday; 
	//...
}
```
