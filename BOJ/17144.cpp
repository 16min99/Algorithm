#include <iostream>
#include <vector>
using namespace std;

#define max 50

int room[max][max] = { 0 };
vector<pair<pair<int, int>, int>> vc;

int R, C, T;
int cleanerR=0;


void diffusion() {
	int dust = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (room[i][j] != 0 && room[i][j] != -1)
			{
				dust = room[i][j] / 5;
				if (i != 0 && !(i == cleanerR + 1 && j == 0)) { //위로확산
					vc.push_back(make_pair(make_pair(i - 1, j), dust));
					room[i][j] = room[i][j] - dust;
				}
				if (j != C - 1) {//오른쪽
					vc.push_back(make_pair(make_pair(i, j + 1), dust));
					room[i][j] = room[i][j] - dust;
				}
				if (i != R - 1 && !(i == cleanerR - 2 && j == 0)) {//아래
					vc.push_back(make_pair(make_pair(i + 1, j), dust));
					room[i][j] = room[i][j] - dust;
				}
				if (j != 0 && !(j == 1 && (i == cleanerR - 1 || i == cleanerR))) {//왼쪽
					vc.push_back(make_pair(make_pair(i, j - 1), dust));
					room[i][j] = room[i][j] - dust;
				}
			}
		}
	}
	int r, c;
	for (int i = 0; i < vc.size(); i++) {
		r = vc[i].first.first;
		c = vc[i].first.second;
		dust = vc[i].second;
		room[r][c] = room[r][c] + dust;
	}
	vc.clear();

}


void cleanerUP() { //공기청정기 윗부분

	for (int i = cleanerR -2 ; i > 0; i--) {//↓
		room[i][0] = room[i - 1][0];
	}
	for (int i = 0; i < C - 1; i++) {//←
		room[0][i] = room[0][i + 1];
	}
	for (int i = 0; i < cleanerR-1; i++) {//↑
		room[i][C - 1] = room[i + 1][C - 1];
	}
	for (int i = C - 1; i > 1; i--) {//→
		room[cleanerR-1][i] = room[cleanerR-1][i - 1];
	}
	room[cleanerR-1][1] = 0;

}

void cleanerDOUWN() {//공기청정기 아래부분

	for (int i = cleanerR + 1; i < R - 1; i++) {//↑
		room[i][0] = room[i + 1][0];
	}

	for (int i = 0; i < C - 1; i++) {//←
		room[R - 1][i] = room[R - 1][i + 1];
	}
	for (int i = R - 1; i > cleanerR  ; i--) {//↓
		room[i][C - 1] = room[i - 1][C - 1];
	}


	for (int i = C - 1; i > 1; i--){//→
		room[cleanerR][i] = room[cleanerR ][i - 1];
	}
	room[cleanerR][1] = 0;

	

}

int main() {

	cin >> R >> C >> T;


	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> room[i][j];
			if (room[i][j] == -1) {
				cleanerR = i;
			}
		}
	}

	
	for (int i = 0; i < T; i++) {
		diffusion();
	 cleanerUP();
		cleanerDOUWN();
	}
	
	int amount=0;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (room[i][j] != -1) {
				amount = amount + room[i][j];
			}
		}
		
	}
	cout << amount;

	return 0;

}
