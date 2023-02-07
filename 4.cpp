#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdint.h>
#include <vector>

uint32_t gcd(int64_t a, int64_t b); //return the greatest common divisor or uint_max
int32_t sum(int32_t* array, int32_t size, int32_t res=0); //return the sum of the elements in array or zero if empty
int32_t cntElems(int32_t* array, int32_t size, int32_t res=0); //return the number of elements in array or zero if empty
int32_t findMax(int32_t* array, int32_t size, int32_t res=0); //return the maximum element in array or zero if empty
int32_t* binarySearch(int32_t* first, int32_t* last, int32_t target); //return the pointer to the target if present or nullptr

template <typename T> 
std::vector<T> qsort(	std::vector<T>& source, 
			std::vector<T> smaller = {}, 
			std::vector<T> bigger = {}); //return the sorted vector

int main(){
	//*****************Greatest common divisor***************
	std::cout<<"gcd(5,1) is "<<gcd(5,1)<<std::endl;			//1
	std::cout<<"gcd(5,0) is "<<gcd(5,0)<<std::endl;			//5
	std::cout<<"gcd(0,5) is "<<gcd(0,5)<<std::endl;			//5
	std::cout<<"gcd(10,5) is "<<gcd(10,5)<<std::endl;		//5
	std::cout<<"gcd(5,5) is "<<gcd(5,5)<<std::endl;			//5
	std::cout<<"gcd(0,0) is "<<gcd(0, 0)<<std::endl;		//UINT32_MAX
	std::cout<<"gcd(1680,640) is "<<gcd(1680, 640)<<std::endl;	//80
	std::cout<<"\n";

	//*************************Divide&conquer********************
	int32_t SIZE = 10000;
	int32_t arr[SIZE];
	for(int i = 0; i<SIZE; i++) arr[i] = i;
	std::cout<<"sum of array 0,1 ... "<<SIZE<<" is "<<sum(arr, SIZE)<<std::endl;
	std::cout<<"number of elements in array size of "<<SIZE<<" is "<<cntElems(arr, SIZE)<<std::endl;
	std::cout<<"max in array 0,1 ... "<<SIZE<<" is "<<findMax(arr, SIZE)<<std::endl;

	int32_t target = 666;
	std::cout<<"in array 0,1 ... "<<SIZE<<" the number "<<target<<" "<<((binarySearch(arr, arr+SIZE-1, target) != nullptr)? "found":"not found")<<std::endl;
	std::cout<<"\n";

	//***************************Quick sort**********************
	std::vector<uint32_t> vec;
	for (int i = SIZE; i>0; i--) vec.push_back(i);
	qsort<uint32_t>(vec);
	for (int i = 0; i<SIZE; i++) std::cout<<vec[i]<<" ";
	std::cout<<std::endl;
	return 0;
}

uint32_t gcd(int64_t a, int64_t b){
	if (a == 0) return (b != 0)? b: -1; //base case #1
	if (b == 0) return (a != 0)? a: -1; //base case #2

	//recursive case
	if(a >= b) return gcd(b, a%b); 
	else return gcd(a, b%a);
}
int32_t sum(int32_t* array, int32_t size, int32_t res){
	if(size <= 0 || array == nullptr) return res;	//base case				
	return sum(array+1, size-1, res+array[0]);	//tail recursive case
}
int32_t cntElems(int32_t* array, int32_t size, int32_t res){
	if(size <= 0 || array == nullptr) return res; //base case
	return cntElems(array+1, size-1, res+1); //tail recursive case
}
int32_t findMax(int32_t* array, int32_t size, int32_t res){
	if(size <= 0 || array == nullptr) return res; //base case

	int32_t first = array[0];
	res = (first > res)? first:res;
	return findMax(array+1, size-1, res);
}
int32_t* binarySearch(int32_t* first, int32_t* last, int32_t target){
	if(first == nullptr || last == nullptr) return nullptr;
	if(last-first == 1) return (*first == target)? first: nullptr; 	//base case #1

	int32_t* mid = first + (last-first)/2;
	if(*mid == target)	return mid; 					//base case #2
	if(*mid < target)	return binarySearch(mid+1, last, target); 	//tail recursive case
	if(*mid > target)	return binarySearch(first, mid, target);	//tail recursive cas
}
template <typename T>
std::vector<T> qsort(std::vector<T>& source, std::vector<T> smaller, std::vector<T> bigger){
	if(source.size() < 2) return source;
	else if(source.size() == 2){
		if(source[0] <= source[1]) return source;
		else{
			auto tmp = source[0];
			source[0] = source[1];
			source[1] = tmp;
		}
	}
	else{
		auto pivot = source[0];
		for (int i = 1; i<source.size(); i++) {
			if(source[i] < pivot) 	smaller.push_back(source[i]);
			else		bigger.push_back(source[i]);
		}
		smaller = qsort(smaller);
		bigger = qsort(bigger);
		smaller.push_back(pivot);
		smaller.insert(smaller.end(), bigger.begin(), bigger.end());
		source = smaller;
		return source;
	}
}
