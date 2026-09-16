# 2차원 격자 탐색 (BFS / DFS & Flood Fill)

코딩테스트(특히 삼성 A/B형, SWEA, 프로그래머스)에서 가장 높은 출제 비중을 차지하는 기본 유형입니다.

---

## 1. BFS vs DFS 선택 기준

| 비교 항목 | BFS (너비 우선 탐색) | DFS (깊이 우선 탐색) |
| :--- | :--- | :--- |
| **주요 도구** | `queue` | 재귀 함수 (또는 `stack`) |
| **대표 활용** | **최단 거리 / 최소 이동 횟수**, 레벨별 탐색 | **모든 경로 탐색 / 백트래킹**, 사이클 검사 |
| **방문 순서** | 시작점에서 가까운 노드부터 차례대로 탐색 | 한 경로를 끝까지 파고든 뒤 복귀 |
| **시간 복잡도** | $O(V + E) = O(N \times M)$ (격자 맵의 경우) | $O(V + E) = O(N \times M)$ |

---

## 2. 필수 테크닉 3가지

### ① 4방향 이동 벡터 (상, 우, 하, 좌)
```cpp
// 시계 방향: 상(0), 우(1), 하(2), 좌(3)
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue; // 경계 밖 제외
}
```

### ② ★ BFS 방문 체크(Visited) 시점
- **잘못된 방식**: 큐에서 꺼낼 때 (`pop()`) 방문 처리 -> 같은 노드가 큐에 여러 번 들어가서 **메모리 초과(OOM)** 발생.
- **올바른 방식**: 큐에 넣을 때 (`push()`) 즉시 `visited[ny][nx] = visited[cy][cx] + 1;` 처리.

### ③ Flood Fill (영역 크기 구하기)
- 격자 맵에서 연결된 1들의 덩어리 개수와 각 덩어리의 크기를 셀 때 DFS 또는 BFS를 사용합니다.
- 방문한 칸은 값을 0으로 지우거나 `visited` 배열로 마킹하여 중복 계산을 방지합니다.

---

## 3. 추천 연습 문제
- **SWEA**
  - [1226. [S/W 문제해결 기본] 7일차 - 미로1 (D4)](https://swexpertacademy.com/)
  - [1238. [S/W 문제해결 기본] 10일차 - Contact (D4)](https://swexpertacademy.com/)
  - [1953. [모의 SW 역량테스트] 탈주범 검거](https://swexpertacademy.com/)
- **Programmers**
  - [게임 맵 최단거리 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/1844)
  - [네트워크 (Lv.3)](https://school.programmers.co.kr/learn/courses/30/lessons/43162)
  - [단어 변환 (Lv.3)](https://school.programmers.co.kr/learn/courses/30/lessons/43163)
