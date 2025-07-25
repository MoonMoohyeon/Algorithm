#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <climits>
using namespace std;

int N, M;
vector<pair<int,int>> graph[100001];
priority_queue<pair<int, int>> pq;
int dist[100001] = { 0, };

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M; // N = 정점의 개수, M = 간선의 개수

    int a, b, c;
    for (int i = 0; i < M; i++) { // 인접 리스트 생성
        cin >> a >> b >> c; // a와 b가 가중치 c의 간선으로 연결됨을 의미한다.
        graph[a].push_back({ c,b });
        graph[b].push_back({ c,a }); // 무방향 그래프인 경우, 양쪽에 추가
    }

    // dist 배열 초기화 (모든 정점까지의 거리를 무한대로 설정)
    for (int i = 0; i < 100001; i++) dist[i] = INT_MAX; 

    // 시작 정점 설정. 여기서는 정점 0을 시작 정점으로 가정합니다.
    // 만약 정점 번호가 1부터 N까지라면, 시작 정점을 1로 설정하고 dist[1] = 0, pq.push({0, 1})로 변경해야 합니다.
    dist[0] = 0; // 시작 정점 (0번 정점) 자기 자신까지의 거리는 0
    pq.push({ 0, 0 }); // 우선순위 큐에 {거리, 정점 번호} 형태로 삽입. (최소 힙처럼 사용하기 위해 거리를 음수로 넣습니다.)

    while (!pq.empty()) { // 우선순위 큐가 비어있지 않은 동안 반복
        int cost = -pq.top().first; // 우선순위 큐에서 꺼낸 가장 작은 가중치 (거리)
        int pos = pq.top().second; // 현재 방문할 정점의 번호
        pq.pop();

        // 현재 꺼낸 거리가 이미 dist[pos]에 기록된 거리보다 크다면, 더 이상 처리할 필요가 없습니다.
        // 이는 이미 더 짧은 경로를 찾았다는 의미이므로, 중복 처리를 방지합니다.
        if (cost > dist[pos]) continue;

        // 현재 정점(pos)과 연결된 모든 간선을 확인
        for (auto it = graph[pos].begin(); it != graph[pos].end(); it++) {
            int next_edge_weight = it->first; // 현재 정점(pos)에서 다음 정점(npos)까지의 간선 가중치
            int npos = it->second; // 다음 정점의 번호

            int new_cost = cost + next_edge_weight; // 시작 정점부터 npos까지의 새로운 총 거리 계산

            // 새로운 총 거리가 현재 npos에 기록된 최단 거리보다 짧으면 갱신
            if (new_cost < dist[npos]) {
                dist[npos] = new_cost; // npos까지의 최단 거리 갱신
                pq.push({ -new_cost, npos }); // 갱신된 거리와 정점 번호를 큐에 삽입 (최소 힙처럼 사용하기 위해 거리를 음수로)
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}