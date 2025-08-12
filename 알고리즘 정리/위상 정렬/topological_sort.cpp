#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void topologicalSort(int N, vector<vector<int>>& adj, vector<int>& in_degree) {
    
    // 1. 초기화: 진입 차수가 0인 노드를 큐에 추가
    // 이 노드들은 선행 작업이 필요 없는, 가장 먼저 시작할 수 있는 노드들입니다.
    queue<int> q;
    vector<int> result;
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        // 큐에서 노드를 하나 꺼냅니다. 이 노드는 현재 시점에서 정렬 순서가 확정된 노드입니다.
        int current_node = q.front();
        q.pop();

        // 결과 리스트에 현재 노드를 추가합니다.
        result.push_back(current_node);

        // 현재 노드와 연결된(즉, 현재 노드가 선행 조건인) 다른 노드들을 순회합니다.
        for (int next_node : adj[current_node]) {
            // 연결된 노드의 진입 차수를 1 감소시킵니다.
            in_degree[next_node]--;

            // 만약 진입 차수가 0이 되었다면, 해당 노드의 모든 선행 작업이 완료된 것이므로
            // 큐에 추가하여 다음 정렬 순서의 후보로 만듭니다.
            if (in_degree[next_node] == 0) {
                q.push(next_node);
            }
        }
    }

    // 정렬된 노드의 개수가 전체 노드의 개수와 같다면 위상 정렬 성공
    if (result.size() == N) {
        cout << "위상 정렬 결과: ";
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        // 같지 않다면 그래프에 사이클이 존재하여 위상 정렬이 불가능함을 의미합니다.
        cout << "그래프에 사이클이 존재하여 위상 정렬을 수행할 수 없습니다." << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cout << "노드의 개수와 간선의 개수를 입력하세요: ";
    cin >> N >> M;

    // 인접 리스트: adj[i]는 i번 노드에서 출발하여 도달하는 노드들의 목록을 저장합니다.
    vector<vector<int>> adj(N + 1);
    
    // 진입 차수 배열: in_degree[i]는 i번 노드로 들어오는 간선의 개수를 저장합니다.
    vector<int> in_degree(N + 1, 0);

    cout << M << "개의 간선 정보를 'A B' 형태로 입력하세요 (A가 B의 선수과목/선행작업을 의미):\n";
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++; 
    }

    // 위상 정렬 함수 호출
    topologicalSort(N, adj, in_degree);

    return 0;
}