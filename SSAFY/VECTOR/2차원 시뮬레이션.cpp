#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;

int N, M, K;
char map[21][21];
int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };

int checkbound(int y, int x) {
    if (x < 0 || y < 0 || x >= M || y >= N) return 0;
    return 1;
}

int iswall(int y, int x) {
    if (map[y][x] == '#') return 1;
    return 0;
}

void boom(int y, int x) {
    if(map[y][x] == '_') map[y][x] = '%';
}

void simul() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == '@') { // 맵에서 폭탄이면
                for (int k = 0; k < 4; k++) { // 4방향 탐색
                    for (int c = 1; c <= K; c++) { // 폭탄 범위
                        int ny = i + dy[k] * c;
                        int nx = j + dx[k] * c;
                        if (checkbound(ny, nx)) {
                            if (iswall(ny, nx)) break;
                            boom(ny, nx);
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    simul();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == '@') map[i][j] = '%';
            cout << map[i][j];
        }
        cout << "\n";
    }

    return 0;
}