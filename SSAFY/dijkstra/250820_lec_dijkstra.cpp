#include <iostream>
#include <queue>

using namespace std;


/*
[Dijkstra 설계]

1. 사전 준비
	- 대기열 준비
	- visited 배열 초기화(최대값을 갖도록)
2. 시작 노드 큐에 등록

아래 과정 반복

3. 우선 순위 높은 노드(now) 확인 및 추출
	- 이미 now까지의 정답이 들어 있음에도
	  같은 now.num 번호로 pq 간선 정보가 들어올 수 있음 
	  ( 더미 제거 코드 필요 )
4. now -> next 후보 찾기
	- next cost 누적 연산 필요
	- 이미 정답 배열에 next.num cost 정보가 있다면 
	  굳이 pq에 추가 X
	  ( 더미 제거 코드 필요 )
5. next 등록

*/


/*

Test Case:


10 12
0 1 23
0 3 8
1 2 26
1 4 100
2 5 35
3 4 10
4 5 50
4 7 11
5 6 1
5 7 777
5 8 5
6 9 53
*/



////////////////////////////////////////////////////////////////////////////

struct Edge {
	int num, w;

	bool operator< (Edge right) const {
		if (w > right.w) return true;
		if (w < right.w) return false;
		return false;
	}
};

int V, E;
int dist[20];
vector<Edge> alis[20];

////////////////////////////////////////////////////////////////////////////
void dijkstra(int start) {

	// 1. 사전 준비
	// 1-1. 정답 배열(해당 노드까지의 최단 거리 저장용)
	// 1-2. PQ 생성
	priority_queue<Edge> pq;
	for (int i = 0; i < 20; i++) {
		dist[i] = 21e8;
	}

	// 2. 시작 노드 큐에 등록
	dist[start] = 0;
	pq.push({ start, 0 });

	// 반복 작업
	while (!pq.empty()) {
		// 3. 최상위 노드 확인 및 추출
		//    -> now까지의 최단 거리임을 보장
		//       더 저렴하게 갈 수 있는 방법은 등장하지 X
		Edge now = pq.top(); pq.pop();
		
		// 더미 제거#1
		// 이후 now로 가는 경로가 등장한다면 더 비싼 비용만 나옴
		if (dist[now.num] < now.w) continue;


		// 4. now -> next 후보 찾기
		for (int i = 0; i < alis[now.num].size(); i++) {
			Edge next = alis[now.num][i];
			int nextcost = dist[now.num] + next.w; // 누적 합
			// 더미 제거#2
			// 이미 등록된 next로 가는 비용보다 현재 경로 비용이 크거나 같으면 더 볼 필요 없음
			if (dist[next.num] <= nextcost) continue;

			// 5. next 등록
			dist[next.num] = nextcost;
			pq.push({ next.num, nextcost });
			
		}


	}

	


}

////////////////////////////////////////////////////////////////////////////

int main() {

	cin >> V >> E;


	for (int i = 0; i < E; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		alis[from].push_back({ to, cost });
		alis[to].push_back({ from,cost });
	}

	dijkstra(0);

	for (int i = 0; i < V; i++) {
		cout << i << " 번 노드까지의 최단 거리 : " << dist[i] << "\n";
	}


	return 0;
}