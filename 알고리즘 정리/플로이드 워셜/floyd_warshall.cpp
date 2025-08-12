#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9; // 무한대(연결되지 않음)를 나타내는 값
const int MAX_N = 101; // 최대 노드 개수 + 1

int N, M;

void print_dist3(int k) {
    cout << "\n=== k = " << k << " (1 ~ " << k << "번 노드 경유) ===\n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (dist3[k][i][j] == INF) cout << "INF ";
            else cout << dist3[k][i][j] << "   ";
        }
        cout << "\n";
    }
}

// dist[k][i][j]: 1~k번 노드'만'을 거쳐서 i에서 j로 가는 최단 거리
int dist3[MAX_N][MAX_N][MAX_N];
void floyd() {
    cout << "### Version 1: 3차원 배열 사용 ###";
    print_dist3(0); // 초기 상태 출력

    // 플로이드-워셜 알고리즘
    // k: 거쳐가는 노드
    for (int k = 1; k <= N; k++) {
        // i: 출발 노드
        for (int i = 1; i <= N; i++) {
            // j: 도착 노드
            for (int j = 1; j <= N; j++) {
                // 점화식: dist[k][i][j] = min(dist[k-1][i][j], dist[k-1][i][k] + dist[k-1][k][j])
                // k번을 거치지 않는 기존 경로(dist[k-1][i][j])와
                // k번을 거쳐가는 새로운 경로(dist[k-1][i][k] + dist[k-1][k][j])를 비교
                int path_without_k = dist3[k - 1][i][j];
                int path_with_k = (dist3[k - 1][i][k] == INF || dist3[k - 1][k][j] == INF)
                                    ? INF
                                    : dist3[k - 1][i][k] + dist3[k - 1][k][j];
                
                dist3[k][i][j] = min(path_without_k, path_with_k);
            }
        }
        print_dist3(k); // 각 단계별 결과 출력
    }
}

int dist2[2][MAX_N][MAX_N];
void floyd_v2() {
    // dist[0][i][j]는 초기 상태로 이미 채워져 있다고 가정

    // k: 거쳐가는 노드
    for (int k = 1; k <= N; k++) {
        int current = k % 2;        // 현재 k의 상태를 저장할 인덱스 (1, 0, 1, 0, ...)
        int prev = (k - 1) % 2;     // 이전 k-1의 상태가 저장된 인덱스 (0, 1, 0, 1, ...)

        // i: 출발 노드
        for (int i = 1; i <= N; i++) {
            // j: 도착 노드
            for (int j = 1; j <= N; j++) {
                // k-1 상태(prev)를 참조하여 k 상태(current)를 갱신
                int path_without_k = dist2[prev][i][j];
                int path_with_k = (dist2[prev][i][k] == INF || dist2[prev][k][j] == INF)
                                    ? INF
                                    : dist2[prev][i][k] + dist2[prev][k][j];

                dist2[current][i][j] = min(path_without_k, path_with_k);
            }
        }
    }
}

void print_dist() {
    cout << "\n=== 최종 최단 경로 행렬 ===\n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << "   ";
        }
        cout << "\n";
    }
}

// 최종 버전: 2차원 배열 하나만 사용
int dist[MAX_N][MAX_N];
void floyd_final() {
    // k: 거쳐가는 노드
    for (int k = 1; k <= N; k++) {
        // i: 출발 노드
        for (int i = 1; i <= N; i++) {
            // j: 도착 노드
            for (int j = 1; j <= N; j++) {
                // 자기 자신을 거쳐가는 경우는 의미 없으므로 건너뛰어도 됨
                if (i == k || j == k) continue;

                // dist[i][k]와 dist[k][j]는 이번 k 루프에서 변하지 않는 값이므로
                // 하나의 배열에서 바로 읽고 갱신해도 문제가 없음
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 예제 입력 (N: 노드 수, M: 간선 수)
    N = 4; M = 7;
    int edges[7][2] = {{1, 2}, {1, 4}, {2, 3}, {2, 4}, {3, 1}, {3, 4}, {4, 2}};
    
    // 배열 초기화
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) dist[i][j] = 0; // 자기 자신으로 가는 경로는 0
            else dist[i][j] = INF;     // 나머지는 무한대로 초기화
        }
    }

    // 초기 간선 정보 입력
    for (int i = 0; i < M; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        dist[a][b] = 1; // 가중치가 1인 간선으로 가정
    }
    
    cout << "### Version 3: 최종 2차원 배열 사용 ###";
    cout << "\n=== 초기 상태 ===\n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << "   ";
        }
        cout << "\n";
    }

    // 플로이드-워셜 알고리즘 실행
    floyd_final();

    // 최종 결과 출력
    print_dist();

    return 0;
}