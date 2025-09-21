#include <iostream>
using namespace std;

/*
    백트래킹
    해당 경로의 가망성을 판단하고 가망성이 없으면 들어가지 않음
*/

int path[10];

void func(int now) {
    if(now >= 3) {
        for(int i=0; i<3; i++) {
            cout << path[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1; i<=6; i++) {
        if(now > 0) {
            if(path[now = 1] - i == 1 || path[now -1] == -1) {
                continue; // 인접하는 경우가 +- 1차이인 경우는 뽑지 않는다.
            }
            path[now] = i;
            func(now + 1);
            path[now] = 0;
        }
    }
}


int used[7];
// 같은 숫자는 뽑지 않는다.
void func2(int now) {
    if(now >= 3) {
        for(int i=0; i<3; i++) {
            cout << path[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1; i<=6; i++) {
        path[now] = i;
        used[i] = 1;
        func2(now + 1);
        path[now] = 0;
        used[i] = 0;
    }
}

char board[4][5];
// 체스판 룩 배치하기
void func3(int row) {
    // 기저조건 N == 4
    if(row >= 4) {
        int de = -1;
        return;
    }

    for(int col = 0; col<4; col++) {
        board[row][col] = '#';
        func3(row+1);
        board[row][col] = 0;
    }
}

// 특정 N 값이 주어졌을 때 1,2,3을 활용해서 N값을 만들 수 있는 경우의 수는 몇 가지인가?
int N;
string path;
void func4(int num, string path) {
    // 기저 조건
    if(num == N) {
        cout << path << "\n";
        return;
    }

    func4(num + 1, path + "1");
    func4(num + 2, path + "2");
    func4(num + 3, path + "3");
}

int main() {
    func(0);
}