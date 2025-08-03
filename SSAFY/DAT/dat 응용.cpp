#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

string isreg[10001] = {"", };
int isin[10001] = { 0, };

int DAT[1000001];
int height[1000001];
int card[1000001];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// 사원 출입 관리 시스템
	int n;
	cin >> n;

	int type, cnum;
	string name;

	for (int i = 0; i < n; i++) {
		cin >> type;
		if (type == 1) {
			cin >> cnum >> name;
			if (isreg[cnum] != "") {
				cout << cnum << " ERROR\n";
			}
			else {
				isreg[cnum] = name;
				cout << cnum << " OK\n";
			}
		}
		else {
			cin >> cnum;
			if (isreg[cnum] == "") {
				cout << cnum << " ERROR\n";
			}
			else if (isin[cnum]) {
				cout << cnum << " " << isreg[cnum] << " EXIT\n";
				isin[cnum] = 0;
			}
			else {
				cout << cnum << " " << isreg[cnum] << " ENTER\n";
				isin[cnum] = 1;
			}
		}
	}

	// 카드 발급기 - 키가 작을수록 높은 번호 배정
	// 키와 번호를 입력받아서 순서가 올바른지 체크하기
	int T, n;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			int h;
			cin >> h;
			height[i] = h;
		}

		for (int i = 0; i < n; i++) {
			int c;
			cin >> c;
			card[i] = c;
		}

		for (int i = 0; i < n; i++) {
			DAT[card[i]] = height[i];
		}
		
		int flag = 0;
		for (int i = 1; i < n; i++) {
			if (DAT[i] < DAT[i + 1]) {
				cout << "NO\n";
				flag = 1;
				break;
			}
		}
		if (!flag) cout << "YES\n";
	}

	return 0;
}