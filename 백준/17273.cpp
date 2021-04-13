#include<iostream>
using namespace std;

int N, M;
int arr[1][2];//번째카드 ,0=앞A 1=뒤B 

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> arr[i][0] >> arr[i][1];
	}

	int ind = 0;
	for (int j = 0; j < M; j++) {
		int K;
		cin >> K;
		if (K < arr[0][ind] && ind == 0) ind = 0;
		else if (K < arr[0][ind] && ind== 1)ind = 1;
		else if (!(K < arr[0][ind])&&ind ==0)ind = 1;
		else if (!(K < arr[0][ind]) && ind == 1)ind = 0;
	}


	cout << arr[0][ind];

	return 0;
}