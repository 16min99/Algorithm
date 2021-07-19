// 같은 결과의 예외 처리가 많은 경우 if문(case) 을 통해서 하는것보다 메쏘드를 만드는 것이 좋다.
// 30%에서 틀렸습니다 나오는 것은 %와 / 연산자에 대한 예외처리가 잘못된 경우이다.
// %연산자에서 앞 피연산자의 부호를 따라가는데 앞,뒤 연산자 순서가 잘못돼서 오래걸림
#include <bits/stdc++.h>
using namespace std;

stack <long long> stk;
vector<string> commands;
vector<long long> nums;
int N;

bool NUM(long long x) {
	stk.push(x);
	return 0;
}

bool POP() {
	if (stk.empty()) return 1;
	stk.pop();
	return 0;
}

bool INV() {
	if (stk.empty())return 1;
	long long tmp;
	tmp = -stk.top();
	stk.pop();
	stk.push(tmp);
	return 0;
}

bool DUP() {
	if (stk.empty()) return 1;
	stk.push(stk.top());
	return 0;
}

bool SWP() {
	if (stk.size() < 2) return 1;
	long long tmp1 = stk.top();
	stk.pop();
	long long tmp2 = stk.top();
	stk.pop();
	stk.push(tmp1);
	stk.push(tmp2);
	return 0;
}

bool ADD() {
	if (stk.size() < 2)return 1;
	long long tmp1, tmp2;
	tmp1 = stk.top();
	stk.pop();
	tmp2 = stk.top();
	stk.pop();
	if (tmp1 + tmp2 > 1000000000) return 1;
	else stk.push(tmp1 + tmp2);
	return 0;
}

bool SUB() {
	if (stk.size() < 2)return 1;
	long long tmp1, tmp2;
	tmp1 = stk.top();
	stk.pop();
	tmp2 = stk.top();
	stk.pop();
	stk.push(tmp2 - tmp1);
	return 0;
}



bool MUL() {
	if (stk.size() < 2)return 1;
	long long tmp1, tmp2;
	tmp1 = stk.top();
	stk.pop();
	tmp2 = stk.top();
	stk.pop();
	if (tmp1 * tmp2 > 1000000000) return 1;
	else stk.push(tmp2 * tmp1);
	return 0;
}

bool DIV() {
	if (stk.size() < 2) return 1;
	long long tmp1, tmp2;
	tmp1 = stk.top();
	if (tmp1 == 0) return 1;
	stk.pop();
	tmp2 = stk.top();
	stk.pop();
	int cnt = 0;
	if (tmp1 < 0)cnt++;
	if (tmp2 < 0) cnt++;
	if (cnt == 1)stk.push((-1) * (abs(tmp2) / abs(tmp1)));
	else stk.push(abs(tmp2) / abs(tmp1));
	return 0;
}

bool MOD() {
	if (stk.size() < 2)return 1;
	long long tmp1, tmp2;
	tmp1 = stk.top();
	if (tmp1 == 0) return 1;
	stk.pop();
	tmp2 = stk.top();
	stk.pop();
	if (tmp2 < 0) stk.push(-(abs(tmp2) % abs(tmp1)));
	else stk.push(abs(tmp2) % abs(tmp1));
	return 0;
}


int main() {

	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);


	bool error = 0;
	for (;;) {
		bool error = 0;

		for (;;) {
			string str;
			cin >> str;
			long long num;
			if (str == "NUM") {
				cin >> num;
				nums.push_back(num);
			}
			if (str == "QUIT") {
				return 0;
			}
			if (str == "END") {
				break;
			}
			commands.push_back(str);
		}

		cin >> N;

		for (int i = 0; i < N; i++) {
			long long num;
			cin >> num;
			stk.push(num);
			int nums_idx = 0;
			for (int j = 0; j < commands.size(); j++) {
				if (commands[j] == "NUM") {
					error = NUM(nums[nums_idx]);
					nums_idx++;
				}

				else if (commands[j] == "POP") error = POP();
				else if (commands[j] == "INV") error = INV();
				else if (commands[j] == "DUP") error = DUP();
				else if (commands[j] == "SWP") error = SWP();
				else if (commands[j] == "ADD") error = ADD();
				else if (commands[j] == "SUB") error = SUB();
				else if (commands[j] == "MUL") error = MUL();
				else if (commands[j] == "DIV") error = DIV();
				else if (commands[j] == "MOD") error = MOD();

				if (!stk.empty() && (abs(stk.top()) > 1000000000)) error = 1;
				if (error == 1) {
					break;
				}
			}

			if (error == 1 || stk.size() != 1)cout << "ERROR\n" ;
			else cout << stk.top() << "\n";
			while (!stk.empty()) {
				stk.pop();
			}
		}
		nums.clear();
		commands.clear();
		cout << endl;
	}
	return 0;

}