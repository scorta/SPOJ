//Solution for http://www.spoj.com/problems/NAKANJ/
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAX = 12; //
const int SIZE = 8;
const int dx[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
const int dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };

struct Square {
	int row, column;
};

int t;
vector<vector<int>> board;
vector <vector<Square>> edge_to;
Square start, destination;
Square root = { -1, -1 };


void PrintStat() {
	for (int row = 0; row < MAX; ++row) {
		for (int column = 0; column < MAX; ++column) {
			printf("%d ", board[row][column]);
		}
		printf("\n");
	}
	printf("\n");
}


void StringToSquare(char s[], Square &square) {
	square.column = (s[0] - 'a') + 2;
	square.row = abs((s[1] - '1') - 7) + 2;
}

void Mark(Square square) {
	board[square.row][square.column] = 1;
}

void InitBoard() {
	board = vector<vector<int>>(MAX);
	for (int row = 0; row < MAX; ++row) {
		for (int column = 0; column < MAX; ++column) {
			board[row].push_back(1);
		}
	}

	edge_to = vector<vector<Square>>(MAX);
	for (int row = 0; row < MAX; ++row)
		for (int column = 0; column < MAX; ++column) {
			edge_to[row].push_back(root);
		}
}

void Init() {
	char a[2], b[2];
	scanf("%2s %2s", a, b);

	StringToSquare(a, start);
	StringToSquare(b, destination);

	for (int row = 2; row < SIZE + 2; ++row)
		for (int column = 2; column < SIZE + 2; ++column) {
			board[row][column] = 0;
		}

	for (int row = 2; row < SIZE; ++row)
		for (int column = 2; column < SIZE; ++column) {
			edge_to[row][column] = root;
		}
}

void Bfs(Square s, Square e) {
	if (s.row == e.row && s.column == e.column) return;

	int next_row, next_column;
	queue<Square> q;
	q.push(s);
	while (!q.empty()) {
		Square current = q.front();
		// printf("LIVE1\n");
		q.pop();
		// printf("LIVE2\n");
		Mark(current);
		// printf("LIVE3\n");
		for (int dir = 0; dir < 8; ++dir) {
			next_row = current.row + dx[dir];
			next_column = current.column + dy[dir];
			// printf("LIVE4\n");
			//printf("%d %d %d\n", next_row, next_column, board[next_row][next_column]);
			//printf("%d %d\n", current.row, current.column);
			// if(next_row < 0 || next_row > MAX - 1 || next_column < 0 || next_column > MAX - 1)
			// printf("FUCKKKKKK\n");

			if (board[next_row][next_column] == 0) {
				PrintStat();
				// printf("%d %d | %d %d\n", destination.row, destination.column, next_row, next_column);

				Square new_square = { next_row, next_column };
				// printf("LIVE5\n");
				q.push(new_square);
				queue<Square> temp_q = q;
				printf("\nCurrent Q\n");
				while (!temp_q.empty()){
					Square node = temp_q.front();
					temp_q.pop();
					printf("QUEUE %d %d\n", node.row, node.column);
				}
				// printf("LIVE6\n");
				edge_to[next_row][next_column] = current;
				// printf("LIVE7\n");

				if (e.row == next_row && e.column == next_column)
					return;
			}
		}
	}
	return;
}

int TrackBack() {
	Square sq = destination;
	int distant = 0;
	do {
		sq = edge_to[sq.row][sq.column];
		distant++;
	} while (sq.row != root.row && sq.column != root.column);

	return distant - 1;
}

int main() {
	scanf("%d", &t);
	InitBoard();
	for (int i = 0; i < t; ++i) {
		Init();
		Bfs(start, destination);
		printf("%d\n", TrackBack());
	}


	return 0;
}
