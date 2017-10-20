//Solution for http://www.spoj.com/problems/NAKANJ/
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int SIZE = 8; // Size of the chess board
const int N_BORDERS = 2; //Number of borders - help to prevent knight moving out of the board
const int MAX = SIZE + 2 * N_BORDERS; //Max size of the board; equal to: SIZE + 2 * N_BORDERS
const int dx[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
const int dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };

struct Square {
	int row, column;
	bool operator == (const Square &b) const {if (this->row == b.row && this->column == b.column) return true; return false;}
};

int t;
vector<vector<int>> board;
vector <vector<Square>> edge_to;
Square start, destination;
constexpr Square root = { -1, -1 };

void StringToSquare(char *const s, Square &square) {
	square.column = (s[0] - 'a') + N_BORDERS;
	square.row = abs((s[1] - '1') - 7) + N_BORDERS;
}

void Mark(const Square &square, const int &mark) {
	board[square.row][square.column] = mark; //0 means unvisited
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

	for (int row = N_BORDERS; row < SIZE + N_BORDERS; ++row)
		for (int column = N_BORDERS; column < SIZE + N_BORDERS; ++column) {
			board[row][column] = 0;
		}

	for (int row = N_BORDERS; row < SIZE + N_BORDERS; ++row)
		for (int column = N_BORDERS; column < SIZE + N_BORDERS; ++column) {
			edge_to[row][column] = root;
		}
}

void Bfs(Square s, Square e) {
	if (s == e) return;

	int next_row, next_column;
	int distant = 1;
	queue<Square> q;
	q.push(s);
	q.push(root);
	Mark(s, distant);
	while (!q.empty()) {
		Square current = q.front();
		q.pop();
		if (current == root) {
			if (current == q.front()) 				return;
			distant++;
			q.push(root);
		} else {
			for (int dir = 0; dir < 8; ++dir) {
				next_row = current.row + dx[dir];
				next_column = current.column + dy[dir];

				if (board[next_row][next_column] == 0) {
					Square new_square = { next_row, next_column };
					q.push(new_square);
					Mark(new_square, distant);
					edge_to[next_row][next_column] = current;
					if (e == new_square) {
						return;
					}
				}
			}
		}
	}
	return;
}

int main() {
	scanf("%d", &t);
	InitBoard();
	for (int i = 0; i < t; ++i) {
		Init();
		Bfs(start, destination);
		printf("%d\n", board[destination.row][destination.column]);
	}

	return 0;
}
