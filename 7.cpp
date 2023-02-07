#include <iostream>
#include <map>
#include <set>
class Node{
public:
	typedef uint32_t	weight_t;
	typedef Node* 		key;
	typedef weight_t	value;
	typedef std::map<key, value>::iterator iterator;
	typedef std::map<key, value>::const_iterator const_iterator;

	Node(std::string nm) : name(nm) {}

	iterator begin() {return neighbors.begin();}
	iterator end() {return neighbors.end();}
	const_iterator begin() const {return neighbors.begin();}
	const_iterator end() const {return neighbors.end();}

	void addNeigbor(Node& node, weight_t wt);
	weight_t getWeight(Node& node);
	std::string getName();
	void clearNeighbors();
//private:
	key getKey();
	value getValue();

	std::string name;
	std::map<key, value> neighbors;
};

Node* findSmallest(std::map<Node*, uint32_t>& costs, std::set<Node*>& checked);
uint32_t dijkstra(Node& start,Node& finish);

int main(){
	//create nodes for 7.1
	Node start("Start");
	Node x1("A");
	Node x2("B");
	Node x3("C");
	Node x4("D");
	Node finish("Finish");
	//make a weighted graphs for 7.1
	start.addNeigbor(x1, 5);
	start.addNeigbor(x2, 2);
	x1.addNeigbor(x3, 4);
	x1.addNeigbor(x4, 2);
	x2.addNeigbor(x1, 8);
	x2.addNeigbor(x4, 7);
	x3.addNeigbor(x4, 6);
	x3.addNeigbor(finish, 3);
	x4.addNeigbor(finish, 1);
	//get the shortest way for 7.1
	std::cout<<dijkstra(start, finish)<<std::endl; //8
	//clear neighbors
	start.clearNeighbors(); 
	x1.clearNeighbors(); 
	x2.clearNeighbors(); 
	x3.clearNeighbors(); 
	x4.clearNeighbors();
	//make a weighted graphs for 7.2
	start.addNeigbor(x1, 10);
	x1.addNeigbor(x2, 20);
	x2.addNeigbor(x3, 1);
	x2.addNeigbor(finish, 30);
	x3.addNeigbor(x1, 1);
	//get the shortest way for 7.2
	std::cout<<dijkstra(start, finish)<<std::endl; //60
	//7.3 has negative edge, dijkstra algorithm doesnt work
	return 0;
}

Node::key Node::getKey(){
	return this;
}
void Node::addNeigbor(Node& node, weight_t wt){
	if(!neighbors.count(node.getKey())) //add neighbor if not present yet
		neighbors[node.getKey()] = wt;
}
Node::weight_t Node::getWeight(Node& node){ return this->neighbors[&node]; }
std::string Node::getName(){ return name; }
void Node::clearNeighbors(){neighbors.clear();}
Node* findSmallest(std::map<Node*, uint32_t>& costs, std::set<Node*>& checked){
	uint32_t minWeight = -1;
	Node* minNode = nullptr;
	for(auto& i: costs){
		if((i.second < minWeight) && (!checked.count(i.first))){
			minWeight = i.second;
			minNode = i.first;
		}
	}
	return minNode;
}
uint32_t dijkstra(Node& start, Node& finish){
	std::map<Node*, Node*> 		parent;
	std::map<Node*, uint32_t> 	costs{{&finish, -1}};
	std::set<Node*> 			checked;
	//process the satrt node
	for(auto i : start){
		costs[i.first] = i.second;
		parent[i.first] = &start;
	}
	checked.insert(&start);
	
	Node* node = findSmallest(costs, checked);
	while(node){
		for(auto pair: (*node)){//check every neighbor of node
			Node& neighbor = *pair.first;
			uint32_t costFromNode = costs[node] + node->getWeight(neighbor);
			if((!costs.count(&neighbor)) || (costFromNode < costs[&neighbor])){ //update if not present or new cost is less
				costs[&neighbor] = costFromNode;
				parent[&neighbor] = node;
			}
		}
		checked.insert(node);
		node = findSmallest(costs, checked);
	}
	return costs[&finish];
}










