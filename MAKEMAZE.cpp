//http://www.spoj.com/problems/MAKEMAZE/
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Node
{
	int row, column;
};

int t, m, n;
vector<vector<int>> maze;
Node start_v, end_v;

void Print_maze()
{
	for (int row = 0; row < m + 2; row++)
	{
		for (int column = 0; column < n + 2; column++)
		{
			printf("%d ", maze[row][column]);
		}
		printf("\n");
	}
	printf("\nEND\n");
}

void Unmark(Node node)
{
	maze[node.row][node.column] = 2;
}

bool Check_entry_helper(int row, int column, int &count_entry)
{
	if (maze[row][column] == 1)
	{
		count_entry++;
		if (count_entry == 1)
		{
			start_v.row = row;
			start_v.column = column;
		}
		else if (count_entry == 2)
		{
			end_v.row = row;
			end_v.column = column;
		}
		else if (count_entry > 2)
			return false;
	}
	return true;
}

bool Check_entry()
{
	int count_entry = 0;
	for (int row = 1; row < m + 1; ++row)
	{
		if (!Check_entry_helper(row, 1, count_entry))
			return false;
		if (n != 1)
			if (!Check_entry_helper(row, n, count_entry))
				return false;
	}

	for (int column = 2; column < n; ++column)
	{
		if (!Check_entry_helper(1, column, count_entry))
			return false;
		if (m != 1)
			if (!Check_entry_helper(m, column, count_entry))
				return false;
	}

	return true;
}

void Init()
{
	scanf("%d%d", &m, &n);

	vector<vector<int>> temp_maze(m + 2);
	maze = temp_maze;

	for (int row = 0; row < m + 2; ++row)
	{
		for (int column = 0; column < n + 2; ++column)
		{
			maze[row].push_back(2);
		}
	}

	for (int row = 1; row < m + 1; ++row)
	{
		for (int column = 1; column < n + 1; ++column)
		{
			char cell;
			int node;

			do
			{
				scanf("%c", &cell);
			} while (cell != '#' && cell != '.');

			if (cell == '.')
				node = 1;
			else
				node = 0;

			maze[row][column] = node;
		}
	}

	//Print_maze();
}

bool Bfs(Node start, Node end)
{
	queue<Node> q;
	q.push(start);
	Unmark(start);

	while (!q.empty())
	{
		Node node = q.front();
		q.pop();

		for (int dir = 0; dir < 4; ++dir)
		{
			int next_row = node.row + dx[dir];
			int next_column = node.column + dy[dir];

			if (maze[next_row][next_column] == 1)
			{
				if (end.row == next_row && end.column == next_column)
				{
					return true;
				}
				Node next_node = {next_row, next_column};
				Unmark(next_node);
				q.push(next_node);
			}
		}
	}
	return false;
}

void Work()
{
	Init();

	if (Check_entry())
	{
		if (Bfs(start_v, end_v))
		{
			printf("valid");
		}
		else
		{
			printf("invalid");
		}
	}
	else
	{
		printf("invalid");
	}

	printf("\n");
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i)
	{
		Work();
	}

	// Init();
	// Print_maze();
	// vector<vector<int>> temp_maze(m + 2);
	// maze = temp_maze;
	// Print_maze();

	return 0;
}
