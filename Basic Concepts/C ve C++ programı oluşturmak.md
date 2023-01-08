C ve C++ dilinde yazılan bir programın çalıştırılabilir hale getirilebilmesi için, çoğunlukla aşağıdaki
süreçlerden geçilir:

1- Kaynak dosyanın oluşturulması:

Kaynak dosya, metin düzenleyici bir programda (text editörü) yazılır. Kaynak dosya bir
metin dosyasıdır. Özellikle büyük programlar, modül ismi verilen ayrı ayrı parçalar halinde yazılır. Bu
modüllerden bazılarının amacı, diğer modüllere hizmet vermektir. C ve C++ dillerinde,
genel hizmet verecek kodlar (server codes), genel olarak iki ayrı dosya halinde yazılır.
Fonksiyon tanımlamaları, global değişken tanımlamaları uzantısı .c ya da .cpp olan dosyada yer alır. Bu
dosyaya, kodlama dosyası (implementation file) denir. Hizmet alacak kodları (client codes) ilgilendiren bildirimler ise 
bir başka dosyada tutulur. Bu dosyaya, başlık dosyası (header file) denir ve uzantısı .h şeklindedir. 

2- Kaynak dosyanın önişlemci (preprocessor) program tarafından düzenlenmesi:

C++ derleyicileri iki ayrı modülden oluşur: Önişlemci Modülü ve Derleme Modülü. Önişlemci modülü, kaynak dosyada çeşitli metinsel düzenlemeler, değişiklikler yapar. C++ programlama dilinde # 
ile başlayan bütün satırlar, önişlemci programa verilen komutlardır. Kendisine verilen komutları yerine getirdikten sonra, #
ile başlayan satırları kaynak dosyadan siler. Derleme modülüne girecek programda # ile başlayan satırlar artık yer almaz.
```cpp
#include <dosya ismi>  
#include "dosya ismi"    //(copy – paste) işlemidir.
```  
```cpp
#define SIZE 100   //(find - replace) işlemidir.
```

3- Önişlemci çıktısının derleyici program (compiler) tarafından derlenmesi:

Bir programlama dilinde yazılmış programı başka bir programlama diline çeviren
programlara "çevirici" (translator) denir. Dönüştürülmek istenen programın yazıldığı dile
"kaynak dil" (source language), dönüşümün yapıldığı dile ise "hedef dil" (target language)
denir. Hedef dil, makine dili ya da simgesel makine dili ise, böyle çevirici programlara
"derleyici" (compiler) denir.

Derleyici program önişlemci çıktısını alır, çeviri işleminde eğer başarılı olursa bu kaynak
dosyadan bir "amaç dosya" (object file) üretir. Unix/Linux sistemlerinde oluşturulan amaç dosyaların uzantısı 
".o" dur. DOS ve Windows sistemlerinde amaç dosyalar ".obj" uzantısını alır.
Derleyici programın derleme işlemini yapma sürecine "derleme zamanı" (compile time)
denir. Derleme işlemi başarısızlık ile de sonuçlanabilir. gcc, clang, MSVC önemli compilerlardır.

4- Amaç dosyalarının bağlayıcı (linker) program ile birleştirilmesi:

Daha önce elde edilmiş amaç dosyalar "bağlayıcı" (linker) program tarafından
birleştirilerek çalıştırılabilir bir dosya elde edilir. UNIX sistemlerinde genellikle
çalıştırılabilir dosyanın uzantısı olmaz. Windows sistemlerinde çalıştırılabilir dosyaların
uzantısı ".exe" olarak seçilir.
