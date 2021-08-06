#include <bits/stdc++.h>
using namespace std;


int N, M;
int arr[100001];
	
int dp[100001];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> M;

	
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
		if (i == 1) dp[1] = arr[1];
		else dp[i] = dp[i - 1] + arr[i];
	}
	


	for (int i = 1; i <= M; i++) {
		int l, r;
		cin >> l >> r;
		cout << dp[r] - dp[l - 1] << "\n";
	}


	return 0;
}
