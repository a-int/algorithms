#include <functional>
#include <iostream>
#include <string>

template <typename T>
void bubbleSort(T* arr, uint32_t sz, std::function<bool(T&, T&)> compare = std::less<T>());

int main(){
	const uint32_t SIZE = 10;
	uint32_t arr[10];
	//fill-up the array
	for(uint32_t i = 0; i < SIZE; i++) arr[i] = SIZE-i;
	//sort array
	bubbleSort<uint32_t>(arr, SIZE, [&](int x, int y)->bool{return x>y;});
	//print the array
	for(uint32_t i = 0; i < SIZE; i++) std::cout<<arr[i]<<" ";
	std::cout<<std::endl;

	std::string strings[3] = {"A", "B", "C"};
	bubbleSort<std::string>(strings, 3, [&](std::string s1, std::string s2)->bool{return s1>s2;});
	for(uint32_t i = 0; i < SIZE; i++) std::cout<<strings[i]<<" ";
	std::cout<<std::endl;
	return 0;
}

template <typename T>
void bubbleSort(T* arr, uint32_t sz, std::function<bool(T&, T&)> compare){
	for(uint32_t i = 0; i < sz; i++){
		for(uint32_t j = 1; j < sz-i; j++){
			if(compare(arr[j], arr[j-1]))
				std::swap(arr[j], arr[j-1]);
		}		
	}
}