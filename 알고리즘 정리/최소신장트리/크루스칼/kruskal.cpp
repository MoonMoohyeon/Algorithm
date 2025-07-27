#include <iostream> // C++ 표준 입출력을 위한 헤더
#include <vector>   // 동적 배열인 vector를 사용하기 위한 헤더
#include <algorithm>// sort 함수를 사용하기 위한 헤더
using namespace std;

// 간선 정보를 저장하기 위한 구조체
// {가중치, 정점1, 정점2} 형태로 정보를 관리하면 코드가 더 깔끔해집니다.
struct Edge {
    int u, v, weight;
    // sort 함수에서 가중치를 기준으로 오름차순 정렬하기 위한 비교 연산자
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// 유니온-파인드(Union-Find)를 위한 부모 노드 정보 배열
vector<int> parent;
vector<int> rk;

// find 연산: 정점 x가 속한 집합의 대표(루트) 노드를 찾는 함수
// 경로 압축(Path Compression) 최적화가 적용되어 있습니다.
int find_set(int x) {
    // 만약 자기 자신이 대표 노드라면, 자기 자신을 반환
    if (parent[x] == x) {
        return x;
    }
    // 아니라면, 부모 노드를 재귀적으로 찾아 올라가면서 경로상의 모든 노드들이 직접 루트를 가리키도록 변경 (경로 압축)
    return parent[x] = find_set(parent[x]);
}

// union 연산: 두 정점 x와 y가 속한 집합을 합치는 함수
void union_sets(int x, int y) {
    // 각 정점의 대표 노드를 찾음
    int rootX = find_set(x);
    int rootY = find_set(y);

    // 두 원소가 이미 같은 집합에 속해 있다면 (루트가 같다면) 아무것도 하지 않습니다.
    if (x != y) {
        // 'Union by Rank' 최적화: 랭크가 더 작은 트리를 랭크가 더 큰 트리에 붙입니다.
        // 이는 전체 트리의 높이가 불필요하게 길어지는 것을 방지하여 효율을 높입니다.
        // 항상 a가 b보다 랭크가 크거나 같도록 조정합니다.
        if (rk[x] < rk[y]) {
            swap(x, y); // a와 b의 역할을 바꿉니다.
        }
        
        // 랭크가 작은 트리의 루트(b)를 랭크가 큰 트리의 루트(a)의 자식으로 만듭니다.
        parent[y] = x;
        
        // 만약 두 트리의 랭크가 같았다면, 합쳐진 후의 트리 랭크는 1 증가합니다.
        if (rk[x] == rk[y]) {
            rk[x]++;
        }
    }
}

int main() {
    // C++ 입출력 속도 향상을 위한 설정 (필요 시 사용)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E; // V: 정점(Vertex)의 개수, E: 간선(Edge)의 개수
    cout << "정점의 개수와 간선의 개수를 입력하세요: ";
    cin >> V >> E;

    // 간선 정보를 저장할 벡터
    vector<Edge> edges;
    cout << E << "개의 간선 정보를 (정점1 정점2 가중치) 형태로 입력하세요:\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // --- 크루스칼 알고리즘 시작 ---

    // 1. 모든 간선을 가중치 기준으로 오름차순 정렬
    sort(edges.begin(), edges.end());

    // 2. 유니온-파인드 자료구조 초기화
    // 처음에는 모든 정점이 자기 자신만을 원소로 갖는 개별적인 집합으로 시작
    parent.resize(V + 1);
    for (int i = 1; i <= V; ++i) {
        parent[i] = i;
        // 모든 집합의 초기 랭크는 1입니다. (원소 1개짜리 트리)
        rk[i] = 1;
    }

    long long mst_cost = 0; // 최소 신장 트리의 총 가중치를 저장할 변수
    int edges_count = 0;   // MST에 포함된 간선의 개수를 저장할 변수

    // 3. 정렬된 간선을 순서대로 순회
    for (const auto& edge : edges) {
        // 4. 간선이 잇는 두 정점이 서로 다른 집합에 속해 있는지 확인 (사이클 생성 여부 검사)
        // find_set(u) != find_set(v)는 두 정점을 연결해도 사이클이 생기지 않음을 의미
        if (find_set(edge.u) != find_set(edge.v)) {
            // 사이클이 생기지 않으면, 이 간선을 MST에 추가
            union_sets(edge.u, edge.v); // 두 정점이 속한 집합을 합침
            mst_cost += edge.weight;   // 간선의 가중치를 총 비용에 더함
            edges_count++;             // MST에 포함된 간선 수 증가

            cout << "간선 추가: (" << edge.u << ", " << edge.v << "), 가중치: " << edge.weight << "\n";
        }

        // MST는 V-1개의 간선으로 이루어지므로, 필요한 만큼 간선을 다 찾았다면 종료
        if (edges_count == V - 1) {
            break;
        }
    }

    // --- 알고리즘 종료 ---

    // 최종 결과 출력
    cout << "\n최소 신장 트리의 총 가중치: " << mst_cost << endl;

    return 0;
}