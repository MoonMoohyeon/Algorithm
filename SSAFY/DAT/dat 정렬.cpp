#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{

    // 배열에 존재하는 알파벳 정렬하여 출력하기
	char arr[5][3] = { {'A','B','C'}, {'A','G','H'}, {'H','I','J'}, {'K','A','B'}, {'A','B','C'} };
	int DAT[26] = { 0, };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			DAT[arr[i][j] - 'A'] += 1;
		}
	}

	for (int i = 0; i < 26; i++) {
		while (DAT[i]--) cout << static_cast<char>(i + 'A');
	}

    // 존재하는 알파벳 순서대로 정렬(중복 제외)
    string str;
	cin >> str;
	char DAT[26] = { 0, };
	for (int i = 0; i < str.size(); i++) {
		DAT[str[i] - 'A']++;
	}

	for (int i = 0; i < 26; i++) {
		if (DAT[i]) cout << static_cast<char>(i + 'A');
	}
	
	return 0;
	
	return 0;
}