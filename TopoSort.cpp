#include <iostream>
#include <vector>

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
		//std::cout << "Sandro fails.";
		printf("Sandro fails.");
	}
	else{
		for (int i = 0; i < topo_order.size() - 1; i++){
			printf("%d ", ++topo_order[i]);
			//std::cout << ++topo_order[i]<< " ";
		}
		printf("%d", ++topo_order[topo_order.size() - 1]);
		//std::cout << ++topo_order[topo_order.size() - 1];
	}
}

void init(){
	//std::cin >> n >> m;
	scanf("%d", &n);
	scanf("%d", &m);

	for (int i = 0; i < n; i++){
		std::vector<int> sub;
		//sub.push_back(0);
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
}

int search(int node){
	int high = source_vertex.size() - 1, low = 0;
	while (high >= low)
	{
		int mid = (high - low) / 2 + low;
		if (mid == 0) {
			if (node > source_vertex[mid]){
				return mid;
			}
			else{
				return -1;
			}
		}
		if (node >= source_vertex[mid] && node < source_vertex[mid - 1]){
			return mid;
		}
		else
			if (node > source_vertex[mid]) high = mid - 1;
			else low = mid + 1;
	}
	return -1;
}

void topo_sort(){
	while (source_vertex.size() > 0){
		int currentSourceNode = source_vertex[source_vertex.size() - 1];
		topo_order.push_back(currentSourceNode);
		source_vertex.pop_back();

		for (int i = adj[currentSourceNode].size() - 1; i >= 0; i--){
			if (--degree[adj[currentSourceNode][i]] == 0){

				int i_source_vertex = search(adj[currentSourceNode][i]);
				if (i_source_vertex >= 0){
					source_vertex.insert(source_vertex.begin() + i_source_vertex, adj[currentSourceNode][i]);
				}
				else {
					source_vertex.push_back(adj[currentSourceNode][i]);
				}
				//for (int i_source_vertex = 0; i_source_vertex < source_vertex.size(); i_source_vertex++){ //Binary search is better?
				//	if (source_vertex[i_source_vertex] < adj[currentSourceNode][i]){
				//		source_vertex.insert(source_vertex.begin() + i_source_vertex, adj[currentSourceNode][i]);
				//		need_insertion = true;
				//		break;
				//	}
				//}

				/*if (!need_insertion){
					source_vertex.push_back(adj[currentSourceNode][i]);
				}*/
			}

			adj[currentSourceNode].pop_back();
		}
	}
}

int main() {
	init();
	topo_sort();
	print_result();
}
