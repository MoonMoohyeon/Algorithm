#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9; // 무한대를 표현할 값

void floydWarshall(int V, vector<vector<int>>& dist) {
    for (int k = 1; k <= V; ++k) {         // 중간 노드
        for (int i = 1; i <= V; ++i) {     // 시작 노드
            for (int j = 1; j <= V; ++j) { // 도착 노드
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    int V = 4; // 정점 개수
    int E = 5; // 간선 개수

    vector<vector<int>> dist(V + 1, vector<int>(V + 1, INF));

    // 자기 자신까지의 거리는 0
    for (int i = 1; i <= V; ++i)
        dist[i][i] = 0;

    // 간선 입력 (from, to, weight)
    dist[1][2] = 4;
    dist[1][4] = 10;
    dist[2][3] = 3;
    dist[3][4] = -2;
    dist[4][2] = -1;

    floydWarshall(V, dist);

    // 결과 출력
    cout << "모든 정점 간 최단 거리:" << endl;
    for (int i = 1; i <= V; ++i) {
        for (int j = 1; j <= V; ++j) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
