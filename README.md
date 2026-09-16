# 🚀 Algorithm & Coding Test Repository

코딩테스트(삼성 A/B형, SWEA, 프로그래머스, 백준) 대비 핵심 자료구조 및 알고리즘 모음 저장소입니다.  
기초 문법부터 코딩테스트 빈출 1순위 유형(격자 BFS/DFS, 구현/시뮬레이션, 기초 DP, 우선순위 큐) 및 심화 알고리즘까지 체계적으로 정리되어 있습니다.

---

## 📚 리포지토리 구성 (Table of Contents)

### 1. [C++ 기초 및 STL](C++/)
- **문법**: [입력](C++/문법/2.%20입력.cpp), [출력](C++/문법/1.%20출력.cpp), [자료형](C++/문법/3.%20%20자료형.cpp), [문자열](C++/문법/4.%20문자열.cpp), [참조자/형변환](C++/문법/5.%20참조자,%20형변환,%20타입.cpp), [동적할당](C++/문법/7.%20동적할당.cpp), [클래스/객체](C++/문법/9.%20클래스와%20객체.cpp), [람다](C++/문법/람다.cpp)
- **STL 컨테이너**: [vector](C++/STL/vector.cpp), [queue](C++/STL/queue.cpp), [stack](C++/STL/stack.cpp), [deque](C++/STL/dequeue.cpp), [priority_queue (heap)](C++/STL/heap.cpp), [map](C++/STL/map.cpp), [set](C++/STL/set.cpp), [unordered_map/set](C++/STL/hash/)
- **STL 알고리즘**: [sort](C++/STL/sort.cpp), [변경/불변경 알고리즘](C++/STL/알고리즘%20라이브러리/)

### 2. 코딩테스트 핵심 필수 알고리즘 (추천 복습 순서)
1. **[2차원 격자 탐색 (BFS/DFS)](알고리즘%20정리/BFS_DFS/)** ⭐⭐⭐
   - 4방향 탐색, 미로 최단 거리(BFS), 연결 요소/크기(Flood Fill)
2. **[구현 & 시뮬레이션](알고리즘%20정리/구현_시뮬레이션/)** ⭐⭐⭐
   - 2차원 배열 90도 회전, 달팽이(소용돌이) 배열, 테두리 회전, 방향 전환
3. **[완전탐색 & 백트래킹](알고리즘%20정리/백트래킹/)** ⭐⭐⭐
   - [순열](알고리즘%20정리/백트래킹/순열과%20조합/순열.cpp), [조합](알고리즘%20정리/백트래킹/순열과%20조합/조합.cpp), [중복허용](알고리즘%20정리/백트래킹/순열과%20조합/중복허용.cpp), [N-Queen](알고리즘%20정리/백트래킹/nqueen/)
4. **[자료구조 & 우선순위 큐](알고리즘%20정리/우선순위큐/)** ⭐⭐
   - [우선순위 큐 실전 가이드](알고리즘%20정리/우선순위큐/priority_queue_guide.cpp), [맵 활용법](알고리즘%20정리/맵%20사용법/), [셋 활용법](알고리즘%20정리/셋%20사용법/)
5. **[다이나믹 프로그래밍 (DP)](알고리즘%20정리/다이나믹프로그래밍/)** ⭐⭐
   - [기초 DP (1차원 선형, 동전 교환, LIS)](알고리즘%20정리/다이나믹프로그래밍/기초_DP/), [배낭 문제 (Knapsack)](알고리즘%20정리/다이나믹프로그래밍/knapsack/)
6. **[탐색 & 투 포인터](알고리즘%20정리/이진탐색/)** ⭐⭐
   - [이진 탐색](알고리즘%20정리/이진탐색/binary_search.cpp), [매개변수 탐색](알고리즘%20정리/이진탐색/매개변수탐색/), [투 포인터 & 슬라이딩 윈도우](알고리즘%20정리/두%20포인터/)

### 3. 그래프 & 중고급 알고리즘
- **최단 경로**: [다익스트라](알고리즘%20정리/다익스트라/), [플로이드 워셜](알고리즘%20정리/플로이드%20워셜/), [벨만-포드](알고리즘%20정리/bellman_ford.cpp)
- **최소 신장 트리 (MST)**: [크루스칼](알고리즘%20정리/최소신장트리/크루스칼/), [프림](알고리즘%20정리/최소신장트리/프림/)
- **트리 & 분리 집합**: [유니온 파인드](알고리즘%20정리/유니온%20파인드/), [위상 정렬](알고리즘%20정리/위상%20정렬/), [트라이](알고리즘%20정리/트라이/), [트리 순회](알고리즘%20정리/트리%20순회/)
- **자료구조 심화**: [세그먼트 트리](알고리즘%20정리/세그먼트%20트리/), [문자열 KMP](알고리즘%20정리/문자열%20탐색/), [CCW 기하](알고리즘%20정리/CCW.cpp)

