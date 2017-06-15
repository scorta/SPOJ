#include <vector>
#include <algorithm>
#include <cstdio>;

const int NMAX = 10000;
std::vector<std::vector<int>> adj;
std::vector<int> topo_order;
std::vector<int> degree;

int n, m;
int source_vertex_size;
int source_vertex[NMAX];

int Left(int x) {
	return x * 2;
}

int Right(int x) {
	return x * 2 + 1;
}

int Parent(int x) {
	return x / 2;
}

void Add(int x) {
	int pos = source_vertex_size + 1;
	++source_vertex_size;
	source_vertex[pos] = x;
	while (pos > 1) {
		if (source_vertex[Parent(pos)] > source_vertex[pos]) {
			std::swap(source_vertex[Parent(pos)], source_vertex[pos]);
			pos = Parent(pos);
		}
		else {
			break;
		}
	}
}

int Pop() {
	if (source_vertex_size < 1) {
		return -1;
	}
	int result = source_vertex[1];
	source_vertex[1] = source_vertex[source_vertex_size];
	--source_vertex_size;
	int pos = 1;
	while (true) {
		int smallestPos = pos;
		if (Left(pos) <= source_vertex_size && source_vertex[Left(pos)] < source_vertex[smallestPos]) {
			smallestPos = Left(pos);
		}
		if (Right(pos) <= source_vertex_size && source_vertex[Right(pos)] < source_vertex[smallestPos]) {
			smallestPos = Right(pos);
		}
		if (smallestPos != pos) {
			std::swap(source_vertex[smallestPos], source_vertex[pos]);
			std::swap(smallestPos, pos);
		}
		else {
			break;
		}
	}
	return result;
}

int Top() {
	if (source_vertex_size > 0) {
		return source_vertex[1];
	}
	return -1;
}

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
		scanf("%d", &vertex1);
		scanf("%d", &vertex2);
		add_edge(vertex1 - 1, vertex2 - 1);
		degree.at(vertex2 - 1)++;
	}

	int index = -1;
	for (int i = n - 1; i >= 0; i--){
		if (degree[i] == 0){
			Add(i);
		}
	}

}

bool descending_comp(const int &a, const int &b){
	return a > b;
}

void topo_sort(){
	while (source_vertex_size > 0){
		int currentSourceNode = Top();
		topo_order.push_back(currentSourceNode);
		Pop();

		for (int i = adj[currentSourceNode].size() - 1; i >= 0; i--){
			if (--degree[adj[currentSourceNode][i]] == 0){
				Add(adj[currentSourceNode][i]);
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
