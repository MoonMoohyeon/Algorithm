#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

int dijkstra(int start, int V, const vector<vector<Edge>>& graph) {
    vector<int> dist(V + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start}); // {거리, 노드}

    while (!pq.empty()) {
        int cost = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if (cost > dist[now]) continue;

        for (const Edge& next : graph[now]) {
            int nextDist = cost + next.weight;
            if (nextDist < dist[next.to]) {
                dist[next.to] = nextDist;
                pq.push({nextDist, next.to});
            }
        }
    }

    // 결과 출력 (for demonstration)
    cout << "시작 정점 " << start << "로부터의 최단 거리:" << endl;
    for (int i = 1; i <= V; ++i) {
        if (dist[i] == INF) cout << i << ": 도달 불가" << endl;
        else cout << i << ": " << dist[i] << endl;
    }

    return 0;
}

int main() {
    int V = 5; // 정점 개수
    int E = 6; // 간선 개수

    vector<vector<Edge>> graph(V + 1);

    // 방향 그래프 (from → to)
    graph[1].push_back(Edge(2, 2));
    graph[1].push_back(Edge(3, 3));
    graph[2].push_back(Edge(3, 4));
    graph[2].push_back(Edge(4, 5));
    graph[3].push_back(Edge(4, 6));
    graph[4].push_back(Edge(5, 1));

    int start = 1;
    dijkstra(start, V, graph);

    return 0;
}
