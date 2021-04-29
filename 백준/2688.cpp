//줄어들지않아 
#include<iostream>
using namespace std;

long long dp[10][64];
int main() {
	int T, n;
	cin >> T;

	for (int t = 0; t < T; t++) {
		cin >> n;
		
		for (int i = 0; i < 10; i++) {
			
			for (int j = 0; j < 64; j++) {
				dp[i][j] = 0;
		}
			dp[i][1] = 1;
		}

		for (int j = 2; j <= n; j++) {
			for (int i = 0; i < 10; i++) {
				for (int k = 0; k + i < 10; k++) {
					dp[i][j] += dp[i + k][j - 1];
					dp[i][j] = dp[i][j];
				}
			}
		}
		long long ans = 0;
		for (int i = 0; i < 10; i++) {
			ans = ans + dp[i][n];
		}

		cout << ans << endl;
	}

	return 0;
}