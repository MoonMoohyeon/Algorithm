#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

/*
===================================================================
 [트라이 (Trie / Prefix Tree) 템플릿]
 
 특징: 문자열 삽입/검색 O(L) (L = 문자열 길이)
 메모리 설정 주의:
   - MAX_NODES = (최대 단어 개수 * 최대 단어 길이) + 1
   - 예: 단어 10,000개, 길이 10글자 -> MAX_NODES = 100,005 (약 10MB)
   - 500만 크기 배열을 잡으면 500MB를 초과하여 메모리 초과(MLE) 발생하므로
     문제의 N * L 제약 조건에 맞춰 크기를 적절히 조절해야 합니다.
===================================================================
*/

const int MAX_NODES = 100005;
const int ALPHABET_SIZE = 26;

int trie[MAX_NODES][ALPHABET_SIZE];
bool is_end[MAX_NODES];
int node_count = 1; // 0번 노드는 루트 노드

// 테스트케이스가 여러 개일 때 초기화 함수
void init() {
    for (int i = 0; i < node_count; i++) {
        memset(trie[i], 0, sizeof(trie[i]));
        is_end[i] = false;
    }
    node_count = 1;
}

// 문자열 삽입 함수
void insert(const string& str) {
    int cur = 0; // 루트에서 시작
    for (char ch : str) {
        int c = ch - 'a';
        if (trie[cur][c] == 0) {
            trie[cur][c] = node_count++;
        }
        cur = trie[cur][c];
    }
    is_end[cur] = true; // 단어 끝 표시
}

// 완전 일치 검색 함수 (해당 단어가 완전히 등록되어 있는가?)
bool search(const string& str) {
    int cur = 0;
    for (char ch : str) {
        int c = ch - 'a';
        if (trie[cur][c] == 0) return false;
        cur = trie[cur][c];
    }
    return is_end[cur];
}

// 접두사 검색 함수 (해당 문자열로 시작하는 단어가 존재하는가?)
bool startsWith(const string& prefix) {
    int cur = 0;
    for (char ch : prefix) {
        int c = ch - 'a';
        if (trie[cur][c] == 0) return false;
        cur = trie[cur][c];
    }
    return true; // 경로만 존재하면 접두사 만족
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    // 단어 사전에 등록
    insert("apple");
    insert("apply");
    insert("banana");
    insert("ban");

    cout << boolalpha;
    cout << "--- [Trie 검색 테스트] ---\n";
    cout << "search('apple'): " << search("apple") << "\n";     // true
    cout << "search('app'): " << search("app") << "\n";         // false (단어 끝 아님)
    cout << "startsWith('app'): " << startsWith("app") << "\n"; // true (apple, apply의 접두사)
    cout << "search('ban'): " << search("ban") << "\n";         // true
    cout << "search('band'): " << search("band") << "\n";       // false

    return 0;
}
