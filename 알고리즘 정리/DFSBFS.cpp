#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

/*
===================================================================
 [그래프 탐색: DFS & BFS 표준 템플릿 (인접 리스트)]
 
 - DFS (깊이 우선 탐색): 재귀 함수 호출 스택 활용 (경로 탐색, 사이클 찾기)
 - BFS (너비 우선 탐색): 큐(queue) 활용 (최단 거리, 레벨별 탐색)
 
 핵심 주의사항:
 1. "작은 번호의 노드부터 방문" 조건이 있으면 각 인접 리스트를 미리 sort()!
 2. BFS에서 visited 처리는 반드시 "큐에 push할 때" 수행 (중복 push로 인한 TLE 방지)!
===================================================================
*/

const int MAX = 1005;
vector<int> adj[MAX];
bool visited[MAX];
int N, M, V; // N: 정점 개수, M: 간선 개수, V: 시작 정점

// 1. 깊이 우선 탐색 (DFS)
void dfs(int cur) {
    visited[cur] = true;
    cout << cur << " ";

    for (int next : adj[cur]) {
        if (!visited[next]) {
            dfs(next);
        }
    }
}

// 2. 너비 우선 탐색 (BFS)
void bfs(int start) {
    memset(visited, false, sizeof(visited)); // 방문 배열 초기화
    queue<int> q;

    q.push(start);
    visited[start] = true; // ★ push 할 때 방문 처리!

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " ";

        for (int next : adj[cur]) {
            if (!visited[next]) {
                visited[next] = true; // ★ push 할 때 방문 처리!
                q.push(next);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 예시 데이터 설정 (BOJ 1260 형식)
    // 정점 4개, 간선 5개, 시작점 1번
    N = 4; M = 5; V = 1;
    vector<pair<int, int>> edges = {
        {1, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}
    };

    for (auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adj[u].push_back(v);
        adj[v].push_back(u); // 양방향 간선
    }

    // 번호가 작은 노드부터 방문하도록 오름차순 정렬
    for (int i = 1; i <= N; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    cout << "DFS: ";
    memset(visited, false, sizeof(visited));
    dfs(V);
    cout << "\n";

    cout << "BFS: ";
    bfs(V);
    cout << "\n";

    return 0;
}
