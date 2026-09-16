# 기초 다이나믹 프로그래밍 (Basic DP)

복잡한 문제를 작은 부분 문제(Subproblem)로 분할하고, 이미 계산한 결과를 재활용(Memoization/Tabulation)하여 해결하는 기법입니다.

---

## 1. DP 문제 접근 4단계
1. **상태(State) 정의**: `dp[i]`가 정확히 무엇을 의미하는지 문장으로 정의합니다.
   - 예: `dp[i]` = $i$번째 계단까지 도달했을 때 얻을 수 있는 점수의 최댓값.
2. **점화식(Transition) 도출**: 이전 단계들의 상태로 현재 단계를 표현합니다.
   - 예: `dp[i] = max(dp[i-1], dp[i-2]) + cost[i]`
3. **초기 기저값(Base Case) 설정**:
   - `dp[0] = 0`, `dp[1] = cost[1]` 등 가장 작은 단위의 값 직접 채우기.
4. **채우는 순서 결정**:
   - 보통 $i=1$부터 $N$까지 순차적으로 반복문을 실행 (Bottom-up 바텀업 방식 추천).

---

## 2. 코딩테스트 3대 필수 패턴

### ① 1차원 선형 DP
- **계단 오르기 / 피보나치 / 1로 만들기**
- 직전 1~2개 상태만 참조하므로 코드가 간결하고 빠름.

### ② 배낭 문제 / 동전 교환 (Knapsack / Coin Change)
- **동전을 무제한 사용할 수 있는 경우**: 내부 루프를 정방향(`w = coin; w <= target; w++`)으로 순회.
- **물건을 1번만 사용할 수 있는 경우(0-1 Knapsack)**: 중복 방지를 위해 내부 루프를 역방향(`w = target; w >= weight; w--`)으로 순회.

### ③ LIS (최장 증가 부분 수열)
- $N \le 2,500$: $O(N^2)$ 이중 루프 DP.
- $N > 10,000$: $O(N \log N)$ `std::lower_bound`를 활용한 이분탐색 DP.

---

## 3. 추천 연습 문제
- **SWEA**
  - [5215. 햄버거 다이어트 (D3)](https://swexpertacademy.com/) : 0-1 Knapsack 기초
  - [3282. 0/1 Knapsack (D3)](https://swexpertacademy.com/) : 정통 냅색 문제
- **Programmers**
  - [정수 삼각형 (Lv.3)](https://school.programmers.co.kr/learn/courses/30/lessons/43105)
  - [등굣길 (Lv.3)](https://school.programmers.co.kr/learn/courses/30/lessons/42898)
  - [피보나치 수 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/12945)
