#include<iostream>
using namespace std;
int A[500000];

int main() {
	int N;
	int max = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
		if (max < A[i]) max = A[i];
	}
	cout << max;
	return 0;
}