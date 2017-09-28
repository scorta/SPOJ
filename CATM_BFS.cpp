//Solution for http://www.spoj.com/problems/CATM/
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Cell {
    int row, column;
};

int n, m, k;
Cell mouse, cat1, cat2;

vector<vector<int>> field;

void Mark(Cell cell) { field[cell.row][cell.column] = 0; }

int Distant(const Cell &cell1, const Cell &cell2){
    return abs(cell1.row - cell2.row) + abs(cell1.column - cell2.column);
}

bool ShouldMoveTo(const Cell &cell){
    if(Distant(mouse, cell) < Distant(cat1, cell) && Distant(mouse, cell) < Distant(cat2, cell))
        return true;
    return false;
}

void InitBoard() {
    scanf("%d%d%d", &n, &m, &k);

    field = vector<vector<int>>(n + 2);
    for (int row = 0; row < n + 2; ++row) {
        for (int column = 0; column < m + 2; ++column)
            field[row].push_back(0);
    }
}

void ResetVisited() {
    for (int row = 1; row < n + 1; ++row) {
        for (int column = 1; column < m + 1; ++column)
            field[row][column] = 1;
    }
}

void Init() {
    scanf("%d %d %d %d %d %d", &mouse.row, &mouse.column, &cat1.row, &cat1.column,
          &cat2.row, &cat2.column);

    Mark(mouse);
    Mark(cat1);
    Mark(cat2);
}

bool IsMouseEscaped(Cell cell) {
    if (cell.row == 1 || cell.row == n || cell.column == 1 || cell.column == m)
        return true;
    return false;
}

bool Bfs() {
    if (IsMouseEscaped(mouse)){
        return true;
    }
    int step = 0;
    queue<Cell> q;
    q.push(mouse);
    Mark(mouse);
    while (!q.empty()) {
        Cell current_cell = q.front();
        q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int next_row = current_cell.row + dx[dir];
            int next_column = current_cell.column + dy[dir];

            if (field[next_row][next_column]) {
                Cell new_cell = {next_row, next_column};
                if(ShouldMoveTo(new_cell)) {
                    if (IsMouseEscaped(new_cell)) {
                        return true;
                    }
                    Mark(new_cell);
                    q.push(new_cell);
                }
            }
        }
    }
    return false;
}

int main() {
    InitBoard();
    for (int i = 0; i < k; ++i) {
        ResetVisited();
        Init();
        if (Bfs())
            printf("YES\n");
        else
            printf("NO\n");
        ResetVisited();
    }
    return 0;
}
