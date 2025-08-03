#include <iostream>
#include <vector>
#include <string>
using namespace std;

// KMP 알고리즘의 핵심인 '부분 일치 테이블(LPS 배열)'을 생성하는 함수
// LPS: Longest proper Prefix which is also Suffix
// (자기 자신을 제외한 접두사 중, 접미사와 일치하는 가장 긴 것의 길이)
// 예: "abaca" -> lps[4]는 "abaca"의 접두사 "a", "ab", "aba", "abac" 중
//                접미사 "a", "ca", "aca", "baca"와 일치하는 가장 긴 "a"이므로 길이는 1.
// 예: "abab" -> lps[3]는 "abab"의 접두사 "ab"와 접미사 "ab"가 일치하므로 길이는 2.
vector<int> computeLPSArray(const string& pattern) {
    int patternLength = pattern.size();
    vector<int> lps(patternLength, 0); // lps 배열을 0으로 초기화

    // lps[0]은 항상 0이므로, i=1부터 시작.
    // length는 현재까지 일치한 접두사-접미사의 길이를 나타냄.
    int length = 0; 
    int i = 1;

    while (i < patternLength) {
        // case 1: 현재 문자가 접두사의 다음 문자와 일치하는 경우
        // 예: pattern = "ababa", i=2 (세번째 'a'), length=1 ('a'가 일치하는 상태)
        // pattern[i] ('a') 와 pattern[length] ('b')는 다름.
        // 예: pattern = "ababa", i=3 ('b'), length=2 ('ab'가 일치하는 상태)
        // pattern[i] ('b') 와 pattern[length] ('a')는 다름.
        if (pattern[i] == pattern[length]) {
            length++;       // 일치 길이를 1 증가
            lps[i] = length; // 현재 인덱스(i)의 lps 값을 갱신
            i++;            // 다음 문자로 이동
        } 
        // case 2: 일치하지 않는 경우
        else {
            // case 2-1: length가 0보다 큰 경우 (이전에 일치했던 부분이 있었음)
            // "되돌아갈 곳"이 있다는 의미.
            // lps 배열을 이용해, 이전 단계에서 일치했던 접두사의 lps 값을 가져와 length를 갱신.
            // 이 과정을 통해, 비교를 처음부터 다시 시작하지 않고 건너뛸 수 있음.
            // 예: pattern = "aaabaaa", i=6 ('a'), length=3 ("aaa")
            // pattern[6] ('a') != pattern[3] ('b') -> 불일치.
            // length = lps[length - 1] = lps[2] = 2. 이제 "aa"를 기준으로 다시 비교 시작.
            if (length != 0) {
                length = lps[length - 1];
            }
            // case 2-2: length가 0인 경우 (일치하는 접두사-접미사가 없음)
            // 더 이상 되돌아갈 곳이 없으므로, 현재 위치(i)의 lps 값은 0이 됨.
            else {
                lps[i] = 0;
                i++; // 다음 문자로 이동
            }
        }
    }
    return lps;
}

// KMP 알고리즘을 사용하여 텍스트에서 패턴을 검색하는 함수
vector<int> kmpSearch(const string& text, const string& pattern) {
    int textLength = text.size();
    int patternLength = pattern.size();

    // 1. 패턴에 대한 LPS 배열 생성
    vector<int> lps = computeLPSArray(pattern);
    vector<int> matchIndices; // 패턴이 일치하는 시작 인덱스들을 저장할 벡터

    int textIndex = 0;    // 텍스트를 순회하는 인덱스
    int patternIndex = 0; // 패턴을 순회하는 인덱스

    while (textIndex < textLength) {
        // case 1: 텍스트와 패턴의 문자가 일치하는 경우
        if (text[textIndex] == pattern[patternIndex]) {
            textIndex++;
            patternIndex++;
        }

        // case 1-1: 패턴의 끝까지 모두 일치한 경우 (패턴 발견!)
        if (patternIndex == patternLength) {
            // 패턴이 시작된 위치를 결과에 추가.
            // 현재 textIndex는 패턴이 끝난 위치의 바로 다음을 가리킴.
            // 따라서 (textIndex - patternLength)가 시작 위치.
            matchIndices.push_back(textIndex - patternLength);

            // 중요! 다음 탐색을 위해 patternIndex를 재설정.
            // lps 배열을 이용해, 이미 일치한 부분에 대한 정보를 활용하여 건너뜀.
            // 예: text="ababa", pattern="aba"일 때, 첫 "aba"를 찾은 후
            // patternIndex는 lps[2]=1이 되어, text의 3번째 문자('a')부터
            // pattern의 1번째 문자('b')를 비교하는 대신, pattern의 인덱스 1('b')부터 비교를 이어감.
            patternIndex = lps[patternIndex - 1];
        } 
        
        // case 2: 문자가 일치하지 않는 경우
        else if (textIndex < textLength && text[textIndex] != pattern[patternIndex]) {
            // case 2-1: patternIndex가 0보다 크다면, 이전에 일치했던 부분이 있음.
            // lps 배열을 참고하여 patternIndex를 "점프"시킴.
            // 텍스트 인덱스는 그대로 두고, 패턴만 오른쪽으로 효율적으로 이동시키는 효과.
            if (patternIndex != 0) {
                patternIndex = lps[patternIndex - 1];
            } 
            // case 2-2: patternIndex가 0이라면, 첫 문자부터 불일치.
            // 단순하게 텍스트의 다음 문자로 이동.
            else {
                textIndex++;
            }
        }
    }
    return matchIndices;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text = "ABABABACABABABCABABABC";
    string pattern = "ABACABAB";

    vector<int> matches = kmpSearch(text, pattern);

    cout << "패턴(" << pattern << ")이 나타난 위치 (0-based index): ";
    for (int idx : matches) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}