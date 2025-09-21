#include <iostream>
#include <vector>
using namespace std;

/*
    트리 = 특정 노드에서 특정 노드로 갈 수 있는 경로가 단 하나인 그래프.

    인접행렬 : 한번에 연결 여부 확인 가능, 정렬이 필요 없음, 메모리가 큼

    인접리스트 : 벡터로 연결된 노드번호만 저장

    DFS : 그래프 자료구조에서 이루어지는 백트래킹, 재귀 구조
    1. 싸이클이 생기는 경우
    2. 다양한 경로
    3. 가중치가 있는 경우
*/


int N, M;
int mat[10][10];
vector<int> alis[5];

void dfs(int now) { // 모든 노드를 확인하는 순회의 경우 V^2이 걸린다.
    cout << now << " ";

    for(int i=0; i<N; i++) {
        int next = i;
        if(mat[now][next] == 0) continue;
        dfs(next);
    }
}

void dfs2(int now) { // V + E만큼 걸린다
    cout << now << " ";

    for(int i=0; i<alis[now].size(); i++) {
        int next = alis[now][i];
        dfs(next);
    }
}

int visited[10]; // 1. 싸이클이 생기는 경우
void dfs3(int now) {
    cout << now << " ";
    for(int i=0; i<alis[now].size(); i++) {
        int next = alis[now][i];
        if(visited[next] == 1) continue;
        visited[next] = 1;
        dfs(next);
    }
}

vector<int> path;
void dfs4(int now) { // 다양한 경로 뽑기

    if(now >= N-1) {
        for(int i=0; i<path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }

    cout << now << " ";
    for(int i=0; i<alis[now].size(); i++) {
        int next = alis[now][i];
        if(visited[next] == 1) continue;
        path.push_back(next);
        visited[next] = 1;
        dfs(next);
        path.pop_back();
        visited[next] = 0;
    }
}

struct Node {
    int num;
    int cost;
};
vector<Node> al[5];
int sum;

int dfs5(int now) {

    if(now >= N-1) {
        for(int i=0; i<path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << " = " << sum << endl;
    }

    for(int i=0; i<al[now].size(); i++) {
        Node next = al[now][i];

        if(visited[next.num] == 1) continue;
        visited[next.num] = 1;
        path.push_back(next.num);
        sum += next.cost;
        dfs5(next.num);
        visited[next.num] = 0;
        path.pop_back();
        sum -= next.cost;

    }
}
    
int main(void) {

    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int from ,to;
        cin >> from >> to;
        mat[from][to] = 1;
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }

    for(int i=0; i<M; i++) {
        int from, to;
        cin >> from >> to;
        alis[from].push_back(to);
        alis[to].push_back(from);
    }

    int de = -1;

    visited[0] = 1;
    path.push_back(0);
    dfs3(0);

    for(int i=0; i<M; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        al[from].push_back({to,cost});
        al[to].push_back({from,cost});
    }

    return 0;
}