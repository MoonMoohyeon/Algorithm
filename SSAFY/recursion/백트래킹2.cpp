#include <iostream>
using namespace std;

/*
    중복 순열 - 순서 고려, N개 중 r개를 뽑는 경우
    순열 - 서로 다른 N개 중에서 r개를 뽑는 경우, 중복 방문 처리 필요
    중복 조합 - 중복 가능한 N개 중에서 r개를 뽑는 경우
    조합 - 현재 선택은 이전 선택보다 커야 함.
*/

int N;
int cnt;
int path[10];
int used[10];


void func(int now) {
    if(now >= N) {
        cnt++;
        for(int i=0; i<N; i++) {
            cout << path[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1; i<=6; i++) {
        path[now] = i;
        func(now+1);
        path[now] = 0;
    }
}

void func2(int now) {
    if(now >= N) {
        cnt++;
        for(int i=0; i<N; i++) {
            cout << path[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1; i<=6; i++) {
        if(used[i]) continue;
        path[now] = i;
        used[i] = 1;
        func(now+1);
        path[now] = 0;
        used[i] = 0;
    }
}

void func3(int now) {
        if(now >= N) {
        cnt++;
        for(int i=0; i<N; i++) {
            cout << path[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1; i<=6; i++) {
        if(now > 0 && path[now - 1] > i) continue;
        path[now] = i;
        func(now+1);
        path[now] = 0;
    }
}

void func4(int now, int start) {
    if(now >= N) {
        for(int i=0; i<N; i++) {
            cout << path[i] << " ";
        }
        cout << "\n";
        cnt++;
        return;

        
    }

    for(int i=start; i<=6;i++) {
        path[now] = i;
        func4(now+1, i);
        path[now] = 0;
    }

}


int main() {
    cin >> N;
    func(0);
}