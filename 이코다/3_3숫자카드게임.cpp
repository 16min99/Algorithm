//DBB3-3숫자카드게임
#include <iostream>
using namespace std;
int main(void) {
	int N, M;
	int arr[101][101];
	
	
	int min[101];

	
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		min[i] = 10001;
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j]<min[i]) {
				min[i] = arr[i][j];
			}
		}
	}


	int j = 0;
	int tmp = 0;
	int idx = 0;
	for (j = 0; j < N; j++) {
		if (min[j] > tmp) {
			tmp = min[j];
			
		}
	}

	cout << tmp;
}