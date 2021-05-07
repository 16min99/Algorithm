#include <iostream>
using namespace std;
#include <vector>
#include <queue>

bool visited[9];
int map[201][201];

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int N, M;
void bfs(int s_x, int s_y) {
    queue<pair<int, int>> q;
    q.push({ s_x, s_y });


    while (!q.empty()) {//q가 빌때까지
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();


        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (map[nx][ny] == 1 && nx > 0 && nx <= N && ny > 0 && ny <= M) {
                map[nx][ny] = 1 + map[cx][cy];
                q.push({ nx,ny });
            }
        }
    }
}

void print() {

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

int main() {

    cin >> N >> M;
    // 2차원 리스트의 맵 정보 입력 받기 공백구분없이 받기
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%1d", &map[i][j]);
        }
    }

    bfs(1, 1);
//    print();
    cout << map[N][M];

    return 0;


}