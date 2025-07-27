#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// {가중치, 연결된 정점} 형태로 간선 정보를 저장하기 위한 pair
typedef pair<int, int> Edge;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E; // V: 정점의 개수, E: 간선의 개수
    cout << "정점의 개수와 간선의 개수를 입력하세요: ";
    cin >> V >> E;

    // 인접 리스트로 그래프 표현. adj[i]는 i번 정점과 연결된 간선들의 목록
    vector<vector<Edge>> adj(V + 1);
    // 방문 여부를 확인할 배열
    vector<bool> visited(V + 1, false);

    cout << E << "개의 간선 정보를 (정점1 정점2 가중치) 형태로 입력하세요:\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        // 양방향 그래프이므로 양쪽 정점에 모두 간선 정보 추가
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    // --- 프림 알고리즘 시작 ---
    // 1. 우선순위 큐(최소 힙) 선언. {가중치, 정점} 순으로 저장.
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    long long mst_cost = 0; // 최소 신장 트리의 총 가중치
    int edges_count = 0;    // MST에 포함된 간선의 개수

    // 2. 임의의 정점(1번)에서 시작.
    visited[1] = true;
    // 1번 정점과 연결된 모든 간선을 우선순위 큐에 추가
    for (auto& edge : adj[1]) {
        pq.push(edge);
    }

    // 3. MST를 구성할 때까지 반복 (V-1개의 간선을 찾을 때까지)
    while (!pq.empty() && edges_count < V - 1) {
        // 4. 현재 추가 가능한 간선 중 가장 가중치가 작은 간선을 선택
        Edge current_edge = pq.top();
        pq.pop();

        int weight = current_edge.first;
        int next_node = current_edge.second;

        // 5. 간선이 연결하는 정점이 이미 방문한 곳이면 사이클이 되므로 무시
        if (visited[next_node]) {
            continue;
        }

        // 6. 방문하지 않은 정점이라면 MST에 추가
        visited[next_node] = true; // 방문 처리
        mst_cost += weight;        // 가중치 누적
        edges_count++;             // 간선 개수 증가

        // 7. 새로 추가된 정점과 연결된 모든 간선을 우선순위 큐에 추가
        for (auto& edge : adj[next_node]) {
            if (!visited[edge.second]) {
                pq.push(edge);
            }
        }
    }

    cout << "\n최소 신장 트리의 총 가중치: " << mst_cost << endl;

    return 0;
}