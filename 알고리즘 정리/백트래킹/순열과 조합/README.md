## 백트래킹 (Backtracking)

**백트래킹**은 문제 해결을 위한 알고리즘 전략 중 하나로, 해를 찾는 과정에서 특정 경로가 더 이상 유망하지 않다고 판단되면 그 경로를 포기하고 이전 상태로 돌아가 다른 경로를 탐색하는 방식입니다. 모든 가능한 경우의 수를 탐색하는 \*\*브루트 포스(Brute-force)\*\*와 유사하지만, \*\*가지치기(Pruning)\*\*를 통해 불필요한 탐색을 줄여 효율성을 높인다는 점에서 차이가 있습니다.

주로 재귀 함수를 통해 구현되며, 깊이 우선 탐색(DFS)과 밀접한 관련이 있습니다. 문제의 해결책을 구성하는 각 단계를 거치면서, 현재까지의 선택이 유효한지(promising)를 지속적으로 검사합니다.

-----

### 백트래킹의 핵심 원리

1.  **상태 공간 트리 (State Space Tree)**: 문제 해결 과정의 모든 가능한 상태를 트리 형태로 표현한 것입니다. 백트래킹은 이 트리를 탐색하는 과정으로 볼 수 있습니다.
2.  **유망성 조사 (Promising Check)**: 현재 노드(상태)가 해가 될 가능성이 있는지를 검사하는 과정입니다. 만약 유망하지 않다면, 해당 노드와 그 자식 노드들은 더 이상 탐색하지 않습니다.
3.  **가지치기 (Pruning)**: 유망하지 않은 노드를 탐색에서 제외하는 작업을 의미합니다. 이를 통해 탐색 공간을 크게 줄일 수 있습니다.
4.  **백트랙 (Backtrack)**: 현재 상태에서 더 이상 진행할 수 없을 때, 이전 상태로 되돌아가는 것을 의미합니다.

-----

### 정확성 증명

백트래킹 알고리즘의 정확성은 **상태 공간 트리의 완전한 탐색**에 기반합니다.

  * **기본 구조**: 백트래킹은 기본적으로 깊이 우선 탐색(DFS)과 같은 방식으로 상태 공간 트리의 모든 노드를 방문할 수 있는 구조를 가집니다. 만약 가지치기를 전혀 하지 않는다면, 이는 모든 가능한 해를 검사하는 브루트 포스 탐색과 동일하며, 따라서 반드시 올바른 해를 찾을 수 있습니다.

  * **가지치기의 역할**: 백트래킹의 핵심인 '가지치기'는 해가 될 가능성이 **절대 없는** 경로를 미리 차단하는 역할을 합니다. 즉, 가지치기 과정에서 잘려나가는 노드들은 어차피 최종 해답에 포함될 수 없는 것들입니다. 따라서 유망성을 판단하는 조건(pruning condition)이 정확하다면, 가지치기는 정답을 찾는 데 영향을 주지 않으면서 탐색의 효율성만 높여줍니다.

결론적으로, 백트래킹 알고리즘은 **정확한 가지치기 조건 하에 상태 공간 트리를 효율적으로 탐색하여 모든 유효한 해를 빠짐없이 찾아내는 방법**이므로 그 정확성이 보장됩니다.

-----

### C++ 예제: 순열과 조합

백트래킹의 대표적인 예제로 순열과 조합을 생성하는 코드를 통해 그 원리를 이해할 수 있습니다.

#### 순열 (Permutation)

서로 다른 N개의 원소에서 M개를 선택하여 나열하는 모든 경우의 수를 구합니다. (순서가 중요)

```cpp
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> result;
vector<bool> visited;

void generatePermutation(int count) {
    // M개를 모두 선택했다면 출력
    if (count == m) {
        for (int i = 0; i < m; ++i) {
            cout << result[i] << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = 1; i <= n; ++i) {
        // 이미 사용한 숫자인지 확인 (가지치기)
        if (!visited[i]) {
            visited[i] = true;  // 상태 변경
            result.push_back(i);

            generatePermutation(count + 1); // 다음 단계로 재귀 호출

            result.pop_back();    // 이전 상태로 복구 (백트래킹)
            visited[i] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    visited.resize(n + 1, false);

    generatePermutation(0);

    return 0;
}
```

#### 조합 (Combination)

