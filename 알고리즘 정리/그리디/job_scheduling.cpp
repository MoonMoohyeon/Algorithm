#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <climits>
using namespace std;

priority_queue<pair<int, int>> pq;

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /*
        Job Scheduling
        1. 끝나는 시간으로 정렬한다.
        2. 빨리 끝나는 일부터 선택한다.
        3. 겹치는 경우 선택하지 않는다.

        불변속성 증명
        알고리즘이 만드는 스케줄을 A(탐욕해), 정답을 S(최적해)라고 하자.
        i번쨰 선택 이후에 i 선택 이전의 일들은 A와 S에서 같은 위치에 존재한다. (Base)
        알고리즘이 i+1번째 일을 선택하지 않은 경우 -> 선택할 수 없는 경우로 S에도 존재 하지 않는다.
        알고리즘이 i+1번째 일을 선택한 경우 -> 
        S에 존재한다. -> 문제가 없다. *최적해와 같음.

        #최적해와 다른 경우는 없다는 것을 보인다.
        S에 존재하지 않는다. -> S-A에서 끝나는 시간이 가장 빠른 일과 교환한다.
        A가 선택한 일(t)과 S-A에서 가져온 일(n)을 비교했을 때,
        t의 종료 시간은 n의 종료 시간보다 같거나 작다. -> A가 종료 시간이 빠른 것부터 선택하기 때문이다.
        t는 종료 시간이 가장 빠른 일이기 때문에, 이전 선택의 종료 시간과 그 사이에 다른 일이 존재할 수 없다.
        따라서 교환이 가능하고 t의 시작 시간이 n보다 빠른 경우 교환에 문제가 없다.
    */

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        pq.push({ -b,a }); // 종료시간, 시작시간
    }

    int time, cnt;
    time = cnt = 0;
    while (!pq.empty()) {
        int end = -pq.top().first;
        int start = pq.top().second;
        pq.pop();
        if (start < time) continue; // 시작 시간이 이전 끝나는 시간보다 빠르므로 겹치는 경우
        else {
            cnt++;
            time = end; // 선택하고 이전 끝나는 시간을 갱신한다.
        }
    }

    cout << cnt;

    return 0;
}