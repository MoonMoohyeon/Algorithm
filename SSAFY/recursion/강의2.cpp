#include <iostream>
#include <vector>
using namespace std;

int visited[7] = {0,};
vector<int> selected;

/*
    백트래킹 + 시뮬레이션
    만들어낼 수 있는 경우를 모두 뽑아보고,
    맵 정보와 같이 활용될 때 일부를 변경
    Copy 배열
*/

int path[10]; // index: 현재 번째, value: 선택한 눈금
int sum = 0;
void dice(int now) {
    if(now >= 3) { // 기저 조건
        // 출력
        for(int i=0; i<3; i++) {
            cout << path[i] << " ";
        }
        cout << " = " << sum << "\n";
        return;
    }

    for(int i=1; i<=6; i++) {
        // 전진 실행
        path[now] = i;
        sum += i;
        dice(now+1);
        // 후진 실행
        path[now] = 0;
        sum -= i;
    }
}

void func(int now, int sum) {
    // 기저 조건
    if(now >= 3) { // 기저 조건
        // 출력
        for(int i=0; i<3; i++) {
            cout << path[i] << " ";
        }
        cout << " = " << sum << "\n";
        return;
    }

    // 재귀 기본
    for(int i=1; i<=6; i++) {
        path[now] = i;
        func(now+1, sum+i);
        path[now] = 0;
    }
}

int main() {
    dice(0);
    func(0,0);
}