#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


/*
깊이 우선 탐색(DFS)을 이용한 위상 정렬
이 방식은 '더 이상 갈 곳이 없는 노드'부터 순서를 정하는 역방향 아이디어에 기반합니다.

동작 원리
1. DFS 수행: 그래프의 모든 노드에 대해 방문하지 않았다면 DFS를 수행합니다.

2. 탐색의 끝에 도달: 특정 노드에서 출발한 DFS가 모든 자식 노드 탐색을 마치고 더 이상 갈 곳이 없어지면, 해당 노드의 탐색이 '종료'된 것입니다.

3. 결과 저장: 탐색이 종료된 노드를 스택(Stack)에 차례대로 쌓습니다.

4. 역순 출력: 모든 노드에 대한 탐색이 끝나면, 스택에 쌓인 노드를 순서대로 꺼냅니다. 이 순서가 바로 위상 정렬의 결과입니다.
*/

// visited: 전역 방문 여부 체크
// recursion_stack: 현재 DFS 호출 스택에 포함되어 있는지(사이클 탐지용)
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& recursion_stack, stack<int>& result_stack, bool& has_cycle) {
    
    // 현재 노드를 방문 처리 및 재귀 스택에 추가
    visited[node] = true;
    recursion_stack[node] = true;

    // 현재 노드와 연결된 모든 인접 노드를 순회
    for (int neighbor : adj[node]) {
        // 인접 노드를 아직 방문하지 않았다면 재귀적으로 DFS 수행
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, recursion_stack, result_stack, has_cycle);
        } 
        // 만약 인접 노드를 이미 방문했는데, 심지어 현재 재귀 스택에도 있다면 사이클 발견!
        // A -> B -> C -> A 와 같은 상황에서 C가 A를 다시 호출하려는 경우
        else if (recursion_stack[neighbor]) {
            has_cycle = true;
            return; // 사이클 발견 시 즉시 종료
        }
    }

    // ★★★ 핵심 ★★★
    // 현재 노드에서 출발하는 모든 경로의 탐색이 끝났을 때,
    // 즉, 더 이상 갈 곳이 없을 때 결과 스택에 현재 노드를 추가합니다.
    result_stack.push(node);
    
    // 현재 노드의 모든 탐색이 끝났으므로 재귀 스택에서 제거
    recursion_stack[node] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cout << "노드의 개수와 간선의 개수를 입력하세요: ";
    cin >> N >> M;

    vector<vector<int>> adj(N + 1);
    cout << M << "개의 간선 정보를 'A B' 형태로 입력하세요 (A가 B의 선행작업):\n";
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    stack<int> result_stack;
    vector<bool> visited(N + 1, false);
    vector<bool> recursion_stack(N + 1, false); // 사이클 탐지용
    bool has_cycle = false;

    // 모든 노드에 대해 DFS 수행
    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, recursion_stack, result_stack, has_cycle);
            if (has_cycle) break; // 사이클이 발견되면 더 이상 진행할 필요 없음
        }
    }

    if (has_cycle) {
        cout << "그래프에 사이클이 존재하여 위상 정렬을 수행할 수 없습니다." << endl;
    } else {
        cout << "위상 정렬 결과: ";
        while (!result_stack.empty()) {
            cout << result_stack.top() << " ";
            result_stack.pop();
        }
        cout << endl;
    }

    return 0;
}