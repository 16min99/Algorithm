#include <iostream>
#include <algorithm>

using namespace std;
#define INF 99999999
#define MAX 101
int N, M;
int arr[MAX][MAX];
int a, b, c;

void floyd() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= N; k++) {
				if (arr[j][i] != INF && arr[i][k] != INF) {
					if (arr[j][k] > arr[j][i] + arr[i][k]) {
							arr[j][k] = arr[j][i] + arr[i][k];
				}
				;
				}
			}
		}
	}
}


int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			arr[i][j] = INF;
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		if (arr[a][b] > c) {
			arr[a][b] = c;
		}
	}

	floyd();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j || arr[i][j] == INF) {
				cout << 0 << " ";
			}
			else {
				cout << arr[i][j] << " ";
			}

		}

		cout << endl;

	}

	return 0;
}