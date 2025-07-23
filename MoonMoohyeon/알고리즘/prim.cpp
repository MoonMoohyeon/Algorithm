#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

// 간선 정보를 담는 구조체
struct Edge {
    int to;
    int weight;
    
    Edge(int t, int w) : to(t), weight(w) {}
    
    // 우선순위 큐에서 가중치가 작은 순으로 정렬되게 하기 위해 operator를 재정의
    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

int prim(int start, const vector<vector<Edge>>& graph, int V) {
    vector<bool> visited(V + 1, false);
    priority_queue<Edge> pq;
    int totalWeight = 0;

    pq.push(Edge(start, 0));

    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();

        int node = current.to;
        int weight = current.weight;

        if (visited[node]) continue;

        visited[node] = true;
        totalWeight += weight;

        for (const Edge& next : graph[node]) {
            if (!visited[next.to]) {
                pq.push(next);
            }
        }
    }

    return totalWeight;
}

int main() {
    int V = 5; // 정점 개수
    int E = 6; // 간선 개수

    vector<vector<Edge>> graph(V + 1);

    // 예시 간선 추가 (양방향 그래프)
    graph[1].push_back(Edge(2, 3));
    graph[2].push_back(Edge(1, 3));

    graph[1].push_back(Edge(3, 1));
    graph[3].push_back(Edge(1, 1));

    graph[2].push_back(Edge(3, 7));
    graph[3].push_back(Edge(2, 7));

    graph[2].push_back(Edge(4, 5));
    graph[4].push_back(Edge(2, 5));

    graph[3].push_back(Edge(4, 2));
    graph[4].push_back(Edge(3, 2));

    graph[4].push_back(Edge(5, 7));
    graph[5].push_back(Edge(4, 7));

    int mstWeight = prim(1, graph, V);
    cout << "최소 신장 트리의 가중치 합: " << mstWeight << endl;

    return 0;
}
