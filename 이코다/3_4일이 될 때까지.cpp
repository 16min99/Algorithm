//DBB3-4일이 될 때까지
#include <iostream>
using namespace std;
#include <algorithm>
int main(void) {
	int N, K;
	cin >> N >> K;
	
	int cnt=0;
	while (N != 1) {
		if (N % K != 0) {
			N--;
			cnt++;
		}
		else {
			N /= K;
			cnt++;
		
		}
	}
	cout << cnt;
}