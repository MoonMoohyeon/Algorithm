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

int C, H, W;
char map[21][21];

pair<int,int> block_type[4][2] = { // ㄴ ㄱ
    {{1,0}, {1,1}}, // ㄴ
    {{1,-1}, {1,0}}, // ㄴ 대칭
    {{0,1}, {1,1}}, // ㄱ
    {{0,1}, {1,0}} // ㄱ 대칭
};

int isinbound(int y, int x) {
    if(y<0 || x<0 || y>=H || x>=W) return 0;
    return 1;
}

int ans = 0;
int blockmatching(int cur_block_num, int goal_block_num, int y, int x) {
    // 현재 블록 개수가 목표치에 도달하면 카운트를 1 늘리고 종료한다.
    if(cur_block_num >= goal_block_num) {
        ans++;
        return 1;
    }
    if(y >= H && x >= W) { // 블록을 목표한 만큼 놓지 못하고 맵 끝까지 탐색한 경우 놓을 수 없는 상태로 종료한다.
        return 0;
    }

    int blockcount = cur_block_num;
    if(map[y][x] == '.') {
        // 블록을 놓을 수 있는지 확인
        for(int k=0; k<4; k++) {
            pair<int,int> a, b;
            a = block_type[k][0];
            b = block_type[k][1];

            // 놓을 수 있는 경우 맵 상태를 변경하고 카운트를 1 늘린 후, 좌표를 변경하여 재귀 호출
            // 재귀 호출이 끝나면 백트래킹
            if(isinbound(y + a.first, x + a.second) && isinbound(y + b.first, x + b.second)) {
                if(map[y + a.first][x + a.second] == '.' && map[y + b.first][x + b.second] == '.') {
                    map[y][x] = '@';
                    map[y + a.first][x + a.second] = '@';
                    map[y + b.first][x + b.second] = '@';
                    blockcount++;
                    if(x < W) {
                        blockmatching(blockcount, goal_block_num, y, x + 1);
                    }
                    else {
                        x = 0;
                        blockmatching(blockcount, goal_block_num, y + 1, x);
                    }
                    map[y][x] = '.';
                    map[y + a.first][x + a.second] = '.';
                    map[y + b.first][x + b.second] = '.';
                    blockcount--;
                }
            }
        }
    }
    else { // 매칭이 안 된 경우 카운트를 늘리지 않고 좌표만 변경하여 재귀 호출
        if(x < W) {
            blockmatching(blockcount, goal_block_num, y, x + 1);
        }
        else {
            x = 0;
            blockmatching(blockcount, goal_block_num, y + 1, x);
        }
    }

    return 0;
}

    /*
        맵의 좌상단부터 블록을 매칭한다. (회전하는 경우 4가지)
        블록을 1개 놓는다. -> 블록이 빈칸/3개가 놓일 때까지 재귀로 탐색한다.
        블록이 빈칸/3개가 놓였을 때, 검사(모든 빈 칸이 채워졌는지)하여 채워진 경우 가짓수를 1 늘린다.
        탐색이 끝난 후 가짓수가 정답.
        블록을 놓을 때는 항상 4가지 회전을 고려하여 4번 호출한다.

        좌상단부터 빈 칸이 있으면 블록을 놓을 수 있는지 검사한다.
        놓을 수 있으면 블록을 놓고, 블록이 놓인 상태의 맵과 함께 다음 블록을 놓도록 재귀 호출한다.
        (필요 블록수 - 1, 맵에서 블록이 놓인 공간을 채움)
    */

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    for(int t=1; t<=C; t++) {
        cin >> H >> W;
        for(int i=0; i<H; i++) {
            cin >> map[i];
        }

        ans = 0;
        int vacant_size = 0;
        for(int i=0; i<H; i++) {
            for(int j=0; j<W; j++) {
                if(map[i][j] == '.') {
                    vacant_size++;
                }
            }
        }

        if(vacant_size % 3 != 0) {
            cout << "0\n";
            continue;
        } 
        else {
            blockmatching(0, vacant_size / 3, 0, 0); // 현재까지 놓은 블록의 수, 모든 빈 칸을 채우기 위해 필요한 블록의 개수, 다음 탐색 위치
        }

        cout << ans << "\n";
    }

    return 0;
}