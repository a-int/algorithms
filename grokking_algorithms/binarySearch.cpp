#include "binarySearch.hpp"

uint32_t binarySearch(uint32_t* buffer, uint32_t size, uint32_t target){
	uint32_t begin = 0, end = size;
	uint32_t index = 0;
	while (begin < end) {
		index = begin + (end-begin)/2;
		uint32_t mid = buffer[index];
		if(mid == target) return index;
		else if (mid > target) end = index-1;
		else if (mid < target) begin = index+1;
	}
	//if(buffer[index] == target) return index;
	return -1;
}

#ifdef DEBUG

	//FIXME add tests
	//array with target
	//array without target
	//empty
	//not sorted array
	//array with wrong size
	//array where multiply targets fits

#endif