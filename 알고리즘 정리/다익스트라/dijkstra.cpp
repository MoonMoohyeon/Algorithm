#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/*
===================================================================
 [다익스트라 (Dijkstra) 최단 경로 알고리즘]
 
 조건: "음수 가중치가 없는" 그래프에서 단일 시작점 최단 경로
 시간 복잡도: O((V + E) log V)
 
 핵심 구현 포인트:
 1. min-heap 우선순위 큐 정의:
    방법 A (권장): priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
                   -> {거리, 노드번호} 형태로 오름차순 자동 정렬
    방법 B (음수 트릭): priority_queue<pair<int, int>> pq;
                   -> 거리에 -부호를 붙여서 max-heap을 min-heap처럼 사용
 2. 방문 검사 (가지치기):
    if (cur_dist > dist[cur_node]) continue;
    -> 이미 더 짧은 경로로 방문된 상태면 스킵 (시간 초과 방지 필수!)
===================================================================
*/

const int MAX = 100005;
const int INF = 1e9; // 또는 INT_MAX / 2 (오버플로우 방지)

int N, M; // N: 정점 개수, M: 간선 개수
vector<pair<int, int>> graph[MAX]; // graph[u] = {{가중치, 도착노드 v}, ...}
int dist[MAX];

// 방법 A: greater를 사용한 직관적인 최소 힙 다익스트라
void dijkstra(int start) {
    // 1. 거리 배열 초기화
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    // {누적 거리, 현재 노드} 오름차순 최소 힙
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        // [가지치기] 이미 처리된 거리보다 길다면 무시
        if (cur_dist > dist[cur_node]) continue;

        // 인접 노드 탐색
        for (auto& edge : graph[cur_node]) {
            int weight = edge.first;
            int next_node = edge.second;
            int next_dist = cur_dist + weight;

            // 더 짧은 경로를 발견한 경우 거리 갱신 및 큐에 삽입
            if (next_dist < dist[next_node]) {
                dist[next_node] = next_dist;
                pq.push({next_dist, next_node});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 예시: 5개 정점, 6개 간선 (1-based)
    N = 5; M = 6;
    int start_node = 1;

    // {가중치, 도착 노드}
    graph[1].push_back({2, 2});
    graph[1].push_back({3, 3});
    graph[2].push_back({4, 3});
    graph[2].push_back({5, 4});
    graph[3].push_back({6, 4});
    graph[4].push_back({1, 5});

    dijkstra(start_node);

    cout << "시작 정점 " << start_node << "로부터의 최단 거리:\n";
    for (int i = 1; i <= N; i++) {
        if (dist[i] == INF) cout << i << "번 노드: 도달 불가\n";
        else cout << i << "번 노드: " << dist[i] << "\n";
    }

    return 0;
}