---

## ⏱️ 코딩테스트 실전 치트시트 (Cheat Sheet)

### 1. $N$의 크기에 따른 시간 복잡도 가늠법 (1초 $\approx 10^8$회 연산)
| $N$의 크기 | 허용 시간 복잡도 | 추천 알고리즘 / 기법 |
| :--- | :--- | :--- |
| **$N \le 10$** | $O(N!), O(2^N)$ | 순열, 조합, 완전탐색, 백트래킹 |
| **$N \le 20$** | $O(2^N)$ | 부분집합 생성, 비트마스킹, DFS |
| **$N \le 100$** | $O(N^3)$ | 플로이드-워셜, 3중 반복문 시뮬레이션 |
| **$N \le 1,000$** | $O(N^2)$ | 2차원 DP, 브루트포스, 2중 루프 |
| **$N \le 100,000$** | $O(N \log N)$ | 정렬, 우선순위 큐, 이진 탐색, 세그먼트 트리 |
| **$N \le 10,000,000$** | $O(N)$ | 슬라이딩 윈도우, 투 포인터, 누적 합 |

---

### 2. 코딩테스트 시작 템플릿 (Fast I/O & 전역 변수)
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    // 빠른 입출력 필수 (cin/cout 속도 향상)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // ★ 다중 테스트케이스인 경우 전역 배열 및 변수 반드시 초기화!
        // memset(visited, 0, sizeof(visited));
        
        // 문제 풀이 로직
        
        cout << "#" << tc << " " << "결과\n";
    }

    return 0;
}
```

---

### 3. 시험장 빈출 실수 5가지 방지 체크리스트
1. **BFS 큐 메모리 초과 방지**: 큐에 `push`하는 순간 즉시 `visited[ny][nx] = true;`를 처리했는가?
2. **다중 테스트케이스(SWEA 필수)**: 테스트 케이스 루프마다 모든 전역 배열/변수를 초기화했는가?
3. **정수 오버플로우 방지**: 최댓값, 곱셈, 거리 합산 결과가 $2 \times 10^9$를 넘길 가능성이 있다면 `long long`을 사용했는가?
4. **Strict Weak Ordering**: `sort`나 `priority_queue`의 비교자에서 `<` 대신 `<=`를 써서 런타임 에러(UB)를 유발하지 않았는가?
5. **격자 경계 체크 순서**: 배열 인덱스 접근 전에 `checkbound(ny, nx)`를 먼저 검사했는가? (`if (checkbound(ny, nx) && map[ny][nx] == 1)`)

---

## 🎯 SWEA & Programmers 추천 문제 로드맵

### 1단계: 감각 되살리기 (기초 구현 & BFS/DFS)
- [SWEA 1954. 달팽이 숫자 (D2)](https://swexpertacademy.com/) : 2차원 방향 회전
- [SWEA 1226. 미로1 (D4)](https://swexpertacademy.com/) : 미로 최단거리/탐색 기본기
- [Programmers 게임 맵 최단거리 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/1844) : 2D BFS 정석
- [Programmers 키패드 누르기 (Lv.1)](https://school.programmers.co.kr/learn/courses/30/lessons/67256) : 맨해튼 거리 & 시뮬레이션

### 2단계: 필수 알고리즘 (백트래킹 & 자료구조 & 투 포인터)
- [SWEA 2806. N-Queen (D3)](https://swexpertacademy.com/) : 백트래킹의 대표작
- [Programmers 피로도 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/87946) : 순열 완전탐색
- [Programmers 더 맵게 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/42626) : 우선순위 큐(힙)
- [Programmers 완주하지 못한 선수 (Lv.1)](https://school.programmers.co.kr/learn/courses/30/lessons/42576) : 해시 맵 활용
- [Programmers 구명보트 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/42885) : 정렬 + 투 포인터

### 3단계: 실전 대비 (DP & 복합 시뮬레이션)
- [SWEA 5215. 햄버거 다이어트 (D3)](https://swexpertacademy.com/) : 0-1 냅색 기초
- [SWEA 1953. 탈주범 검거 (모의역량테스트)](https://swexpertacademy.com/) : 조건부 방향 연결 격자 BFS
- [Programmers 정수 삼각형 (Lv.3)](https://school.programmers.co.kr/learn/courses/30/lessons/43105) : 2D DP
- [Programmers 행렬 테두리 회전하기 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/77485) : 격자 조작 시뮬레이션
- [Programmers 입국심사 (Lv.3)](https://school.programmers.co.kr/learn/courses/30/lessons/43238) : 매개변수 탐색(이분탐색)
