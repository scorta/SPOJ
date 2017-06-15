#include <algorithm>
#include <cstdio>
#include <queue>
#include <map>

using namespace std;

const int NMAX = 255;

typedef pair<int, int> pt;

int n, m;

const int dx[] = { 1, -1, 0, 0 };
const int dy[] = { 0, 0, 1, -1 };

int grid[NMAX][NMAX];
//map<int, int> answer;
map<int, int> answer;

void print_matrix(){
	printf("\n");
	printf("\n");
	for (int iN = 0; iN < n; iN++){
		for (int iM = 0; iM < m; iM++){
			printf("%*d", 2, grid[iN][iM]);
		}
		printf("\n");
	}
}

void print_result(){
	for (map<int, int>::iterator it = answer.begin(); it != answer.end(); it++){
		printf("%d %d\n", *it);
	}
}

void Unmark(pt p) {
	grid[p.first][p.second] = 2;
}

void Bfs(pt start) {
	int size = 0;
	queue<pt> q;
	q.push(start);
	Unmark(start);

	while (!q.empty()) {
		pt v = q.front();
		q.pop();

		for (int dir = 0; dir < 4; ++dir) {
			int next_x = v.first + dx[dir];
			int next_y = v.second + dy[dir];

			// check that we are inside grid

			// check that new square is not visited

			// unmark and push to the queue
			if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < m && grid[next_x][next_y] == 1){
				pt newPoint;
				newPoint.first = next_x;
				newPoint.second = next_y;

				Unmark(newPoint);
				q.push(newPoint);
				size++;
			}
			
		}
	}
	answer[++size]++;
	//printf("size %d", size);
}

void Solve(int n, int m) {
	// goes through the grid and starts Bfs in some places
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			if (grid[i][j] == 1){
				pt newPoint;
				newPoint.first = i;
				newPoint.second = j;
				Bfs(newPoint);
			}
		}
}

int main() {	
	while (true) {
		scanf("%d%d", &n, &m);

		if (n == 0 || m == 0) break;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &grid[i][j]);
			}
		}

		Solve(n, m);
		printf("\n\n");
		print_result();
	}

	return 0;
}
