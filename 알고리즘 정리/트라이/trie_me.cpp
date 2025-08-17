#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <climits>
using namespace std;

const int MAX_NODES = 5000005;
const int ALPHABET_SIZE = 26;

int N, M;

int trie[MAX_NODES][ALPHABET_SIZE];
bool is_end[MAX_NODES];
int node_count;

void init() {
    memset(trie, 0, sizeof(trie));
    memset(is_end, false, sizeof(is_end));
    node_count = 1;
}

void insert(string& str) {
    int current_node = 0;

    for (int i = 0; i < str.size(); i++) {
        int c = str[i] - 'a';

        if (trie[current_node][c] == 0) { // 현재 노드에서 다음 문자로 가는 경로가 없는 경우
            trie[current_node][c] = node_count++; // 새로 생성한다.
        }

        current_node = trie[current_node][c]; // 있으면 노드를 타고 내려가 이동한다.
    }

    is_end[current_node] = true; // 문자열의 끝에 도달했음을 표시한다.
}

bool search(string& str) {
    int current_node = 0;

    for (int i = 0; i < str.size(); i++) {
        int c = str[i] - 'a';

        if (trie[current_node][c] == 0) { // 다음 문자로 가는 경로가 없는 경우 트라이에 없는 것.
            return false;
        }

        current_node = trie[current_node][c]; // 있으면 노드를 타고 내려간다.
    }

    //return is_end[current_node]; // 끝까지 도달했을 때, 단어의 끝 플래그가 있는 경우 단어를 찾은 것
    
    return true; // 접두사가 일치하는 것을 찾는 문제이므로 수정
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    init();
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        insert(str);
    }

    int cnt = 0;
    for (int i = 0; i < M; i++) {
        string str;
        cin >> str;
        if (search(str) == true) {
            cnt++;
        }
    }

    cout << cnt;

    return 0;
}
