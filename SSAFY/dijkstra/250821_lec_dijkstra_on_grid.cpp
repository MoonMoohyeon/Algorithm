#include <iostream>
#include <queue>
#include <string>

using namespace std;



/*
5
0000
##0#
0000
0##0
0#00


5
0123
##3#
1231
2##1
3452
*/

/*
다익스트라 vs 플러드필

- 구현상의 유사점
  가중치 값이 없는 경우


경유지를 방문하는 문제
두 점의 거리를 비교하는 문제
*/



int N;
string MAP[5];
int dys[] = { 1, 0, -1, 0 };
int dxs[] = { 0, 1, 0, -1 };


/////////////////////////////////////////////////
// Flood Fill
////////////////////////////////////////////////

struct Node { int y, x;  };
int visited[5][4];

void bfs(int y, int x) {


	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			visited[i][j] = -1;
		}
	}

	queue<Node> q;
	q.push({ y, x });
	visited[y][x] = 0;

	while (!q.empty()) {

		Node now = q.front(); q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = now.y + dys[dir];
			int nx = now.x + dxs[dir];
			if (ny >= N || nx >= 4 || ny < 0 || nx < 0) continue;
			if (visited[ny][nx] != -1) continue;
			if (MAP[ny][nx] == '#') continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });

		}




	}

}

/////////////////////////////////////////////////
// Dijkstra
////////////////////////////////////////////////

int dist[5][4];

struct Edge {
	int y, x, cost;

	bool operator< (const Edge& next) const {
		// cost가 저렴한 순
		if (cost < next.cost) return false; // 우선 순위가 false
		if (cost > next.cost) return true;
		return false;
	}
};


void dijkstra(int y, int x, int cost) {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			dist[i][j] = 21e8;
		}
	}
	priority_queue<Edge>pq;
	dist[y][x] = cost;
	pq.push({ y, x, cost });

	while (!pq.empty()) {
		Edge now = pq.top(); pq.pop();

		if (dist[now.y][now.x] < now.cost) continue;

		for (int dir = 0; dir < 4; dir++) {
			int ny = now.y + dys[dir];
			int nx = now.x + dxs[dir];
			if (ny >= N || nx >= 4 || ny < 0 || nx < 0) continue;
			if (MAP[ny][nx] == '#') continue;

			int nextcost = dist[now.y][now.x] + (MAP[ny][nx] - '0');

			if (dist[ny][nx] < nextcost) continue;
			dist[ny][nx] = nextcost;
			pq.push({ ny, nx, nextcost });



		}
	}

}


int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> MAP[i];
	}

	/*bfs(0, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 4; j++) {
			if (visited[i][j] == -1)
				cout << '#';
			else
				cout << visited[i][j];
		}
		cout << "\n";
	}*/

	dijkstra(0, 0, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 4; j++) {
			if (dist[i][j] == 21e8)
				cout << '#' << " ";
			else
				cout << dist[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}

