#include <iostream>
#include <queue>
#include <string>
using namespace std;

int visited[7][7];
int N;

struct Node {
    int y, x;
};
string map[7];

int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};
queue<Node> q;

void BFS(int y, int x) {
    /*
        대기열 준비
        시작 노드 큐에 등록
        
        큐가 빌 때까지 반복
        맨 앞 노드 확인 및 추출
        next 찾기(방향 배열 활용)
        next를 큐에 등록
    */
    visited[y][x] = 1;
    q.push({y,x});

    while(!q.empty()) {
        Node cur = q.front();
        q.pop();

        for(int i=0; i<4; i++) {
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if(ny < 0 || nx < 0 || ny >=N || nx >= N) continue;
            if(visited[ny][nx] == 1) continue;
            visited[ny][nx] = 1;
            q.push({ny,nx});
        }
    }

}

void BFS2(int y, int x) {
    memset(visited, 0, sizeof(visited));
    visited[y][x] = 1;
    q.push({y,x});

    while(!q.empty()) {
        Node cur = q.front();
        q.pop();

        for(int i=0; i<4; i++) {
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if(ny < 0 || nx < 0 || ny >=N || nx >= N) continue;
            if(visited[ny][nx] == 1) continue;
            visited[ny][nx] = visited[cur.y][cur.x] + 1;
            q.push({ny,nx});
        }
    }
}

void BFS3(int y, int x) {
    memset(visited, 0, sizeof(visited));
    visited[y][x] = 1;
    q.push({y,x});

    while(!q.empty()) {
        Node cur = q.front();
        q.pop();

        for(int i=0; i<4; i++) {
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if(ny < 0 || nx < 0 || ny >=N || nx >= N) continue;
            if(visited[ny][nx] == 1) continue;
            if(map[ny][nx] == '#') continue;
            visited[ny][nx] = visited[cur.y][cur.x] + 1;
            q.push({ny,nx});
        }
    }
}

int elsaY, elsaX, annaY, annaX;
int BFS4(int y, int x) {
    memset(visited, 0, sizeof(visited));
    visited[y][x] = 1;
    q.push({y,x});

    while(!q.empty()) {
        Node cur = q.front();
        q.pop();
        if(cur.y == annaY && cur.x == annaX) {
            return (visited[cur.y][cur.x] - 1) / 2;
        }

        for(int i=0; i<4; i++) {
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if(ny < 0 || nx < 0 || ny >=N || nx >= N) continue;
            if(visited[ny][nx] == 1) continue;
            if(map[ny][nx] == '#') continue;
            visited[ny][nx] = visited[cur.y][cur.x] + 1;
            q.push({ny,nx});
        }
    }
}

int main(void) {
    cin >> N;
    BFS(3,3);
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }

    for(int i=0; i<N; i++) {
        cin >> map[i];
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(!visited[i][j]) BFS(i,j);
        }
    }

    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> map[i];
    }
    cin >> elsaY >> elsaX >> annaY >> annaX;

    return 0;
}