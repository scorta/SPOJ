#include <iostream>
#include <vector>

const int MAX_VERTEX = 10000;
bool seen[MAX_VERTEX];

std::vector<std::vector<int>> adj(MAX_VERTEX);
std::vector<int> topo_order;

void dfs(int u) {
	seen[u] = true;
	for (int v : adj[u]) {
		if (!seen[v]) {
			dfs(v);
		}
	}
	
	topo_order.push_back(u);
}

void add_edge(int u, int v) {
	adj[u].push_back(v);	
}

void topo_sort(int no_vertex) {
	for (int v = 0; v < no_vertex; ++v) {
		if (!seen[v]) {
			dfs(v);
		}
	}
	
	for (int index = no_vertex - 1; index > -1; index--) {
		std::cout << topo_order.at(index) + 1 << " ";
	}
}

int main() {
	int n, m;
	std::cin >> n >> m;

	for (int index = 0; index < m; index++){
		int vertex1, vertex2;
		std::cin >> vertex1 >> vertex2;
		add_edge(vertex1 - 1, vertex2 - 1);
	}

	topo_sort(n);

	int wait_key;
	std::cin >> wait_key;
	return 0;
}
