//1062
#include <bits/stdc++.h>
using namespace std;
vector <string> vec;
bool alpha[26];
int N, K;
int res = 0;

void Check() {
    int tmp_res = 0;
    for (int i = 0; i < N; i++) {
        bool flg = 0;

        for (int j = 0; j < vec[i].length(); j++) {
            if (!alpha[vec[i][j] - 97]) {
                flg = 1;
                break;
            }
        }
        if (!flg)tmp_res++;
    }
    res = max(res, tmp_res);
    return;
}

void Learn_alpha(int int_alpha, int Learn) {
    if (K == Learn) {
        Check();
        return;
    }
    else {
        for (int i = int_alpha; i < 26; i++) {
            if (!alpha[i]) {
                alpha[i] = 1;
                Learn_alpha(i, Learn + 1);
                alpha[i] = 0;
            }
        }
    }
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> K;
    if (K < 5) cout << 0;
    else if (K == 26) cout << N;
    else {

        bool alpa[26];
        alpa['a' - 97] = 1;
        alpa['c' - 97] = 1;
        alpa['n' - 97] = 1;
        alpa['t' - 97] = 1;
        alpa['i' - 97] = 1;
        K = K - 5;

        for (int i = 0; i < N; i++) {
            string tmp;
            cin >> tmp;
            string str = "";
            for (int j = 4; j < tmp.size() - 4; j++) {
                //if (alpa[tmp[j] - 97] != 1)
                str = str + tmp[j];
            }
            vec.push_back(str);
        }
        Learn_alpha(0, 0);
        cout << res;

    }
    return 0;
}