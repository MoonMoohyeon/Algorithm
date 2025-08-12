#include <iostream>
#include <vector>
#include <queue>

// using namespace std; // 전역 using namespace는 충돌을 유발할 수 있어 명시적으로 사용

// --- 전역 변수 선언부 ---
// adj: 인접 리스트 방식의 그래프. adj[A]는 A가 가리키는 노드들의 목록을 저장합니다.
std::vector<int> adj[32001]; 
// indegree: 각 노드의 진입 차수. 자신을 가리키는 간선의 개수를 의미합니다.
// 어떤 노드의 진입 차수가 0이라는 것은 모든 선수과목/선행작업이 완료되었음을 뜻합니다.
int indegree[32001] = {0, };
// is_enqueued: 특정 노드가 큐에 추가되었는지 여부를 표시하는 배열입니다.
// 노드가 중복으로 큐에 들어가는 것을 방지하는 방문(visited) 배열 역할을 합니다.
bool is_enqueued[32001] = {false, };
// q: 위상 정렬의 결과를 순서대로 담을 큐입니다.
std::queue<int> q;

/**
 * @brief 특정 노드로부터 시작되는 위상 정렬 과정을 재귀적으로 처리하는 함수
 * @param node 현재 처리 중인 노드. 이 노드가 선행 조건인 다른 노드들을 확인합니다.
 */
void topology_recursive(int node)
{
    // 현재 노드(node)가 가리키는 모든 인접 노드(neighbor)를 순회합니다.
    for (int neighbor : adj[node])
    {
        // 인접 노드(neighbor)의 진입 차수를 1 감소시킵니다.
        // 선행 작업인 'node'가 처리되었음을 의미합니다.
        // --indegree[neighbor]는 값을 1 감소시킨 후, 그 값을 반환합니다.
        
        // 만약 진입 차수가 0이 되었고, 아직 큐에 추가된 적이 없다면
        if (--indegree[neighbor] == 0 && !is_enqueued[neighbor])
        {
            // 이제 이 인접 노드(neighbor)도 모든 선행 작업이 끝났으므로
            // 결과 큐에 추가합니다.
            q.push(neighbor);
            is_enqueued[neighbor] = true; // 큐에 추가되었음을 표시 (중복 방지)

            // 이제 'neighbor' 노드를 기준으로 다음 단계를 재귀적으로 탐색합니다.
            topology_recursive(neighbor);
        }
    }
}

int main(void)
{
    // C++ 입출력 속도 향상을 위한 설정
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, M; // N: 노드(학생)의 수, M: 간선(키 비교)의 수
    std::cin >> N >> M;

    // M개의 간선 정보를 입력받아 그래프를 구성하고 진입 차수를 계산합니다.
    for (int i = 0; i < M; i++)
    {
        int a, b;
        std::cin >> a >> b;
        adj[a].push_back(b); // a에서 b로 가는 간선 추가 (a가 b 앞에 서야 함)
        indegree[b]++;       // b의 진입 차수 1 증가
    }

    // --- 위상 정렬 시작 ---
    // 1번부터 N번 노드까지 순회하며 위상 정렬의 시작점이 될 노드를 찾습니다.
    // 시작점: 진입 차수가 0인 노드 (즉, 선행 조건이 없는 노드)
    for (int i = 1; i <= N; i++)
    {
        if (indegree[i] == 0 && !is_enqueued[i])
        {
            // 시작점을 결과 큐에 추가하고, 방문(enqueued) 표시
            q.push(i);
            is_enqueued[i] = true;

            // 해당 시작점으로부터 파생되는 모든 관계를 재귀적으로 처리
            topology_recursive(i);
        }
    }

    // 최종적으로 큐에 담긴 노드들을 순서대로 출력하면 위상 정렬 결과가 됩니다.
    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\n";
    
    return 0;
}