서로 다른 N개의 원소에서 순서에 상관없이 M개를 선택하는 모든 경우의 수를 구합니다.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> result;

// start 파라미터를 추가하여 이전에 사용한 원소는 고려하지 않도록 함
void generateCombination(int start, int count) {
    // M개를 모두 선택했다면 출력
    if (count == m) {
        for (int i = 0; i < m; ++i) {
            cout << result[i] << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = start; i <= n; ++i) {
        result.push_back(i); // 상태 변경

        generateCombination(i + 1, count + 1); // 다음 원소는 현재 원소보다 큰 수에서 찾음 (가지치기)

        result.pop_back(); // 이전 상태로 복구 (백트래킹)
    }
}

int main() {
    cin >> n >> m;

    generateCombination(1, 0);

    return 0;
}
```

-----

### 백트랙(Backtrack)의 역할: 선택의 철회와 상태 복원

쉽게 비유하자면, **미로 찾기**와 같습니다. 여러 갈림길 중 하나를 선택해 나아가다가 막다른 길을 만나면, 이전 갈림길로 되돌아와 아직 가보지 않은 다른 길을 선택하는 것과 똑같습니다. 이 \*\*"이전 갈림길로 되돌아오는 행위"\*\*가 바로 백트랙입니다.

백트래킹 알고리즘에서 백트랙은 **"하나의 탐색을 마친 후, 이전 상태로 돌아가 새로운 탐색을 시작할 수 있도록 길을 열어주는"** 필수적인 과정입니다.

만약 백트랙 과정이 없다면, 알고리즘은 단 하나의 경로만 탐색하고 다른 가능성은 전혀 고려하지 못한 채 종료될 것입니다.

이전 순열(Permutation) 예제 코드에서 백트랙을 담당하는 부분은 바로 이 두 줄입니다.

```cpp
// ...
generatePermutation(count + 1); // 다음 단계로 재귀 호출

// 여기가 바로 '백트랙' 부분입니다.
result.pop_back();    // (1) 선택했던 숫자 제거
visited[i] = false;   // (2) 해당 숫자를 '방문하지 않음' 상태로 변경
// ...
```

1.  `result.pop_back();`: 재귀 호출을 통해 다음 탐색을 마쳤다면, 현재 경로에 추가했던 숫자(선택)를 다시 **제거**합니다. 예를 들어 `[1, 2]`까지 탐색했다면, `2`를 빼서 다시 `[1]` 상태로 돌아가는 것입니다.
2.  `visited[i] = false;`: `result`에서 숫자를 뺐으니, 해당 숫자는 이제 다른 경로에서 다시 선택될 수 있습니다. 따라서 '방문했다'는 표시(`true`)를 '방문하지 않았다'(`false`)로 **원상 복구**합니다.

이 두 가지 작업을 통해, **재귀 호출 직전의 상태로 완벽하게 되돌아갈 수 있으며**, 이로써 for문이 다음 `i`값을 가지고 새로운 탐색을 시작할 수 있게 됩니다.

-----

### N=3, M=2 순열 예제로 보는 백트랙 과정

`generatePermutation(0)`을 호출했을 때의 동작을 단계별로 따라가 보겠습니다.

**상태:** `result: []`, `visited: [F, F, F, F]`

1.  `generatePermutation(0)` 호출

      * `i = 1` 선택
      * `visited[1] = true` (상태 변경)
      * `result.push_back(1)` -\> `result: [1]` (상태 변경)
      * `generatePermutation(1)` 호출

2.  `generatePermutation(1)` 호출

      * `i = 1`은 `visited[1]`이 `true`이므로 건너뜀
      * `i = 2` 선택
      * `visited[2] = true` (상태 변경)
      * `result.push_back(2)` -\> `result: [1, 2]` (상태 변경)
      * `generatePermutation(2)` 호출

3.  `generatePermutation(2)` 호출

      * `count == m` (2 == 2) 조건을 만족하므로 **`1 2`를 출력**
      * 함수 종료, 이전 호출 지점으로 복귀

4.  **백트랙 (1)**: `generatePermutation(1)`의 `i = 2` 루프로 복귀

      * `result.pop_back()` 실행 -\> `result: [1]` (상태 복원)
      * `visited[2] = false` 실행 (상태 복원)
      * 이제 `i = 2`에 대한 탐색이 끝났으므로 for문 계속 진행

5.  `generatePermutation(1)` 계속 진행

      * `i = 3` 선택
      * `visited[3] = true`
      * `result.push_back(3)` -\> `result: [1, 3]`
      * `generatePermutation(2)` 호출

6.  `generatePermutation(2)` 호출

      * `count == m` 이므로 **`1 3`을 출력**
      * 함수 종료, 복귀

7.  **백트랙 (2)**: `generatePermutation(1)`의 `i = 3` 루프로 복귀

      * `result.pop_back()` 실행 -\> `result: [1]`
      * `visited[3] = false` 실행
      * `i = 3`까지 for문이 모두 끝났으므로 `generatePermutation(1)` 함수 종료

8.  **백트랙 (3)**: `generatePermutation(0)`의 `i = 1` 루프로 복귀

      * `result.pop_back()` 실행 -\> `result: []` (최초 상태로 복원)
      * `visited[1] = false` 실행
      * `i = 1`에 대한 모든 탐색이 끝났으므로 for문 계속 진행

이제 `generatePermutation(0)`의 for문은 `i = 2`부터 다시 시작할 수 있습니다. `visited[1]`이 `false`로 복원되었기 때문에, `2`로 시작하는 `[2, 1]`, `[2, 3]` 등의 새로운 경로를 문제없이 탐색할 수 있게 됩니다.

이처럼 **백트랙**은 하나의 선택으로 파생된 모든 탐색을 마친 뒤, 그 선택 자체를 없었던 일로 하고 이전 상태로 돌아가 다음 선택지를 탐색하게 해주는, 모든 경우의 수를 탐색하기 위한 **필수적인 후처리 작업**이라고 할 수 있습니다.


---

## 💡 코딩테스트 실전 팁 (Cheat Sheet)
1. **순열 vs 조합 템플릿 차이**:
   - **순열**: 순서가 중요하므로 매번 `1`부터 `N`까지 확인하며 `visited` 배열로 중복 선택 방지.
   - **조합**: 순서가 상관없으므로 매개변수로 `start`를 넘겨주어 `for (int i = start; i <= N; i++)`로 항상 다음 숫자만 선택.
2. **백트래킹의 3단계 공식**:
   ```cpp
   visited[i] = true; result.push_back(arr[i]); // 1. 상태 변경
   dfs(depth + 1);                              // 2. 재귀 호출
   result.pop_back(); visited[i] = false;       // 3. 상태 원상 복구 (백트랙)
   ```
3. **시간 복잡도 암기**:
   - 순열: $O(N!)$ ($N \le 10$ 내외에서만 사용 가능)
   - 조합: $O(2^N)$ 또는 $O(\binom{N}{R})$ ($N \le 20$ 내외에서만 사용 가능)

---

## 🎯 추천 연습 문제 (SWEA & Programmers & BOJ)

| 플랫폼 | 문제 번호 및 제목 | 난이도 | 핵심 풀이 포인트 |
| :--- | :--- | :---: | :--- |
| **SWEA** | [5215. 햄버거 다이어트](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWT-lAU6IH4DFAVT) | D3 | 칼로리 제한 이하에서 가장 높은 선호도 점수를 얻는 조합/부분집합 백트래킹 |
| **SWEA** | [4012. [모의 SW 역량테스트] 요리사](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeArG6ACMDFAVU) | 모의역량 | $N$개의 식재료를 $N/2$개씩 두 그룹으로 나누는 조합 백트래킹 후 맛 차이 최소화 |
| **Programmers** | [피로도](https://school.programmers.co.kr/learn/courses/30/lessons/87946) | Lv.2 | 던전 탐험 순서를 순열 백트래킹으로 모두 탐색하여 최대 탐험 던전 수 계산 |
| **Programmers** | [소수 찾기](https://school.programmers.co.kr/learn/courses/30/lessons/42839) | Lv.2 | 숫자 카드로 만들 수 있는 모든 순열을 백트래킹으로 생성 후 소수 판별 |
| **백준** | [15649. N과 M (1)](https://www.acmicpc.net/problem/15649) | 실버 3 | 중복 없는 순열 생성 기본기 훈련 |
| **백준** | [15650. N과 M (2)](https://www.acmicpc.net/problem/15650) | 실버 3 | 오름차순 조합 생성 기본기 훈련 |
