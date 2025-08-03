#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> computeLPSArray(const string& pattern) {
    int patternLength = pattern.size();
    vector<int> lps(patternLength, 0);
    int length = 0; 
    int i = 1;

    while (i < patternLength) {
        // case 1: 현재 문자가 접두사의 다음 문자와 일치하는 경우
        if (pattern[i] == pattern[length]) {
            length++;       // 일치 길이를 1 증가
            lps[i] = length; // 현재 인덱스(i)의 lps 값을 갱신
            i++;            // 다음 문자로 이동
        } 
        // case 2: 일치하지 않는 경우
        else {
            // case 2-1: length가 0보다 큰 경우 (이전에 일치했던 부분이 있었음)
            if (length != 0) {
                length = lps[length - 1];
            }
            // case 2-2: length가 0인 경우 (일치하는 접두사-접미사가 없음)
            else {
                lps[i] = 0;
                i++; // 다음 문자로 이동
            }
        }
    }
    return lps;
}

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
            matchIndices.push_back(textIndex - patternLength);
            patternIndex = lps[patternIndex - 1];
        } 
        
        // case 2: 문자가 일치하지 않는 경우
        else if (textIndex < textLength && text[textIndex] != pattern[patternIndex]) {
            // case 2-1: patternIndex가 0보다 크다면, 이전에 일치했던 부분이 있음.
            if (patternIndex != 0) {
                patternIndex = lps[patternIndex - 1];
            } 
            // case 2-2: patternIndex가 0이라면, 첫 문자부터 불일치.
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