#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;

int N;
int M;

int visited[9] = {0,};
int selected[9] = {0,};

    /*
        N개의 자연수 중 M개를 중복 없이 고른 수열을 출력

        param
        cnt(현재까지 고른 개수), selected배열(현재까지 고른 숫자들)
        전역변수
        현재까지 방문한 숫자를 저장하는 배열

        1. cnt = M개가 되면 출력하고 반환
        2. cnt < M이면 N개의 자연수 중에서 하나를 선택(중복인 경우 제외한다)
        3. i번째 호출이 끝나면 해당 숫자에서 만들 수 있는 조합을 모두 선택한 것이므로
        4. i+1로 시작 지점을 옮긴다.
        5. 재귀 호출
    

        3 2

        1 2
        1 3
        2 1
        2 3
        3 1
        3 2

        1 2
        1 3
        2 3
    */

int NM(int cnt, int start) {
    if(cnt == M) {
        for(int i=0; i<M; i++) {
            if(selected[i]) {
                cout << selected[i] << " ";
            }
        }
        cout << "\n";
        return 1;
    }

    for(int i = start; i <=N; i++) {
        if(visited[i]) {
            continue;
        }

        visited[i] = 1;
        selected[cnt] = i;
        NM(cnt+1, i+1);
        visited[i] = 0;
        selected[cnt] = 0;
    }


    return 0;
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    NM(0, 1);


    return 0;
}