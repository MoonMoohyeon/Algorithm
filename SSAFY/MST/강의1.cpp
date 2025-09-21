#include <iostream>
#include <algorithm>
using namespace std;
/*
    신장 트리
    그래프에서 N개의 노드를 N-1개의 간선으로 모든 정점을 연결한 트리
    1. 사이클이 없다.
    2. 특정 노드에서 특정 노드로 갈 수 있는 경로가 단 하나

    크루스칼 알고리즘
    간선의 가중치가 최소값인 것부터 선택한다 (pq)
    가중치가 작은 순서대로 선택한다
    유니온 파인드로 같은 그룹인지 판별한다
    같은 그룹이라면 연결하지 않는다
    N-1개의 간선이 선택될 때까지 반복한다
*/

struct Edge {
    int A, B, cost;
    bool operator<(Edge next)const {
        // 가중치 작은 것 우선, 같으면 노드 번호가 작은 것
        if(cost < next.cost) return true;
        if(cost > next.cost) return false;

        if(A < next.A) return true;
        if(A > next.A) return false;

        if(B < next.B) return true;
        if(B > next.B) return false;

        return false;
    }
};

Edge edges[20];
int parent[20];
int ran[20] = {0,};
int N, M;

int find(int x) {
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void uni(int a, int b) {
    int ra = find(a);
    int rb = find(b);

    if(ra != rb) {
        if(ran[ra] < ran[rb]) {
            swap(ra, rb);
        }

        parent[rb] = ra;

        if(ran[ra] == ran[rb]) ran[ra]++;
    }
}

int main(void) {
    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        edges[i] = {a,b,c};
    }

    for(int i=0; i<N; i++) {
        parent[i] = i;
    }

    sort(edges, edges+M);

    int sum = 0;
    for(int i=0; i<M; i++) {
        Edge now = edges[i];
        if(find(now.A) != find(now.B)) {
            uni(now.A, now.B);
            sum += now.cost;
        }
    }
}