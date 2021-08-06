#include <bits/stdc++.h>
using namespace std;

int n, m;

string s[1001];
int dp[1001][1001];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		
	}
	int Max = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = s[i-1][j-1] - 48;
			if (dp[i][j] == 1 ) {
			/*	if (dp[i - 1][j] == dp[i][j - 1]) {
				
				
				}
				else {*/
				
				/*if (dp[i - 1][j - 1] == 0 || dp[i - 1][j] == 0 || dp[i][j - 1] == 0) continue;
				else */
				dp[i][j] =min(dp[i - 1][j - 1],min(dp[i][j-1],dp[i-1][j])) + 1;
				Max = max(dp[i][j], Max);
				//}

					
			}
		}
	}
	//cout << endl;

	/*for (int i = 0; i < n; i++) { 
		for (int j = 0; j < m; j++) {
			cout << dp[i][j];
		}
		cout << endl;
	}*/
	cout << Max*Max << endl;

	return 0;
}