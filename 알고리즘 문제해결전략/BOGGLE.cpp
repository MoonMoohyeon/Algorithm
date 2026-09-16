#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

char board[6][6];
int C, W;
string words[11];

// 8방향 이동 벡터 (상, 하, 좌, 우 및 4개 대각선)
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// memoization 캐시: cache[y][x][idx] -> (y, x) 위치에서 word[idx]부터 끝까지 완성할 수 있는가? (-1: 미방문, 0: 불가, 1: 가능)
int cache[6][6][11];

bool inRange(int y, int x) {
    return y >= 0 && y < 5 && x >= 0 && x < 5;
}

// (y, x) 위치의 문자가 word[idx]와 일치할 때, 남은 단어를 완성할 수 있는지 판별
bool hasWord(const string& word, int y, int x, int idx) {
    // 1. 기저 사례: 보드 밖으로 벗어난 경우
    if (!inRange(y, x)) return false;
    // 2. 기저 사례: 첫 글자가 일치하지 않는 경우
    if (board[y][x] != word[idx]) return false;
    // 3. 기저 사례: 단어의 마지막 글자까지 모두 일치한 경우
    if (idx == (int)word.length() - 1) return true;

    // 4. 메모이제이션 확인
    int& ret = cache[y][x][idx];
    if (ret != -1) return ret;

    // 5. 8방향으로 다음 글자 탐색
    for (int dir = 0; dir < 8; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (hasWord(word, ny, nx, idx + 1)) {
            return ret = 1;
        }
    }

    return ret = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> C;
    while (C--) {
        for (int i = 0; i < 5; i++) {
            cin >> board[i];
        }

        cin >> W;
        for (int i = 0; i < W; i++) {
            cin >> words[i];
        }

        for (int w = 0; w < W; w++) {
            memset(cache, -1, sizeof(cache));
            bool found = false;

            // 5x5 보드의 모든 시작 위치에 대해 탐색
            for (int i = 0; i < 5 && !found; i++) {
                for (int j = 0; j < 5 && !found; j++) {
                    if (hasWord(words[w], i, j, 0)) {
                        found = true;
                    }
                }
            }

            cout << words[w] << " " << (found ? "YES" : "NO") << "\n";
        }
    }

    return 0;
}