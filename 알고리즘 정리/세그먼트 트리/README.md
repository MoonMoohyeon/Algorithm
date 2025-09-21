# Segment Tree & Lazy Propagation Segment Tree

## 1\. 세그먼트 트리 (Segment Tree)

### 소개 (Introduction)

**세그먼트 트리**는 배열의 특정 구간에 대한 연산(예: 구간 합, 최댓값, 최솟값 등)을 매우 효율적으로 처리할 수 있는 트리 기반의 자료구조입니다. 🌳

주로 다음과 같은 두 가지 연산을 빠르게 수행하는 데 사용됩니다.

1.  **구간 쿼리 (Range Query)**: 특정 구간 `[L, R]`에 대한 연산 결과를 구합니다.
2.  **점 갱신 (Point Update)**: 배열의 특정 원소 값을 변경합니다.

표준적인 배열에서는 구간 쿼리는 $O(N)$, 점 갱신은 $O(1)$의 시간이 걸리지만, 세그먼트 트리를 사용하면 두 연산 모두 \*\*$O(log N)$\*\*의 시간 복잡도로 수행할 수 있어 매우 효율적입니다.

### 동작 방식 (How it Works)

세그먼트 트리는 이진 트리 형태를 가집니다.

  * **루트 노드 (Root Node)**: 배열의 전체 구간 `[1, N]`에 대한 정보를 가집니다.
  * **중간 노드 (Internal Node)**: 특정 구간 `[start, end]`의 정보를 가지며, 두 자식 노드는 각각 구간을 반으로 나눈 `[start, mid]`와 `[mid+1, end]`를 담당합니다.
  * **리프 노드 (Leaf Node)**: 배열의 각 원소 하나에 대한 정보를 가집니다.

예를 들어 '구간 합'을 구하는 세그먼트 트리에서 부모 노드의 값은 항상 **두 자식 노드의 값의 합**이 됩니다.

`node(start, end) = node(start, mid) + node(mid+1, end)`

#### **주요 연산**

1.  **build (트리 구축)**: 초기 배열을 바탕으로 세그먼트 트리를 재귀적으로 생성합니다. 리프 노드에 배열의 원소를 채워 넣고, 부모 노드들은 자식 노드의 값을 합쳐서 자신의 값을 결정합니다.
2.  **query (구간 쿼리)**: 주어진 구간 `[L, R]`에 대한 값을 구합니다. 현재 노드의 구간이 쿼리 구간에 완전히 포함되면 해당 노드의 값을 반환합니다. 부분적으로 겹치면 자식 노드로 재귀적으로 탐색하여 결과를 조합하고, 겹치지 않으면 연산의 항등원(합의 경우 0)을 반환합니다.
3.  **update (점 갱신)**: 특정 인덱스의 값을 변경합니다. 해당 인덱스를 담당하는 리프 노드를 찾아 값을 갱신한 뒤, 그 노드의 모든 조상 노드들을 루트까지 거슬러 올라가며 값을 다시 계산합니다.

### 구현 방식 (Implementation Analysis)

제공된 `세그먼트트리.cpp` 코드를 바탕으로 주요 함수를 분석합니다.

#### **`build` 함수**

```cpp
void build(int idx, int left, int right) {
    if (left == right) { // 리프 노드인 경우
        tree[idx] = arr[left];
        return;
    }

    int mid = (left + right) / 2;
    build(idx * 2, left, mid); // 왼쪽 자식 빌드
    build(idx * 2 + 1, mid + 1, right); // 오른쪽 자식 빌드
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1]; // 자식 노드 합으로 현재 노드 값 결정
}
```

  * `left == right`는 리프 노드에 도달했음을 의미하며, 이 노드는 `arr[left]` 원소 하나를 담당합니다.
  * 재귀적으로 왼쪽과 오른쪽 서브트리를 구축한 후, 현재 노드(`tree[idx]`)의 값을 두 자식의 합으로 설정합니다.

#### **`update` 함수**

```cpp
void update(int idx, int left, int right, int target, ll value) {
    if (target < left || target > right) { // target이 현재 노드 구간 밖인 경우
        return;
    }
    if (left == right) { // target을 찾은 경우 (리프 노드)
        tree[idx] = value;
        return;
    }

    int mid = (left + right) / 2;
    // target 위치에 따라 재귀적으로 갱신
    update(idx * 2, left, mid, target, value);
    update(idx * 2 + 1, mid + 1, right, target, value);

    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1]; // 자식 변경에 따른 부모 노드 갱신
}
```

  * `target` 인덱스를 포함하는 경로를 따라 리프 노드까지 내려가 값을 변경합니다.
  * 그 후 재귀 호출이 끝나면서, 변경된 리프 노드의 모든 조상 노드들이 새로운 자식 값에 맞춰 갱신됩니다.

