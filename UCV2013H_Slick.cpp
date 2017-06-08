#include <iostream>
#include <vector>

int n, m;
int count;
std::vector<std::vector<int>> map;
std::vector<std::vector<bool>> is_checked;

void print_matrix(){
	printf("\n");
	printf("\n");
	for (int iN = 0; iN <= n + 1; iN++){
		for (int iM = 0; iM <= m + 1; iM++){
			printf("%*d", 2, map[iN][iM]);
		}
		printf("\n");
	}
}

void init(){
	count = 2;
	scanf("%d", &n);
	scanf("%d", &m);

	std::vector<std::vector<int>> temp_map(n + 2);
	std::vector<std::vector<bool>> temp_is_checked(n + 2);
	map = temp_map;
	is_checked = temp_is_checked;

	for (int iN = 0; iN <= n + 1; iN++){
		for (int iM = 0; iM <= m + 1; iM++){
			map[iN].push_back(-1);
			is_checked[iN].push_back(false);
		}
	}

	for (int iN = 1; iN <= n; iN++){
		for (int iM = 1; iM <= m; iM++){
			int temp;
			scanf("%d", &temp);
			map[iN][iM] = temp;
		}
	}
}

void flood_fill(int row, int column, int mark){
	is_checked[row][column] = true;
	map[row][column] = mark;

	if (map[row + 1][column] == 1 && !is_checked[row + 1][column]){
		flood_fill(row + 1, column, mark);
	}

	if (map[row - 1][column] == 1 && !is_checked[row - 1][column]){
		flood_fill(row - 1, column, mark);
	}

	if (map[row][column + 1] == 1 && !is_checked[row][column + 1]){
		flood_fill(row, column + 1, mark);
	}

	if (map[row][column - 1] == 1 && !is_checked[row][column - 1]){
		flood_fill(row, column - 1, mark);
	}
}

void BFS(){
	for (int iN = 1; iN <= n; iN++){
		for (int iM = 1; iM <= m; iM++){
			if (map[iN][iM] == 1 && !is_checked[iN][iM]){
				flood_fill(iN, iM, count++);
			}
		}
	}
}

int main(){
	init();
	BFS();
	print_matrix();

	return 0;
}
