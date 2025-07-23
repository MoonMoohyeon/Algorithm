#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}

    // 정렬 시 가중치 오름차순으로
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<int> parent;

// 유니온 파인드 - find
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

// 유니온 파인드 - union
void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[b] = a;
}

int kruskal(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // 간선 가중치 기준으로 정렬

    parent.resize(V + 1);
    for (int i = 1; i <= V; ++i) parent[i] = i;

    int totalWeight = 0;
    for (const Edge& edge : edges) {
        if (find(edge.from) != find(edge.to)) {
            unite(edge.from, edge.to);
            totalWeight += edge.weight;
        }
    }

    return totalWeight;
}

int main() {
    int V = 5; // 정점 수
    int E = 6; // 간선 수

    vector<Edge> edges;

    // 간선 추가
    edges.push_back(Edge(1, 2, 3));
    edges.push_back(Edge(1, 3, 1));
    edges.push_back(Edge(2, 3, 7));
    edges.push_back(Edge(2, 4, 5));
    edges.push_back(Edge(3, 4, 2));
    edges.push_back(Edge(4, 5, 7));

    int mstWeight = kruskal(V, edges);
    cout << "최소 신장 트리의 가중치 합: " << mstWeight << endl;

    return 0;
}
