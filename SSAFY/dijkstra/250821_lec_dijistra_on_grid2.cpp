#include <iostream>
#include <queue>
#include <string>

using namespace std;

/*
V, (V<=5000) 
E, (E<=10000)
P (민철 위치, 1<= P <= V)

cost <= 10000
도착하지 못할 수 있음


6 7 4
1 2 1
1 3 3
2 3 10
3 4 1
3 5 2
4 5 1
5 6 1
*/

int V, E, P;


/////////////////////////////////////////////////
// Dijkstra
////////////////////////////////////////////////


struct Edge {
	int num;	// to
	int cost;

	bool operator< (const Edge& next) const {
		// cost가 저렴한 순
		if (cost < next.cost) return false; // 우선 순위가 false
		if (cost > next.cost) return true;
		return false;
	}
};

vector<int> dist;
vector<vector<Edge>> alis;


int dijkstra(int start, int dest) {

	for (int i = 1; i <= V; i++) {
		dist[i] = 21e8;
	}

	priority_queue<Edge>pq;
	dist[start] = 0;
	pq.push({ start, 0 });

	while (!pq.empty()) {
		Edge now = pq.top(); pq.pop();
		if (now.num == dest) return dist[dest];
		if (dist[now.num] < now.cost) continue;

		for (Edge& next : alis[now.num]) {
			int nextcost = dist[now.num] + next.cost;
			if (dist[next.num] <= nextcost) continue;
			dist[next.num] = nextcost;
			pq.push({ next.num, nextcost });
		}
	}

	return -1;

}


int main() {

	cin >> V >> E >> P;

	dist.resize(V + 1);
	alis.resize(V + 1, vector<Edge>(V + 1));

	for (int i = 0; i < E; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		alis[from].push_back({ to, cost });
		alis[to].push_back({ from, cost });
	}

	int toMin = dijkstra(1, P);
	int withMin = dijkstra(P, V);
	int company = dijkstra(1, V);

	cout << toMin << "\n";
	cout << withMin << "\n";
	cout << company << "\n";

	return 0;
}

