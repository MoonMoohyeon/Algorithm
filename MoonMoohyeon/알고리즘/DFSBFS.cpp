#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int V;  // 정점 개수
    vector<vector<int>> adj; // 인접 리스트
    vector<bool> visited; // 방문 여부

public:
    Graph(int V) : V(V), adj(V), visited(V, false) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // 무방향 그래프
    }

    void dfs(int v) {
        cout << v << " ";
        visited[v] = true;

        for (int next : adj[v]) {
            if (!visited[next]) {
                dfs(next);
            }
        }
    }

    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int next : adj[v]) {
                if (!visited[next]) {
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
    }

    void resetVisited() {
        fill(visited.begin(), visited.end(), false);
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "DFS: ";
    g.dfs(0);
    
    g.resetVisited(); // 방문 배열 초기화
    cout << "\nBFS: ";
    g.bfs(0);

    return 0;
}
