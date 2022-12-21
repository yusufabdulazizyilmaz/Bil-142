# R VALUE REFERANS
Sağ taraf referansları C++11 standartlarıyla C++ diline eklenmiş en önemli araçlardan biridir. X bir tür olmak üzere, X&& türüne X‘e sağ taraf referansı denir.  
R value referanslar için [inceleyiniz](http://plepa.com/2016/10/04/sag-taraf-referanslari-1/).

Standart move işlevi (işlev şablonu) sol taraf değerini sağ taraf değerine dönüştürüyor. Yani x bir sol taraf değeri olsa da move işlevinin geri dönüş değeri bir sağ taraf değeridir.  

```cpp
  std::move(x)
  static_cast<X&&>(x)
```
