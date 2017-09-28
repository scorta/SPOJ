//Solution for http://www.spoj.com/problems/PPATH/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cstdlib>

using namespace std;

const int NMAX = 10000;

bool is_prime[NMAX], mark[NMAX];
int edge_to[NMAX];

void Sieve(){
	memset(is_prime, true, sizeof(is_prime));
	is_prime[0] = false;
	is_prime[1] = false;
	is_prime[2] = true;

	for (int i = 2; i < NMAX; ++i)
		for (int j = i + i; j < NMAX; j += i){
			is_prime[j] = false;
		}
}

void Init(){
	memset(mark, false, sizeof(mark));
	memset(edge_to, -1, sizeof(edge_to));
}

int Distant(int target){
	int index = target;
	int distant = 0;

	while (edge_to[index] != -1){
		index = edge_to[index];
		distant++;
	}

	return distant;
}

int Bfs(int start, int target){
	if (start == target) return 0;
	queue<int> q;	

	q.push(start);
	edge_to[start] = -1;
	mark[start] = true;
	int step = 0;
	while (!q.empty()){
		char num_str[4];
		int current_number = q.front();
		q.pop();
		step++;
		sprintf(num_str, "%d", current_number);

		for (int position = 0; position < 4; ++position)
			for (int value = 0; value <= 9; ++value){
				if ((value == 0 && position == 0) || (value % 2 == 0 && position == 3)) continue;

				char temp_num_str[4];
				memcpy(temp_num_str, num_str, 4);
				temp_num_str[position] = value + '0';

				int next_number = atoi(temp_num_str);
				if (is_prime[next_number] && !mark[next_number]){
					mark[next_number] = true;
					q.push(next_number);
					edge_to[next_number] = current_number;
					if (next_number == target){
						return Distant(target);
					}
				}

			}
	}
	return -1;
}

void Solve(){
	int no_of_case;
	vector<pair<int, int>> room_numbers;
	scanf("%d", &no_of_case);

	for (int i = 0; i < no_of_case; ++i){
		pair<int, int> room_number;
		scanf("%d%d", &room_number.first, &room_number.second);
		room_numbers.push_back(room_number);
	}

	for (auto i : room_numbers){
		Init();

		int step = Bfs(i.first, i.second);
		if (step >= 0)
			printf("%d\n", step);
		else
			printf("Impossible");
	}
}

int main(){
	Sieve();
	Solve();	

	return 0;
}
