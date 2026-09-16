#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/*
    2차원 격자(Grid) BFS / DFS 핵심 템플릿
    
    1. 4방향 벡터 (상, 우, 하, 좌)
    2. 경계 검사 함수 checkbound(y, x)
    3. 미로 최단 거리 구하기 (BFS) - dist/visited 갱신
    4. 연결 요소(섬) 개수 및 크기 구하기 (Flood Fill)
    
    ★ 핵심 주의점:
    BFS에서 큐에 넣을 때(push 시점) 반드시 visited를 체크해야 중복 방문에 의한 메모리 초과를 방지할 수 있습니다.
*/

const int MAX = 100;
int N, M;
int map_data[MAX][MAX];
int visited[MAX][MAX];

// 상, 우, 하, 좌 시계방향
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

// 1. 격자 범위 내에 있는지 검사
bool checkbound(int y, int x) {
    return (y >= 0 && y < N && x >= 0 && x < M);
}

// 2. 미로 최단 거리 (BFS)
// (startY, startX) -> (destY, destX) 최단 거리 반환 (도달 불가시 -1)
int bfs_shortest_path(int startY, int startX, int destY, int destX) {
    memset(visited, -1, sizeof(visited)); // -1: 미방문
    queue<pair<int, int>> q;

    visited[startY][startX] = 0; // 시작점 거리 0
    q.push({startY, startX});

    while (!q.empty()) {
        auto cur = q.front();
        int cy = cur.first;
        int cx = cur.second;
        q.pop();

        if (cy == destY && cx == destX) {
            return visited[cy][cx];
        }

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i];
            int nx = cx + dx[i];

            if (!checkbound(ny, nx)) continue;
            if (map_data[ny][nx] == 1) continue; // 벽(1)인 경우 건너뜀
            if (visited[ny][nx] != -1) continue; // 이미 방문한 경우

            // 큐에 넣는 즉시 방문 처리 및 거리 갱신
            visited[ny][nx] = visited[cy][cx] + 1;
            q.push({ny, nx});
        }
    }

    return -1; // 목적지 도달 불가
}

// 3. 연결 요소(Flood Fill) 크기 구하기 (DFS)
int dfs_flood_fill(int y, int x) {
    visited[y][x] = 1;
    int area_size = 1;

    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (!checkbound(ny, nx)) continue;
        if (map_data[ny][nx] == 1 && !visited[ny][nx]) { // 연결된 땅(1)이고 미방문
            area_size += dfs_flood_fill(ny, nx);
        }
    }

    return area_size;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 예제 1: 5x5 미로 최단 거리 테스트 (0: 길, 1: 벽)
    N = 5; M = 5;
    int sample_maze[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            map_data[i][j] = sample_maze[i][j];
        }
    }

    cout << "=== 1. 미로 최단 거리 (BFS) ===\n";
    int dist = bfs_shortest_path(0, 0, 4, 4);
    cout << "(0,0)에서 (4,4)까지의 최단 거리: " << dist << "\n\n";

    // 예제 2: 연결된 섬의 개수 및 각 섬의 크기 구하기 (Flood Fill)
    int sample_islands[5][5] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            map_data[i][j] = sample_islands[i][j];
        }
    }

    memset(visited, 0, sizeof(visited));
    int island_count = 0;
    vector<int> island_sizes;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map_data[i][j] == 1 && !visited[i][j]) {
                island_count++;
                island_sizes.push_back(dfs_flood_fill(i, j));
            }
        }
    }

    cout << "=== 2. 연결 요소 Flood Fill (DFS) ===\n";
    cout << "섬의 총 개수: " << island_count << "\n";
    cout << "각 섬의 크기: ";
    for (int s : island_sizes) cout << s << " ";
    cout << "\n";

    return 0;
}
