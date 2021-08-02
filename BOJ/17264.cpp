#include<iostream>
using namespace std;
#include<string>

int N, P;
int W, L, G;
string p[1000];

int rating = 0;
bool B = 0;
int main() {

	cin >> N >> P;
	cin >> W >> L >> G;

	int wcnt = 0;
	for (int i = 0; i < P; i++) {
		string qp;
		char R;
		cin >> qp >> R;
		if (R == 'W') p[wcnt++] = qp;
	}

	for (int i = 0; i < N; i++)
	{
		string t;
		cin >> t;
		bool find=0;
		for (int j = 0; j < wcnt; j++) {
			if (t == p[j]) find = 1;
		}

		if (find == 0) rating -= L;
		else rating += W;
		
		
		if (rating < 0) rating = 0;
		else if (rating >= G)  B = 1;
	}

	if (B==1) cout << "I AM NOT IRONMAN!!";
	else cout << "I AM IRONMAN!!";

	return 0;
}