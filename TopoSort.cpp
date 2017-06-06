#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> adj;
std::vector<int> topo_order;
std::vector<int> source_vertex;
std::vector<int> degree;
int n, m;

void add_edge(int u, int v) {
	adj[u].push_back(v);	
}

bool is_fail(){
	if (topo_order.size() < n){
		return true;
	}

	return false;
}

void print_result(){
	if (is_fail()){
		printf("Sandro fails.");
	}
	else{
		for (int i = 0; i < topo_order.size() - 1; i++){
			printf("%d ", ++topo_order[i]);
		}
		printf("%d", ++topo_order[topo_order.size() - 1]);
	}
}

void init(){
	scanf("%d", &n);
	scanf("%d", &m);

	degree = std::vector<int>(n, 0);
	std::vector<std::vector<int>> temp_adj(n);
	adj = temp_adj;

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
}

bool descending_comp(const int &a, const int &b){
	return a > b;
}

void topo_sort(){
	while (source_vertex.size() > 0){
		int currentSourceNode = source_vertex.back();
		topo_order.push_back(currentSourceNode);
		source_vertex.pop_back();

		for (int i = adj[currentSourceNode].size() - 1; i >= 0; i--){
			if (--degree[adj[currentSourceNode][i]] == 0){

				std::vector<int>::iterator lower_bound = std::lower_bound(source_vertex.begin(), source_vertex.end(), adj[currentSourceNode][i], descending_comp);
				source_vertex.insert(lower_bound, adj[currentSourceNode][i]);
			}

			adj[currentSourceNode].pop_back();
		}
	}
}

int main() {
	init();
	topo_sort();
	print_result();
	return 0;
}
