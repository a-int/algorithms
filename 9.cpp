#include <iostream>
#include <functional>
#include <vector>

template <typename weight_t, typename cost_t>
cost_t knapsack(std::vector<std::pair<weight_t,cost_t>> items, weight_t maxWeight, weight_t step = 1.0f);

uint32_t longestCommonSubstring(const char* src1, const char* src2, uint32_t cnt = 0);

int main(){
	std::vector<std::pair<uint32_t, uint32_t>> items1{{4,3000},{3,2000},{1,1500}, {1,2000}};
	std::cout<<knapsack<uint32_t, uint32_t>(items1, 4)<<std::endl;

	//9.1 what happens if you add mp3 1lb 1000$. Should you steal it?
	items1.push_back({1, 1000});
	std::cout<<knapsack<uint32_t, uint32_t>(items1, 4)<<std::endl; //became 4500. The answer: yes

	//Vacation in London
	std::vector<std::pair<double, uint32_t>> items2{{0.5,7},{0.5, 6},{1, 9}, {2, 9}, {0.5, 8}};
	std::cout<<knapsack<double, uint32_t>(items2, 2, 0.5)<<std::endl;

	//9.2 camping
	std::vector<std::pair<uint32_t, uint32_t>> items3{{3, 10}, {1, 3}, {2, 9}, {2, 5}, {1, 6}};
	std::cout<<knapsack<uint32_t, uint32_t>(items3, 6)<<std::endl;	

	std::cout<<"longest common substring between blue and clues is "<<longestCommonSubstring("blue", "clues")<<std::endl;//3
	std::cout<<"longest common substring between blue and clues is "<<longestCommonSubstring(nullptr,nullptr)<<std::endl;//0
	return 0;
}

template <typename weight_t, typename cost_t>
cost_t knapsack(std::vector<std::pair<weight_t,cost_t>> items, weight_t maxWeight, weight_t step){
	std::vector<cost_t> globalBestCost(maxWeight/step+1);

	for(auto& i: items){
		weight_t weight = i.first;
		cost_t cost = i.second;

		std::vector<cost_t> localBestCost(globalBestCost);
		for(int i = weight/step; i <= localBestCost.size(); i++){
			if(cost > localBestCost[i]){
				localBestCost[i] = cost;
			}
			if((cost + globalBestCost[(i-weight/step)]) > localBestCost[i])
				localBestCost[i] = (cost + globalBestCost[(i-weight/step)]);
		}
		globalBestCost.swap(localBestCost);
	}
	return globalBestCost.back();
}

uint32_t longestCommonSubstring(const char* src1, const char* src2, uint32_t cnt){
	if(!(src1&&src2)) return cnt;
	if((*src1 == '\0') || (*src2 == '\0')) return cnt; //base case
	return longestCommonSubstring(src1+1, src2+1, (((*src1)==(*src2))? ++cnt : cnt)); //tail-resucrive case
}