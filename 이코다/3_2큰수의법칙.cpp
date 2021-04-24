//DBB3-2큰수의법칙
#include <iostream>
using namespace std;
#include <algorithm>
int main(void) {
	int N, M, K;
	int arr[1001];

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + N);
	int first = arr[N - 1];
	int second = arr[N - 2];

	int result = 0;

	int cnt = 0;

	for (int m = M; m > 0; m--) {
		if (cnt < K) {
			result += first;
			cnt++;
		}
		else {
			cnt = 0;
			result += second;
		}
	}


	cout << result;
}