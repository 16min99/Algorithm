#include<iostream>
using namespace std;
#define MAX 987654321
//벨만-포드는 간선 리스트로 한다 인접리스트 필요X 
#include<vector>
#include<algorithm>
int N;
int M;
bool flg = 0 ;
struct edge {
	int start;
	int end;
	int cost;
};

edge list[6001];
long long dist[501];

void BellmanFord() {
	for (int i = 1; i < N; i++) {
		for (int j = 1; j <= M; j++) {
			edge cur = list[j];
			if (dist[cur.start] == MAX)continue;
			dist[cur.end] = min(dist[cur.end], dist[cur.start] + cur.cost);
		}
	}

	for (int i = 1; i <= M; i++) {
		edge cur = list[i];
		if (dist[cur.start] == MAX) continue;

		if (dist[cur.start] + cur.cost < dist[cur.end]) {
			flg = 1;
			return;
		}
	}
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	cin >> M;

	
	for (int i = 1; i <= M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		edge tmp;
		tmp.start = a;
		tmp.end = b;
		tmp.cost = c;
		list[i]=tmp;
	}
	dist[1] = 0;
	for (int i = 2; i <= N; i++) dist[i] = MAX;
	
	BellmanFord();
	if (flg) cout << "-1\n";
	else {
		for (int i = 2; i <= N; i++) {
			if (dist[i] == MAX) cout << "-1\n";
			else cout << dist[i] << "\n";
		}
	}



	return 0;
}
