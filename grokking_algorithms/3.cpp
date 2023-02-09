#include <iostream>
#include <list>
#include <streambuf>

uint64_t fibonachi(int64_t x);
uint64_t factorial(int64_t x);

uint64_t factorial_tail_rec(int64_t n, int64_t res = 1);
uint64_t fibonachi_tail_rec(int64_t n, int64_t prev1=0, int64_t prev2=1);

template <typename T>
class stack{
public:
	void push(const T& val) {buffer_.push_back(val);}
	void pop() {buffer_.pop_back();}
	T& back(){return buffer_.back();}
	T& top(){return buffer_.front();}
private:
	std::list<T> buffer_;
};

int main(){
	//*******BASE&RECURSIVE CASE******************
	std::cout<<"fibonachi(3) is "<<fibonachi(3)<<std::endl;	//2
	std::cout<<"fibonachi(10) is "<<fibonachi(10)<<std::endl;//55
	std::cout<<"fibonachi(19) is "<<fibonachi(19)<<std::endl;//4181

	std::cout<<"factorial(-10) is "<<factorial(-10)<<std::endl;	//0
	std::cout<<"factorial(1) is "<<factorial(1)<<std::endl;		//1
	std::cout<<"factorial(5) is "<<factorial(5)<<std::endl;		//120	
	//*********STACK*******************************
	const int SIZE = 10;
	stack<int> s;
	for(int i = 0; i<SIZE; i++) s.push(i);
	std::cout<<"back is "<<s.back()<<std::endl;	
	s.pop();
	s.pop();
	s.pop();
	std::cout<<"after 3 pop() back is "<<s.back()<<std::endl;
	//**********************tail recursion***************************
	std::cout<<"fibonachi_tail_rec(100) is "<<fibonachi_tail_rec(100)<<std::endl; //infinite for non tail recursion
	std::cout<<"factorial_tail_rec(20) is "<<factorial_tail_rec(20)<<std::endl;
	return 0;
}

uint64_t fibonachi(int64_t x){
	if(x < 0) return 0; //base case #1
	if(x < 2) return x; // base case #2
	else return fibonachi(x-1)+fibonachi(x-2); //recursive case

	//may be optimized by compiler to become tail recursion(one loop)
	/*
	
	int x1 = 0; x2 = 1;
	for(int i = 1; i <= x; i++){
		if(x1 >= x2) 
	}
	return sum;
	*/
}

uint64_t factorial(int64_t x){
	if(x <= 0) return 0;			//base case #1
	else if(x == 1) return 1;		//base case #2
	else return x*factorial(x-1); 	//recursive case #1
}

uint64_t factorial_tail_rec(int64_t n, int64_t res){
	if (n < 0) 		return 0;	//base case #1
	else if(n == 1) return res;	//base case #1
	else return factorial_tail_rec(n-1, res*n);	//tail recursive case
}

uint64_t fibonachi_tail_rec(int64_t n, int64_t prev1, int64_t prev2){
	if(n <= 0) return 0;								//base case #1
	else if(n==1) return prev2;							//base case #2
	else return fibonachi_tail_rec(n-1, prev2, prev2+prev1);	//tail recursive case
}