# 우선순위 큐 (Priority Queue)

힙(Heap) 트리 구조를 기반으로 가장 우선순위가 높은 데이터를 $O(\log N)$에 빠르게 조회/삽입/삭제할 수 있는 자료구조입니다.

---

## 1. 선언 방법 요약

```cpp
// 1. 최대 힙 (기본값, 큰 원소가 top)
priority_queue<int> max_pq;

// 2. 최소 힙 (작은 원소가 top)
priority_queue<int, vector<int>, greater<int>> min_pq;

// 3. 커스텀 구조체
struct Node {
    int w, u;
    // 연산자 오버로딩 시 '<' 정의
    bool operator<(const Node& other) const {
        return w > other.w; // w가 작은 것이 top에 오도록 (최소 힙)
    }
};
priority_queue<Node> pq;
```

---

## 2. 주의사항 (Strict Weak Ordering)
비교자(Comparator) 함수 작성 시 반드시 `<` 또는 `>` 연산자만 사용해야 하며, `<=` 또는 `>=`를 사용하면 동등한 값 비교 시 `true`가 반환되어 힙 불변성이 깨지고 런타임 에러(UB)가 발생합니다.

---

## 3. 추천 연습 문제
- **SWEA**
  - [1249. [S/W 문제해결 응용] 4일차 - 보급로 (D4)](https://swexpertacademy.com/) : 다익스트라 / 우선순위 큐 격자 탐색
- **Programmers**
  - [더 맵게 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/42626) : 최소 힙 활용
  - [디스크 컨트롤러 (Lv.3)](https://school.programmers.co.kr/learn/courses/30/lessons/42627) : 작업 스케줄링 힙
