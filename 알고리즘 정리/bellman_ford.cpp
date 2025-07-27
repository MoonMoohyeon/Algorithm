#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

struct Edge {
    int from, to, weight;
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

bool bellmanFord(int start, int V, const vector<Edge>& edges, vector<int>& dist) {
    dist.assign(V + 1, INF);
    dist[start] = 0;

    // V-1번 모든 간선 relaxation
    for (int i = 1; i < V; ++i) {
        for (const Edge& edge : edges) {
            if (dist[edge.from] != INF && dist[edge.to] > dist[edge.from] + edge.weight) {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }

    // 음수 사이클 검사
    for (const Edge& edge : edges) {
        if (dist[edge.from] != INF && dist[edge.to] > dist[edge.from] + edge.weight) {
            return false; // 음수 사이클 존재
        }
    }

    return true; // 정상 종료
}

int main() {
    int V = 5; // 정점 개수
    int E = 7; // 간선 개수
    int start = 1;

    vector<Edge> edges;

    // 간선 추가 (단방향)
    edges.push_back(Edge(1, 2, 4));
    edges.push_back(Edge(1, 3, 2));
    edges.push_back(Edge(2, 3, -1));
    edges.push_back(Edge(2, 4, 2));
    edges.push_back(Edge(3, 5, 3));
    edges.push_back(Edge(4, 5, -3));
    edges.push_back(Edge(5, 4, 1)); // 이 간선이 없다면 음수 사이클 없음

    vector<int> dist;
    bool noNegativeCycle = bellmanFord(start, V, edges, dist);

    if (noNegativeCycle) {
        cout << "시작 정점 " << start << "로부터의 최단 거리:" << endl;
        for (int i = 1; i <= V; ++i) {
            if (dist[i] == INF) cout << i << ": 도달 불가" << endl;
            else cout << i << ": " << dist[i] << endl;
        }
    } else {
        cout << "음수 사이클이 존재합니다." << endl;
    }

    return 0;
}
