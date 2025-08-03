#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int arr[4][4] = { 0, };
int dx[8] = { 1,-1,1,-1,0,0,-1,1 };
int dy[8] = { 1,-1,-1,1,1,-1,0,0 };

int N, M;

int checkbound(int y, int x) {
    if (x < 0 || y < 0 || y >= N || x >= M) return 0;
    return 1;
}

// 2 * 3 크기의 사각형의 합을 구하기
int rectSum(int y, int x) {
    int rv = 0;
    for (int i = y; i < y+2; i++) {
        for (int j = x; j < x + 3; j++) {
            if (!checkbound(i, j)) return -1;
            rv += arr[i][j];
        }
    }
    return rv;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> arr[i][j];
        }
    }
    N = M = 4;

    int maxv = 0;
    int maxx, maxy;
    maxx = maxy = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int res = rectSum(i, j);
            if (res > maxv) {
                maxv = res;
                maxx = j;
                maxy = i;
            }
        }
    }

    cout << "(" << maxy << "," << maxx << ")";


    return 0;
}