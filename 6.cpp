#include <iostream>
#include <string>
#include <map>
#include <set>
#include <queue>

class Graph{
public:
	typedef std::string name;
	typedef std::vector<name> neighbors;

	bool breadthFirstSearch(name from, name target);
//private:
	std::map<name, neighbors> graph;
};

int main(){
	Graph g;
	g.graph["Alex"] = {"Mike", "John"};
	g.graph["Mike"] = {"Lola", "Carl"};
	g.graph["Lola"] = {"Carl"};
	std::cout<<g.breadthFirstSearch("Alex", "Carl")<<std::endl;
	return 0;
}

bool Graph::breadthFirstSearch(name from, name target){
	if(from == target) return true;

	std::set<name> checked = {from};
	std::queue<name> queue;
	
	for(name& i: graph[from]) queue.push(i); //add all neighbors of start Node
	
	while (!queue.empty()) {
		name checkNext = queue.front();
		if(checkNext == target) return true;
		else{
			checked.insert(checkNext);
			for(name& i: graph[checkNext]) { //add every unseen neighbor
				if(!checked.count(i)) queue.push(i);
			}
		}
		queue.pop();
	}
	return false;
}

