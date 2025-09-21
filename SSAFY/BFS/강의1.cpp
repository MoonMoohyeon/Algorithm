#include <iostream>
#include <queue>
using namespace std;

/*
    그래프에서 한 분기점을 기준으로 넓게 퍼져나가면서 모든 노드를 탐색하는 완전탐색
*/

vector<int> alis[11];
int visited[11];
int N, M;

/*
    대기열 준비
    시작노드 큐에 등록
    큐가 비기 전까지
    맨 앞노드 확인 및 추출(now)
    다음 next 후보 찾기
    next를 대기열에 등록
*/
void BFS(int start) {
    queue<int> q;
    visited[start] = 1;
    q.push(start);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        cout << now;
        for(int i=0; i<alis[now].size(); i++) {
            int next = alis[now][i];
            if(visited[next] == 1) continue;
            visited[next] = 1;
            q.push(next);
        }
    }
}

int mat[11][11];

void BFS2(int start) {
    queue<int> q;
    q.push(start);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        cout << now << " ";
        for(int i=1; i<=N; i++) {
            if(mat[now][i] == 1) {
                q.push(mat[now][i]);
            }
        }
    }
}

// visited에 시작 노드 기준 몇 번만에 갈 수 있는지 기록하기
void BFS3(int start) {
    queue<int> q;
    for(int i=0; i<=N; i++) {
        visited[i] = -1;
    }
    visited[start] = 0;
    q.push(start);

    while(!q.empty()) {
        int now = q.front();
        q.pop();
        cout << now << " ";
        for(int i=0; i<alis[now].size(); i++) {
            int next = alis[now][i];
            if(visited[next] != -1) continue;
            visited[next] = visited[now] + 1;
            q.push(next);
        }
    }

    for(int i=1; i<=N; i++) {
        cout << "[]" << i << "] " << visited[i] << "\n";
    }
}

// start -> dest 몇 번만에 갈 수 있는지 쿼리 형태로 처리하기
int BFS4(int start, int dest) {
    queue<int> q;
    for(int i=0; i<=N; i++) {
        visited[i] = -1;
    }
    visited[start] = 0;
    q.push(start);

    while(!q.empty()) {
        int now = q.front();
        q.pop();
        if(now == dest) {
            cout << visited[now] << " ";
        }
        // cout << now << " ";
        for(int i=0; i<alis[now].size(); i++) {
            int next = alis[now][i];
            if(visited[next] != -1) continue;
            visited[next] = visited[now] + 1;
            q.push(next);
        }
    }

    for(int i=1; i<=N; i++) {
        cout << "[]" << i << "] " << visited[i] << "\n";
    }
}

int main() {
    queue<int> q;
    
    q.push(1);
    q.push(3);
    q.push(5);
    q.push(7);

    cout << q.front() << " ";
    q.pop();
    cout << "\n";
    cout << q.empty() << " ";

    while(!q.empty()) {
        int node = q.front();
        cout << node << " ";
        q.pop();
    }

    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int from, to;
        cin >> from >> to;
        alis[from].push_back(to);
        alis[to].push_back(from);
    }

        for(int i=0; i<M; i++) {
        int from, to;
        cin >> from >> to;
        mat[from][to] = 1;
    }

    int Q;
    cin >> Q;
    for(int i=0; i<Q; i++) {
        int a, b;
        cin >> a >> b;
        int ans = BFS4(a, b);
        cout << ans << "\n";
    }

    return 0;
}