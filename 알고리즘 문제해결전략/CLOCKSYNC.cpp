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

int C;
int clocks[17];

int sw[11][17] = {
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1},
    {1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1},
    {0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0}
};

int check12() {
    int cnt = 0;
    for (int i = 0; i < 16; i++) {
        if (clocks[i] == 12) cnt++;
    }

    if (cnt == 16) return 1;
    return 0;
}

void pushsw(int swnum) {
    for (int i = 0; i < 16; i++) {
        if (sw[swnum][i] == 1) {
            if (clocks[i] == 12) {
                clocks[i] = 3;
            }
            else {
                clocks[i] += 3;
            }
        }
    }
}

int ans = 10e8;
void solve(int sw, int push) { // 현재까지의 스위치, 현재까지 스위치를 누른 횟수의 합
    if (push >= ans) {
        return;
    }

    if (sw >= 10) {
        if (check12()) {
            if (push < ans) {
                ans = push;
            }
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        solve(sw + 1, push + i);
        pushsw(sw);
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    /*
        모든 시계가 12시인지 체크하는 함수
        스위치를 눌렀을 때 연결된 시계들을 +3시간 이동하는 함수
        4^10만큼 완전탐색하는 함수
    */

    cin >> C;
    for (int t = 1; t <= C; t++) {
        for (int i = 0; i < 16; i++) {
            cin >> clocks[i];
        }
        ans = 10e8;
        solve(0, 0);

        if (ans == 10e8) cout << "-1\n";
        else cout << ans << "\n";
    }


    return 0;
}
