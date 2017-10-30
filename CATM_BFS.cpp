//Solution for http://www.spoj.com/problems/CATM/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using Board = vector<vector<int>>;

constexpr int dx[] = {1, -1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};
constexpr int N_BORDERS = 1;

struct Cell {
	int row, column;
	bool operator==(const Cell &b) const {if (this->row == b.row && this->column == b.column) return true; return false;}
};

constexpr Cell root = { -1, -1};

int n, m, k;
Cell mouse, cat1, cat2;
Board cats_board, mouse_board;

void PrintBoard(Board &board) {
	for (int row = 0; row < n + 2 * N_BORDERS; ++row) {
		for (int column = 0; column < m + 2 * N_BORDERS; ++column)
			printf("%d ", board[row][column]);
		printf("\n");
	}
	printf("---END---\n");
}

void Mark(Board &board, const Cell &cell, const int &mark) { board[cell.row][cell.column] = mark; }

void InitBoardHelper(Board &board) {
	board = Board(n + 2 * N_BORDERS);
	for (int row = 0; row < n + 2 * N_BORDERS; ++row) {
		for (int column = 0; column < m + 2 * N_BORDERS; ++column)
			board[row].push_back(1);
	}
}

void ResetVisited(Board &board) {
	for (int row = 1; row < n + N_BORDERS; ++row) {
		for (int column = 1; column < m + N_BORDERS; ++column)
			board[row][column] = 0;
	}
}

void InitBoard() {
	scanf("%d%d%d", &n, &m, &k);

	InitBoardHelper(cats_board);
	InitBoardHelper(mouse_board);
}

void Init() {
	scanf("%d %d %d %d %d %d", &mouse.row, &mouse.column, &cat1.row, &cat1.column,
	      &cat2.row, &cat2.column);

	ResetVisited(cats_board);
	ResetVisited(mouse_board);
}

bool IsMouseEscaped(Cell cell) {
	if (cell.row == 1 || cell.row == n || cell.column == 1 || cell.column == m)
		return true;
	return false;
}

void BfsCat(const Cell &cat1_, const Cell &cat2_, Board &board) {
	queue<Cell> q;
	int distant = 1;
	int next_row, next_column;

	q.push(cat1_);
	q.push(cat2_);
	q.push(root);

	Mark(board, cat1_, distant);
	Mark(board, cat2_, distant);

	while (!q.empty()) {
		Cell current = q.front();
		q.pop();
		if (current == root) {
			if (current == q.front()) {
				return;
			}
			distant++;
			q.push(root);
		} else {
			for (int dir = 0; dir < 4; ++dir) {
				next_row = current.row + dx[dir];
				next_column = current.column + dy[dir];
				if (board[next_row][next_column] == 0) {
					Cell new_cell = {next_row, next_column};
					q.push(new_cell);
					Mark(board, new_cell, distant);
				}
			}
		}
	}
}

bool BfsMouse(const Cell &mouse_, Board &board) {
	if (IsMouseEscaped(mouse)) return true;
	queue<Cell> q;
	int distant = 1;
	int next_row, next_column;

	q.push(mouse_);
	q.push(root);

	Mark(mouse_board, mouse_, distant);

	while (!q.empty()) {
		Cell current = q.front();
		q.pop();
		if (current == root) {
			if (current == q.front()) {
				return false;
			}
			distant++;
			q.push(root);
		} else {
			for (int dir = 0; dir < 4; ++dir) {
				next_row = current.row + dx[dir];
				next_column = current.column + dy[dir];
				if (board[next_row][next_column] == 0 && distant < cats_board[next_row][next_column]) {
					Cell new_cell = {next_row, next_column};
					if (IsMouseEscaped(new_cell)) {
						return true;
					}
					q.push(new_cell);
					Mark(board, new_cell, distant);
				}
			}
		}
	}
}

void Work() {
	Init();
	BfsCat(cat1, cat2, cats_board);
	if (BfsMouse(mouse, mouse_board)) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
}

int main() {
	InitBoard();
	for (int i = 0; i < k; ++i) {
		Work();
	}

	return 0;
}
