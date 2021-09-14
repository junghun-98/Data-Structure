#pragma once

template <typename T>
class bag {
public:
	bag();
	bag(const int init_capacity); //initialize bag
	bag(const bag& source); //copy constructor.
	~bag() { delete[] data; }

	void reserve(int new_size); //Modify the memory size.
	
	void insert(T new_data);
	void remove(T data);
	void printdata();

	size_t size() { return used; }

	void operator =(const bag& source);
	void operator +=(const bag& addend);
private:
	T* data;		//The address of the memory where the data is stored.
	size_t capacity;//The size of memoty.
	size_t used;	//The number of data.
};