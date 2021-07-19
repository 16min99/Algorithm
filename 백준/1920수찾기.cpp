//���� ���� , ����Ž��
#include <bits/stdc++.h>
using namespace std;
int A[100000];
void BS(int n, int key) {
	int start = 0;
	int end = n - 1;
	int mid;
	while (end - start >= 0) {
		mid = (start + end) / 2;

		if (A[mid] == key) {   //key ���� �迭�� �߾� ���� ������
			cout << 1 << "\n";
			return;
		}
		else if (A[mid] > key) { //key ���� �迭�� �߾� ������ ������ 
			end = mid - 1;
		}
		else {  //key ���� �迭�� �߾� ������ Ŭ�� 
			start = mid + 1;
		}
	}

	cout << 0 << "\n";
	return;
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int N, M;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	sort(A, A + N);
	cin >> M;

	for (int i = 0; i < M; i++) {
		int num;
		cin >> num;
		BS(N, num);
	}

	return 0;
}

