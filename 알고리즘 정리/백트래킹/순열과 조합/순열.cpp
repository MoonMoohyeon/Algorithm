#include <iostream>
#include <vector>
using namespace std;

/*
    1부터 N까지 자연수 중 중복 없이 M개를 고른 수열 (순열 nPr)
    사전 순으로 증가하는 순서로 출력한다.
    
    코딩테스트 표준 패턴:
    - visited[i] 배열로 이미 선택된 숫자인지 O(1)에 확인
    - selected 배열(또는 vector)에 현재 선택한 숫자들을 담고 백트래킹
*/

int N, M;
int visited[10] = {0,};
int selected[10] = {0,};

void NM(int cnt) {
    // M개를 모두 선택했으면 출력
    if (cnt == M) {
        for (int i = 0; i < M; i++) {
            cout << selected[i] << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = 1; i <= N; i++) {
        if (visited[i]) continue; // 이미 선택한 숫자 건너뛰기

        visited[i] = 1;
        selected[cnt] = i;

        NM(cnt + 1); // 다음 자리 선택

        // 백트래킹 (원상복구)
        visited[i] = 0;
        selected[cnt] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    NM(0);

    return 0;
}