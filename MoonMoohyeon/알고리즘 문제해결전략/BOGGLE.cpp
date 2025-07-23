#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;

char board[11][11] = { 0, };
int C, W;
string word[11];
bool check[11] = { false, };
int dx[8] = { 0,0,1,-1,-1,1,1,-1 };
int dy[8] = { 1,-1,0,0,-1,1,-1,1 };

int boggle(string target, int i, int j, int idx, int num) {
    if (target.length() == idx) {
        check[i] = true;
        return 1;
    }

    if (board[i][j] == target[idx]) {
        for (int k = 0; k < 8; k++) {
            boggle(target.substr(1, target.length()), i + dx[k], i + dy[k], idx + 1, num);
        }
    }
    else {
        return 0;
    }
}

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> C;
    int cnt = 0;
    while (true) {
        for(int i=0; i<11; i++) {
            word[i].erase();
            check[i] = false;
        }
        if (cnt == C) break;
        for (int i = 0; i < 5; i++) {
            cin >> board[i];
        }
        cin >> W;
        for (int i = 0; i < W; i++) {
            cin >> word[i];
        }

        int res = 0;
        for (int i = 0; i < W; i++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    res = boggle(word[i], j, k, 0, i);
                    if (res) goto br;
                }
            }
        br:;
        }
        for (int i = 0; i < W; i++) {
            if (check[i]) {
                cout << word[i] << " " << "YES\n";
            }
            else {
                cout << word[i] << " " << "NO\n";
            }
        }
        cnt++;
    }

    return 0;
}