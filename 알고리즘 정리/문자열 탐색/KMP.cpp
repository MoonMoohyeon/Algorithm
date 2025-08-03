#include <iostream>
#include <vector>
using namespace std;

// 부분 일치 테이블(pi 배열) 생성
vector<int> computePi(const string& pattern) {
    int m = pattern.size();
    vector<int> pi(m, 0);
    int j = 0; // 접두사 비교 인덱스

    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1]; // 이전 접두사 정보로 이동

        if (pattern[i] == pattern[j]) {
            j++;
            pi[i] = j; // pi[i]에 접두사-접미사 일치 길이 저장
        }
    }
    return pi;
}

// KMP 문자열 검색 함수
vector<int> KMP(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    vector<int> output;
    vector<int> pi = computePi(pattern);
    vector<int> result; // 패턴이 나타난 위치 저장
    int i, j = 0; // 패턴의 비교 인덱스

    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1]; // 점프

        if (text[i] == pattern[j]) {
            if (j == m - 1) { // 패턴 끝까지 일치하면 찾음
                result.push_back(i - m + 1); // 시작 위치 저장
                j = pi[j]; // 다음 탐색을 위해 j 이동
            } else {
                j++; // 패턴의 다음 문자 비교
            }
        }
    }
    return result;
}

int main() {
    string text = "ABABABACABABABCABABABC";
    string pattern = "ABACABAB";

    vector<int> matches = KMP(text, pattern);

    cout << "패턴이 나타난 위치: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;

    return 0;
}