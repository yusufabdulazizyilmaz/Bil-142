# Numaralandırma Sabitleri (ENUM)

Enum vs Scoped Enum (Enum Class)
1- Numaralandırma türlerinde (Enum) tanıtılan numaralandırma sabitlerinin kapsamları (scope) ilgili türün kapsamı iken Numaralandırma sınıfı(Enum Class) türlerinin kendi kapsamları var ve tanıtılan numaralandırma sabitleri numaralandırma sınıfının kendi kapsamında yer alıyor.

```cpp
enum Color { white, red, magenta, black};
enum TrafficLight { red, yellow, green};


```

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
