#include <bits/stdc++.h>
using namespace std;

//좌 우 위 아래
int mx[4] = { -1,1,0,0 };
int my[4] = { 0,0,-1,1 };
int R, C;
char Map[51][51];
int dp[51][51];

struct Point {
	int y;
	int x;
	char type;
};

queue <Point> q;
bool foundAnswer;


int main() {
	cin >> R >> C;

	Point st;
	for (int r = 0; r < R; r++) {
		string str;
		cin >> str;
		for (int c = 0; c < C; c++) {
			Map[r][c] = (char)str[c];
			if (Map[r][c] == 'S') {
				st.y = r;
				st.x = c;
				st.type = 'S';
			}
			else if (Map[r][c] == '*') {
				Point pt;
				pt.y = r;
				pt.x = c;
				pt.type = '*';
				q.push(pt);//물 먼저 큐에넣고
			}
		}
	}
	q.push(st);//두더지 넣기

	while (!q.empty()) {
		//1. 큐에서 꺼내옴
		Point p = q.front();
		q.pop();
		//2. 목적지인가? if(p==D)
		if (p.type == 'D') {
			cout << dp[p.y][p.x] << endl;
			foundAnswer = 1;
			break;
		}
		//3. 갈 수 있는 곳을 순회 for( 좌, 우 ,위 ,아래)
		for (int i = 0; i < 4; i++) {
			int ty = p.y + my[i];
			int tx = p.x + mx[i];
			//4. 갈 수 있는가? if(맵을 벗어나지 않고,[.]이거나[D]이거나)
			if (0 <= ty && ty < R && 0 <= tx && tx < C) {
				if (p.type == '*') {
					if (Map[ty][tx] == '.' || Map[ty][tx] == 'S') {
						//5.체크인
						Map[ty][tx] = '*';
						//6.큐에 넣음
						Point pt;
						pt.y = ty;
						pt.x = tx;
						pt.type = '*';
						q.push(pt);
					}
				}
				else {
					//[.]이거나[D]이거나
					if (Map[ty][tx] == '.' || Map[ty][tx] == 'D') {
						if (dp[ty][tx] == 0) {//방문 한적이 없고
							//5. 체크인
							dp[ty][tx] = dp[p.y][p.x] + 1;
							//6. 큐에넣음
							Point pt;
							pt.y = ty;
							pt.x = tx;
							pt.type = Map[ty][tx];
							q.push(pt);
						}
					}

				}
			}		
		}
	}
	if (foundAnswer == 0) cout << "KAKTUS" << endl;
	return 0;
}