#include<iostream>
#include<string>
using namespace std;
string N, M;
int n, m;
int arr[201];
int main() {
	cin >> n >> m;
	cin >> N >> M;
	if (n <= m) {
		for (int i = 0; i < n; i++) {
			arr[2 * i] = N[i];
			arr[2 * i + 1] = M[i];
		}
		for (int i = n; i < m; i++) {
			arr[i + n] = M[i];
		}
	}
	else {
		for (int i = 0; i < m; i++) {
			arr[2 * i] = N[i];
			arr[2 * i + 1] = M[i];
		}
		for (int i = m; i < n; i++) {
			arr[i + m] = N[i];
		}
	}
	for (int i = 0; i < n + m; i++) {
		if (arr[i] == 'A' || arr[i] == 'F' || arr[i] == 'H' || arr[i] == 'K' || arr[i] == 'M') arr[i] = 3;
		else if (arr[i] == 'B' || arr[i] == 'D' || arr[i] == 'N' || arr[i] == 'P' || arr[i] == 'Q' || arr[i] == 'R' || arr[i] == 'T'  || arr[i] == 'X' || arr[i] == 'Y') arr[i] = 2;
		else if (arr[i] == 'E') arr[i] = 4;
		else if(arr[i]=='C'||arr[i]=='G' || arr[i] =='I' || arr[i] == 'J' || arr[i] == 'L' || arr[i] == 'O' || arr[i] == 'S' || arr[i] == 'U' || arr[i] == 'V' || arr[i] == 'W' || arr[i] == 'Z') arr[i] = 1;
	}
	for (int j = 1; j < n + m - 1; j++) {
		for (int i = 0; i < n + m - j; i++) {
			if (arr[i] + arr[i + 1] < 10) arr[i] = arr[i] + arr[i + 1];
			else arr[i] = arr[i] + arr[i + 1] - 10;
		}
	}
	if (arr[0] != 0) cout << arr[0];
	cout << arr[1]; 
	cout<<"%";
	return 0;
}