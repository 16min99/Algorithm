//로또

#include <iostream>
using namespace std;
#define MAX 13
#include <algorithm>


int lotto[MAX];
int arr[MAX];
int k;

void Cout() {
	for (int i = 0; i < 6; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void dfs(int start,int count) {
	if (count == 6) {
		Cout();
		return;
	}
	for (int i = start; i < k; i++) {
		arr[count] = lotto[i];
		dfs(i + 1, count + 1);
	}
}


int main() {

	for (;;) {
		cin >> k;
		if (k==0) {
			break;
		}
		
		for (int i = 0; i < k; i++) {
			cin >> lotto[i];
		}
		dfs(0, 0);
		cout << endl;

	}

}