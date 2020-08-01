#include <stdio.h>

#define abs(a, b) ((a-b > 0) ? (a-b) : (b-a))
#define NMAX (500+1)
int dx[] = { 1, -1, 0,  0 };
int dy[] = { 0,  0, 1, -1 };

int n;
int grid[NMAX][NMAX];
int visited[NMAX][NMAX];

int is_gonna_next(int i, int j, int d, int dir)
{
	int i_n = i + dx[dir];
	int j_n = j + dy[dir];
	return (i_n >= 0 && i_n < n && j_n >= 0 && j_n < n && abs(grid[i_n][j_n], grid[i][j]) <= d);
}

int dfs(int i, int j, int d) 
{
	if (visited[i][j]) return 0;
	visited[i][j] = 1;
	int count = 1;

	for (int dir = 0; dir < 4; dir++) 
	{
		int i_n = i + dx[dir];
		int j_n = j + dy[dir];
		if (is_gonna_next(i, j, d, dir)) count += dfs(i_n, j_n, d);
	}
	return count;
}

int is_possible(int d) 
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!visited[i][j]) {
				if (dfs(i, j, d) * 2 >= n * n) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void input_data()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &grid[i][j]);
		}
	}
}

int main() 
{
	freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	input_data();
	
	int s = -1, e = 1000000;
	while (e > s + 1) {
		int mid = (s + e) / 2;
		if (is_possible(mid)) e = mid;
		else s = mid;
	}
	printf("%d\n", e);
}