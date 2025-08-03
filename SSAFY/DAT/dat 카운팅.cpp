#include <iostream>
using namespace std;

/*
    DAT(Direct Access Table)
    배열의 조회 속도가 빠른 이점을 살린다.
    조회가 빈번한 경우 DAT에 기록하여 사용한다.
    해당 값의 존재 유무, 개수 체크 등에 사용한다.
*/

int main(int argc, char** argv) {
	int arr[10] = { 3,4,6,7,9,7,6,1,2,3 };
	
	// 개수 세기
	int DAT[10] = { 0, };
	for (int i = 0; i < 10; i++) {
		DAT[arr[i]] += 1; // 카운팅
	}
	int Q = 0;
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int num = 0;
		cin >> num;
		cout << num << DAT[num] << endl;
	}

	// 개수 세기(알파벳)
	char str[10] = "ACEFDFSAS";
	char DATc[26] = { 0, };
	for (int i = 0; i < 10; i++) {
		DATc[str[i] - 'A'] += 1;
	}

	cout << endl;
	for (int i = 0; i < 26; i++) {
		while(DATc[i]--) cout << static_cast<char>(i + 'A');
	}

	

	return 0;
}