#### **`query` 함수**

```cpp
ll query(int idx, int left, int right, int lptr, int rptr) {
    // case 1: 쿼리 구간과 현재 노드 구간이 전혀 겹치지 않을 때
    if (lptr > right || rptr < left) {
        return 0; // 합 연산의 항등원
    }
    // case 2: 현재 노드 구간이 쿼리 구간에 완전히 포함될 때
    if (lptr <= left && right <= rptr) {
        return tree[idx];
    }

    // case 3: 현재 노드 구간과 쿼리 구간이 일부만 겹칠 때
    int mid = (left + right) / 2;
    return query(idx * 2, left, mid, lptr, rptr) + query(idx * 2 + 1, mid + 1, right, lptr, rptr);
}
```

  * 쿼리 로직은 세 가지 경우로 나뉩니다.
    1.  **완전 불일치**: 현재 노드 구간이 쿼리 범위와 겹치지 않으면, 합에 영향을 주지 않는 0을 반환합니다.
    2.  **완전 포함**: 현재 노드 구간이 쿼리 범위에 완전히 속하면, 더 내려갈 필요 없이 미리 계산된 `tree[idx]` 값을 반환합니다. 이것이 세그먼트 트리가 빠른 이유입니다.
    3.  **부분 겹침**: 양쪽 자식 노드로 재귀적으로 쿼리를 보내고, 반환된 두 결과를 합산합니다.

-----

## 2\. 느리게 갱신되는 세그먼트 트리 (Lazy Propagation Segment Tree)

### 소개 (Introduction)

표준 세그먼트 트리는 **점 갱신**에는 효율적이지만, \*\*구간 갱신 (Range Update)\*\*에는 비효율적입니다. 특정 구간 `[L, R]`의 모든 원소에 특정 값을 더하거나 변경하려면 최악의 경우 $O(N)$의 시간이 걸릴 수 있습니다.

\*\*느리게 갱신되는 세그먼트 트리 (Lazy Propagation Segment Tree)\*\*는 이러한 구간 갱신 문제를 해결하기 위해 고안되었습니다. ⚡

핵심 아이디어는 \*\*"변경 사항을 당장 적용하지 않고, 나중에 필요할 때 한꺼번에 처리하자"\*\*는 것입니다. 이를 위해 `lazy`라는 추가 배열을 사용합니다.

  * **구간 쿼리 (Range Query)**: $O(log N)$
  * **구간 갱신 (Range Update)**: $O(log N)$

### 동작 방식 (How it Works)

`lazy` 배열은 각 노드에 "수행해야 할 변경 작업"을 저장합니다.

  * **Range Update**: 구간 `[L, R]`에 값 `D`를 더하는 갱신 요청이 들어왔다고 가정해봅시다.

    1.  트리를 탐색하며 현재 노드 구간이 갱신 구간 `[L, R]`에 완전히 포함되면, **더 이상 자식으로 내려가지 않습니다.**
    2.  대신, 현재 노드의 `lazy` 값에 `D`를 더해주고, 현재 노드의 `tree` 값도 이 변경을 반영하여 갱신합니다. (예: `tree[idx] += (구간 크기) * D`)
    3.  자식 노드들은 아직 변경되지 않은 상태로 남습니다. 이 변경 사항은 나중에 전파(propagate)됩니다.

  * **Lazy Propagation (지연 전파)**: `lazy` 값을 자식 노드로 내려보내는 과정입니다.

    1.  특정 노드에 접근할 때(쿼리 또는 업데이트 시), 해당 노드의 `lazy` 값이 0이 아닌지 확인합니다.
    2.  만약 `lazy` 값이 있다면, 이 값을 **자식 노드들의 `lazy` 값에 더해주고**, 현재 노드의 `tree` 값을 `lazy` 값을 반영하여 갱신합니다.
    3.  모든 작업을 마친 후, 현재 노드의 `lazy` 값은 0으로 초기화합니다.

이 방식을 통해 불필요한 노드 방문을 최소화하여 구간 갱신의 시간 복잡도를 $O(log N)$으로 줄일 수 있습니다.

### 구현 방식 (Implementation Analysis)

제공된 `느리게갱신되는세그먼트트리.cpp` 코드를 분석합니다.

#### **`propagate` 함수**

