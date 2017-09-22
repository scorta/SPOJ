//Solution for The Cats and the Mouse problem on SPOJ: http://www.spoj.com/problems/CATM/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Cell
{
	int row, column;
};

int n, m, k;
Cell mouse, cat1, cat2;

int Distant(Cell start, Cell target) {
	return abs(start.row - target.row) + abs(start.column - target.column);
}

bool IsEscapedCell(Cell target) {
	if (Distant(mouse, target) < Distant(cat1, target) && Distant(mouse, target) < Distant(cat2, target))
		return true;
	return false;
}

void Init() {
	scanf("%d%d%d", &n, &m, &k);
}

void Work() {
	Cell target1, target2;
	bool found;
	for (int i = 0; i < k; ++i) {
		scanf("%d%d%d%d%d%d", &mouse.row, &mouse.column, &cat1.row, &cat1.column, &cat2.row, &cat2.column);
		found = false;

		for (int row = 1; row <= n; ++row) {
			target1 = {row, 1};
			target2 = {row, m};
			if (IsEscapedCell(target1) || IsEscapedCell(target2)) {
				printf("YES\n");
				found = true;
				break;
			}
		}

		if (!found) {
			for (int column = 1; column <= m; ++column) {
				target1 = {1, column};
				target2 = {n, column};
				if (IsEscapedCell(target1) || IsEscapedCell(target2)) {
					printf("YES\n");
					found = true;
					break;
				}
			}
		}

		if(!found){
			printf("NO\n");
		}
	}
}

int main() {
	Init();
	Work();
}
