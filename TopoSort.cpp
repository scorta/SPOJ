#include <iostream>
#include <vector>
#include <deque>

const int MAX_VERTEX = 10000;
bool seen[MAX_VERTEX];

std::vector<std::vector<int>> adj;
std::vector<int> topo_order;
std::vector<int> source_vertex;
std::vector<int> degree;


void add_edge(int u, int v) {
	adj[u].push_back(v);	
}

bool isFail(){
	/*for(int i = 0; i < adj.size() - 1; i++){
		if (adj[i].size() > 0){
			return true;
		}
	}*/

	return false;
}

void print_result(){
	if (isFail()){
		std::cout << "Sandro fails.";
	}
	else{
		for (int i = 0; i < topo_order.size(); i++){
			std::cout << ++topo_order[i];
		}
	}
}

int main() {
	int n, m;
	std::cin >> n >> m;

	for (int i = 0; i < n; i++){
		std::vector<int> sub;
		sub.push_back(0);
		adj.push_back(sub);

		degree.push_back(0);
		
	}

	for (int index = m - 1; index >= 0; index--){
		int vertex1, vertex2;
		std::cin >> vertex1 >> vertex2;
		add_edge(vertex1 - 1, vertex2 - 1);
		degree.at(vertex2 - 1)++;
	}

	for (int i = n - 1; i >= 0; i--){
		if (degree[i] == 0){
			source_vertex.push_back(i);
		}
	}

	while (source_vertex.size() > 0){
		int currentSourceNode = source_vertex[source_vertex.size() - 1];
		topo_order.push_back(currentSourceNode);
		source_vertex.pop_back();

		for (int i = adj[currentSourceNode].size() - 1; i >= 0; i--){
			if (--degree[adj[currentSourceNode][i]] == 0){
				source_vertex.push_back(adj[currentSourceNode][i]);
			}

			adj[currentSourceNode].pop_back();
		}
	}

	print_result();

	int wait_key;
	std::cin >> wait_key;
	return 0;
}
