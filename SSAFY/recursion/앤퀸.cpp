#include <iostream>
using namespace std;

int N;
int group1[20][20]; // 좌하방향 대각선 저장용
int group2[20][20]; // 우하방향 대각선 저장용
// R++, C-- 라인번호 : R + C
void makeGroup(int row, int col) {
    while(1) {
        if(row >= N || col <0) return;
        group1[row][col] = row + col;
        row++;
        col--;
    }
}

void makeGroup2(int row, int col) {
    while(1) {
        if(row >= N || col <0) return;
        // R++, C++ 라인번호 : R - C + N
        group2[row][col] = row + col;
        row++;
        col--;
    }
}

int ans = 0;
int used1[20]; // 좌하방향 대각선 체크, 인덱스 : 좌하방향 대각선 라인 번호, value : 사용 여부
void func(int row) {
    if(row >= N) {
        ans++;
        return;
    }
    
    for(int col =0; col<N; col++) {
        if(used1[group1[row][col]] == 1) continue;
        used1[group1[row][col]] =1;
        func(row + 1);
    }
}

int main(void) {
    cin >> N;

    for(int row = 0; row<N; row++) {
        for(int col = 0; col < N; col++) {
            if(group1[row][col] == 0) {
                makeGroup(row,col);
            }
        }
    }

    for(int row = 0; row<N; row++) {
        for(int col = 0; col < N; col++) {
            if(group2[row][col] == 0) {
                makeGroup2(row,col);
            }
        }
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout <<group1[i][j] << " ";
        }
        cout << "\n";
    }
}