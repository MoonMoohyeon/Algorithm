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

    cin >> N >> M;

    int a, b, c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        graph[a].push_back({ c,b });
        graph[b].push_back({ c,a });
    }

    for (int i = 0; i < 100001; i++) dist[i] = INT_MAX;

    dist[0] = 0;
    pq.push({ 0, 0 });

    while (!pq.empty()) {
        int pos = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();
        if (cost > dist[pos]) continue;

        for (auto i = graph[pos].begin(); i != graph[pos].end(); i++) {
            int npos = i->second;
            int ncost = i->first + cost;

            if (ncost < dist[npos]) {
                dist[npos] = ncost;
                pq.push({ -ncost, npos });
            }
        }
    }

    for (int i = 0; i < N; i++) {
       cout << dist[i] << " ";
    }

    return 0;
}