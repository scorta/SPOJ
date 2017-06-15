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
map<int, int> answer;
int number_of_slick;

void print_result(){
	printf("%d\n", number_of_slick);
	map<int, int>::iterator last_it = --answer.end();
	for (map<int, int>::iterator it = answer.begin(); it != last_it; it++){
		printf("%d %d\n", *it);
	}

	printf("%d %d", *last_it);
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
	number_of_slick++;
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
		number_of_slick = 0;
		scanf("%d%d", &n, &m);

		if (n == 0 || m == 0) break;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &grid[i][j]);
			}
		}

		Solve(n, m);
		print_result();
	}

	return 0;
}