```cpp
void propagate(int idx, int start, int end) {
    if (lazy[idx] != 0) { // lazy 값이 있다면
        // 1. 현재 노드(tree[idx])에 lazy 값을 반영
        tree[idx] += (end - start + 1) * lazy[idx];
        if (start != end) { // 리프 노드가 아니라면
            // 2. 자식 노드들에게 lazy 값을 전파
            lazy[idx * 2] += lazy[idx];
            lazy[idx * 2 + 1] += lazy[idx];
        }
        // 3. 현재 노드의 lazy 값은 처리 완료했으므로 초기화
        lazy[idx] = 0;
    }
}
```

  * `propagate` 함수는 쿼리 또는 업데이트 함수가 특정 노드에 접근하기 **직전에 항상 호출**되어야 합니다.
  * 이 함수는 현재 노드에 쌓여있던 `lazy` 값을 자신의 `tree` 값에 반영하고, 자식들에게 "너희도 나중에 이만큼 변해야 해"라고 알려주는(자식 `lazy`에 값을 넘겨주는) 역할을 합니다.

#### **`update_range` 함수**

```cpp
void update_range(int idx, int start, int end, int left, int right, ll diff) {
    propagate(idx, start, end); // ★ 항상 먼저 propagate 호출
    if (start > right || end < left) return;

    if (left <= start && end <= right) { // 현재 구간이 업데이트 범위에 완전히 포함될 때
        tree[idx] += (end - start + 1) * diff; // tree 값 즉시 반영
        if (start != end) {
            lazy[idx * 2] += diff; // 자식들에게 lazy 값 추가
            lazy[idx * 2 + 1] += diff;
        }
        return; // ★ 더 이상 내려가지 않음!
    }

    int mid = (start + end) / 2;
    update_range(idx * 2, start, mid, left, right, diff);
    update_range(idx * 2 + 1, mid + 1, end, left, right, diff);
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}
```

  * `propagate`를 먼저 호출하여 이전의 `lazy` 값을 처리합니다.
  * 표준 세그먼트 트리와 가장 큰 차이점은, 현재 노드 구간이 업데이트 범위에 완전히 포함될 때 자식으로 내려가지 않고 `lazy` 값만 갱신하고 종료한다는 점입니다. 이것이 시간 복잡도를 $O(log N)$으로 만드는 핵심입니다.

#### **`query` 함수**

```cpp
ll query(int idx, int start, int end, int left, int right) {
    propagate(idx, start, end); // ★ 항상 먼저 propagate 호출
    if (start > right || end < left) return 0;
    if (left <= start && end <= right) {
        return tree[idx];
    }

    int mid = (start + end) / 2;
    return query(idx * 2, start, mid, left, right) + query(idx * 2 + 1, mid + 1, end, left, right);
}
```

  * `query` 함수의 구조는 표준 세그먼트 트리와 거의 동일합니다.
  * 가장 중요한 차이점은 재귀 탐색을 시작하기 전에 반드시 `propagate`를 호출하여, 현재 노드와 그 자식들이 최신 상태를 반영하도록 만들어야 한다는 것입니다.

-----

## 3\. 요약 및 정확성

| 구분                     | 세그먼트 트리 (Standard) | 느리게 갱신되는 세그먼트 트리 (Lazy Propagation) |
| ------------------------ | ------------------------ | ------------------------------------------------ |
| **주요 목적** | 구간 쿼리, **점** 갱신   | 구간 쿼리, **구간** 갱신                         |
| **구축 (Build)** | $O(N)$                   | $O(N)$                                           |
| **쿼리 (Query)** | $O(log N)$               | $O(log N)$                                       |
| **갱신 (Update)** | $O(log N)$ (점)          | $O(log N)$ (구간)                                |
| **추가 공간** | `tree` 배열              | `tree` 배열 + `lazy` 배열                        |

### 정확성 증명 (Intuitive Proof of Correctness)

느리게 갱신되는 세그먼트 트리가 정확한 이유는 **어떤 노드의 정확한 값이 필요한 순간에는 반드시 그 노드와 그 조상들의 모든 `lazy` 값이 전파되어 반영되기 때문**입니다.

`query(L, R)`를 호출하면, 루트부터 `L`과 `R`에 관련된 노드들까지의 경로가 활성화됩니다. `propagate` 함수는 이 경로상의 모든 노드에 대해 호출되므로, 쿼리 결과에 영향을 미치는 모든 노드들은 탐색 시점에 최신 값을 가지게 됩니다. 따라서 지연되었던 모든 업데이트가 쿼리 결과에는 정확히 반영됩니다.