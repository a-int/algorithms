#include "sort.hpp"
#include <cstdint>
#include <iostream>
uint32_t findSmallest(int32_t* array, uint32_t size){
	int32_t min = INT32_MAX;
	uint32_t index = -1;
	for(int i = 0; i<size; i++) {
		if(array[i] <= min){
			min = array[i];
			index = i;
		}
	}
	return index;
}

int32_t* selectingSort(int32_t* source, uint32_t size){
	if(size<1) return nullptr;
	if(source != nullptr){
		while(size--){
			uint32_t indexSmallest = findSmallest(source, size+1);
			
			//swap smallest and the last
			int32_t tmp = source[indexSmallest];
			source[indexSmallest] = source[size];
			source[size] = tmp;
		}
	}
	return source;
}