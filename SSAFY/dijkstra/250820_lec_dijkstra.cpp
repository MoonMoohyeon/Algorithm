#include <iostream>
#include <queue>

using namespace std;


/*
[Dijkstra ����]

1. ���� �غ�
	- ��⿭ �غ�
	- visited �迭 �ʱ�ȭ(�ִ밪�� ������)
2. ���� ��� ť�� ���

�Ʒ� ���� �ݺ�

3. �켱 ���� ���� ���(now) Ȯ�� �� ����
	- �̹� now������ ������ ��� ��������
	  ���� now.num ��ȣ�� pq ���� ������ ���� �� ���� 
	  ( ���� ���� �ڵ� �ʿ� )
4. now -> next �ĺ� ã��
	- next cost ���� ���� �ʿ�
	- �̹� ���� �迭�� next.num cost ������ �ִٸ� 
	  ���� pq�� �߰� X
	  ( ���� ���� �ڵ� �ʿ� )
5. next ���

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

	// 1. ���� �غ�
	// 1-1. ���� �迭(�ش� �������� �ִ� �Ÿ� �����)
	// 1-2. PQ ����
	priority_queue<Edge> pq;
	for (int i = 0; i < 20; i++) {
		dist[i] = 21e8;
	}

	// 2. ���� ��� ť�� ���
	dist[start] = 0;
	pq.push({ start, 0 });

	// �ݺ� �۾�
	while (!pq.empty()) {
		// 3. �ֻ��� ��� Ȯ�� �� ����
		//    -> now������ �ִ� �Ÿ����� ����
		//       �� �����ϰ� �� �� �ִ� ����� �������� X
		Edge now = pq.top(); pq.pop();
		
		// ���� ����#1
		// ���� now�� ���� ��ΰ� �����Ѵٸ� �� ��� ��븸 ����
		if (dist[now.num] < now.w) continue;


		// 4. now -> next �ĺ� ã��
		for (int i = 0; i < alis[now.num].size(); i++) {
			Edge next = alis[now.num][i];
			int nextcost = dist[now.num] + next.w; // ���� ��
			// ���� ����#2
			// �̹� ��ϵ� next�� ���� ��뺸�� ���� ��� ����� ũ�ų� ������ �� �� �ʿ� ����
			if (dist[next.num] <= nextcost) continue;

			// 5. next ���
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
		cout << i << " �� �������� �ִ� �Ÿ� : " << dist[i] << "\n";
	}


	return 0;
}