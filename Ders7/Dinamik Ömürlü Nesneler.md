# DİNAMİK ÖMÜRLÜ NESNELER
Hayata istenildiği zaman getirilip istenildiği zaman bitirilen nesneler dinamik ömürlü nesnelerdir. Zorunda değilsen dinamik ömürlü nesne oluşturma. Normalde otomatik ömürlü kullanırız, mecbur kalırsak dinamik ömürlü kullanırız. Neden?    
1 - Dinamik ömürlüler çok daha yüksek maliyetli.  
2 - Kullanımı otomatik ömürlüye göre daha zor, hata yapmak daha kolay.  
3 - Test-Debug-Değişiklik daha zor.  

C++'ta Dinamik ömürlü nesne oluşturan new operatörleri ve nesnenin hayatını sonlandıran delete operatörleri vardır.  
** new <tür>;**. 
  
```cpp 

new ifadesi = operator new() --> constructor
delete ifadesi = destructor --> operator delete()
//void * operator new(size_t n); C++ ın global functionu.
```
