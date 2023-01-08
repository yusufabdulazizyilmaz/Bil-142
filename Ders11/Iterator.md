# ITERATOR
Pointer like bir interface e sahip dolayısı ile bunların sınıf türünden nesneler olması durumunda yine pointer gibi 
kullanılmasını sağlayan operator overloading mekanizması. Bir iteratörün hangi işlemlerde kullanılabileceğini belirleyen iteratörün kategorisi.
Bu kategorilere isimler verilmiş. Her iteratörün bir kategorisi olmak zorunda.
* Output iterator
* Input iterator
* Forward iterator
* Bidirectional iterator
* Random access iterator
* Contiguous iterator (C++17)

![Screenshot 2023-01-08 at 10 36 55](https://user-images.githubusercontent.com/92329809/211185533-cd6014c3-c7ea-45cf-9a05-969b91657192.png)

Bütün iteratorlerin iterator_category isimli bir nested type ı var. iterator kategorisinin ne olduğunu anlamanın yolu, iterator sınıfının iterator category
nested type ının ne olduğuna bakmak. **vector<int>::iterator::iterator_category** 
  
| 		ITERATOR KATEGORİLERİ		  |						OPERASYONLAR						      |													  |
|-------------------------------------------------|-------------------------------------------------------|-------------------------------|
|						      |	Copy constructible				  |		    		      |	
|	 OUTPUT ITERATOR	  		  |	++it	it++	=				  |	   	 ostream_iterator    		      |
|						  |	*it		it->  (sol taraf değeri)	  |  ostreambuf_iterator						      |
|						  |							  |						      |
|						  |	Copy constructible			  	  |						      |
|						  |	++it	it++	=		  	  	  |		 istream_iterator     		      |
|	  INPUT ITERATOR	  		  |	*it		it->  (sağ taraf değeri)	  |	istreambuf_iterator	      		      |
|						  |	it1 == it2		it1 != it2		  |						      |
|						  |							  |						      |
|						  |	Copy constructible - Default Constructible	  |		 				      |
|						  |	++it	it++	=				  |	forward_list		    		      |
|	FORWARD ITERATOR	  		  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	unordered_set		unordered_multiset    |
|						  |	it1 == it2		it1 != it2		  |	unordered_map		unordered_multimap    |
|						  |							  |						      |
|						  |	Copy constructible - Default Constructible	  |						      |
|		BIDIRECTIONAL				  |	++it	it++	--it	it--		=	  |	list					      |
|	 	ITERATOR	 		  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	set		multiset		      |
|	    		  		  |	it1 == it2		it1 != it2		  |	map		multimap		      |
|						  |							  |						      |
|						  |							  |						      |
|						  |	Copy constructible - Default Constructible        |						      |
|						  |	++it	it++		--it	it--	=	  |	vector			      		      |
|						  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	deque			      		      |
|	  RANDOM ACCESS		  		  |	it1 == it2		it1 != it2		  |	array			      		      |
|	    ITERATOR		  		  |	it + n		n + it		it - n		  |	string			      		      |
|	(Pointer Interface )  			  |	it+=n		it-=n				  |	C array			      		      |
|						  |	it1 - it2					  |						      |
|						  |	it[n]						  |						      |
|						  |	it1 < it2   it1 <= it2   it1 > it2   it1 >= it2   |						      |
--------------------------------------------------------------------------------------------------------------------------------------------------------------
```cpp

```

