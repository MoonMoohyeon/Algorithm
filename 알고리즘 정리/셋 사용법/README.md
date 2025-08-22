## C++ STL Set 완전 정복: `set`, `unordered_set`, `multiset` 🧠

`set`은 `map`과 매우 유사하지만, **Key-Value 쌍이 아닌 Key 자체를 저장**한다는 점이 가장 큰 차이입니다. 즉, `set`은 **중복되지 않는 원소들의 집합**을 관리하는 자료구조입니다.

`map`이 `{이름: 나이}` 와 같은 사전을 만드는 데 쓰인다면, `set`은 `{참석자 명단}`처럼 값의 존재 여부나 유일성이 중요할 때 사용됩니다.

### 한눈에 보는 핵심 차이점

| 특징 / 자료구조 | `set` | `unordered_set` | `multiset` |
| :--- | :--- | :--- | :--- |
| **원소 중복** | **불가능** | **불가능** | **가능** ⭐ |
| **내부 구현** | 균형 이진 탐색 트리 (RB-Tree) | 해시 테이블 (Hash Table) | 균형 이진 탐색 트리 (RB-Tree) |
| **원소 정렬** | **자동 정렬됨 (커스텀 가능)** | 정렬 안 됨 | **자동 정렬됨 (커스텀 가능)** |
| **탐색/삽입/삭제** | $O(\\log N)$ | 평균 $O(1)$, 최악 $O(N)$ | $O(\\log N)$ |
| **핵심 장점** | **정렬**과 **유일성** 동시 보장, **범위 탐색** | **압도적으로 빠른** 평균 속도 | **정렬**된 상태로 **중복 원소** 관리 |
| **메모리 사용** | `unordered_set`보다 적게 사용 | 노드 외 해시 버킷 등 추가 오버헤드 | `set`과 유사 |
| **이터레이터** | 원소 순회 시 정렬 순서 보장 | 순서 보장 안 됨 | 정렬 순서 보장 |

-----

## 공통 핵심 멤버 함수 🤝

아래 함수들은 `set`, `unordered_set`, `multiset` 모두에서 거의 동일하게 사용됩니다. `set`과 `unordered_set`의 동작은 대부분 같으므로, 속도가 빠른 `unordered_set`을 기준으로 예시를 들겠습니다.

### **1. 원소 추가: `insert()`**

`set` 계열에는 `map`의 `[]` 연산자가 없습니다. 원소에 대응하는 Value가 없기 때문이죠. 따라서 원소를 추가할 때는 반드시 `insert()` 함수를 사용해야 합니다.

`set`에서 유일한 추가 방법인 `insert()`는 생각보다 많은 정보를 제공합니다.
  * **기능**: 집합에 새로운 원소를 추가합니다.
  * **기본 사용법**: `set.insert(value)`
  * **반환값 `pair<iterator, bool>` 심층 분석**: 이 반환값을 제대로 활용하면 코드가 훨씬 효율적으로 변합니다.
      * `iterator`: 삽입된 원소 또는 이미 존재하던 원소를 가리키는 반복자
      * `bool`:
          * `true`: 삽입에 성공 (기존에 원소가 없었음)
          * `false`: 삽입에 실패 (이미 원소가 존재하여 아무것도 하지 않음)



<!-- end list -->

```cpp
#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    std::unordered_set<std::string> user_set;

    // 1. 원소 추가
    user_set.insert("Alice");
    user_set.insert("Bob");

    // 2. "Alice"는 이미 있으므로 삽입에 실패
    auto result = user_set.insert("Alice");

    if (result.second == false) {
        std::cout << *result.first << " is already in the set." << std::endl;
    }

    // 3. 삽입 성공 여부 확인
    if (user_set.insert("Charlie").second) {
        std::cout << "Charlie was successfully inserted." << std::endl;
    }

    std::cout << "Current users: ";
    for (const auto& user : user_set) {
        std::cout << user << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**실행 결과:** (순서는 다를 수 있습니다)

```
Alice is already in the set.
Charlie was successfully inserted.
Current users: Charlie Bob Alice
```

  * **고급 사용법: `insert` 힌트(hint) 활용**
    `set.insert(iterator_hint, value)` 형태로 사용하면, `value`가 삽입될 위치를 `iterator_hint` 근처에서부터 탐색합니다. 만약 힌트가 정확하다면, 탐색 과정 없이 $O(1)$에 가까운 시간 복잡도로 삽입이 가능합니다. 정렬된 데이터를 순차적으로 삽입할 때 매우 유용합니다.

<!-- end list -->

```cpp
std::set<int> s;
auto hint = s.begin();
for (int i = 0; i < 1000; ++i) {
    // s.insert(i) 보다 훨씬 빠름
    hint = s.insert(hint, i); 
}
```

### **2. 원소 검색: `find()` 와 `count()`**

`set`에서 특정 원소가 있는지 확인할 때는 `find()` 또는 `count()`를 사용합니다. `map`에서 `[]` 연산자로 존재 여부를 확인하면 의도치 않은 원소가 생성되는 부작용이 있었지만, `set`에는 `[]`가 없으므로 이런 실수는 원천적으로 방지됩니다.

  * **`find(key)`**: `key`를 검색하여 해당 원소를 가리키는 \*\*반복자(iterator)\*\*를 반환합니다. 못 찾으면 `.end()` 반복자를 반환합니다.
  * **`count(key)`**: `key`와 일치하는 원소의 **개수**를 반환합니다.
      * `set`, `unordered_set`: 중복이 없으므로 항상 **0 또는 1**을 반환합니다.
      * `multiset`: 중복을 허용하므로 **0 이상**의 값을 반환할 수 있습니다.

<!-- end list -->

```cpp
// ... 이전 코드에 이어서
// find()를 사용한 검색 (권장되는 일반적인 방법)
if (user_set.find("Bob") != user_set.end()) {
    std::cout << "Bob is in the user set." << std::endl;
}

// count()를 사용한 검색 (코드가 더 간결함)
if (user_set.count("David") == 0) {
    std::cout << "David is not in the user set." << std::endl;
}
```

### **3. 원소 삭제: `erase()`**

`erase()`는 3가지 오버로딩 형태를 가지며, 상황에 맞게 사용해야 합니다.

1.  **`erase(key)`**: `key`에 해당하는 원소를 삭제하고, \*\*삭제된 원소의 개수(0 또는 1)\*\*를 반환합니다. 가장 안전하고 직관적인 방법입니다.
2.  **`erase(iterator)`**: 특정 위치의 원소를 삭제합니다. **유효하지 않은 이터레이터(예: `.end()`)를 넘기면 미정의 동작(undefined behavior)으로 프로그램이 죽을 수 있으니 주의**해야 합니다.
3.  **`erase(start_iterator, end_iterator)`**: `[start, end)` 범위의 모든 원소를 삭제합니다.

<!-- end list -->

```cpp
std::set<int> s = {1, 2, 3, 4, 5, 6};

// 1. key로 삭제
s.erase(3); // s: {1, 2, 4, 5, 6}

// 2. iterator로 삭제 (find와 연계)
auto it = s.find(5);
if (it != s.end()) {
    s.erase(it); // s: {1, 2, 4, 6}
}

// 3. 범위로 삭제
auto start = s.find(2);
auto end = s.find(6);
s.erase(start, end); // s: {1, 6}
```

-----

### **4. 기타 유용한 함수**

  * `size()`: `set`에 저장된 원소의 개수를 반환합니다.
  * `empty()`: `set`이 비어있는지 확인합니다 (비었으면 `true`).
  * `clear()`: `set`의 모든 원소를 삭제합니다.

-----

## `set` / `multiset` 전용 주요 함수 (정렬 특성 활용) 🌳

`set`과 `multiset`은 원소들이 정렬된 상태로 저장되기 때문에 `map`처럼 강력한 범위 기반 검색이 가능합니다.

### **1. `lower_bound(key)`**

  * **기능**: `key` 값 **이상이 되는 첫 번째 원소**의 반복자를 반환합니다.

### **2. `upper_bound(key)`**

  * **기능**: `key` 값을 **초과하는 첫 번째 원소**의 반복자를 반환합니다.

<!-- end list -->

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> sorted_nums = {10, 20, 30, 40, 50};

    // 30 이상인 첫 원소 찾기 (>= 30)
    auto it_lower = sorted_nums.lower_bound(30);
    if (it_lower != sorted_nums.end()) {
        std::cout << "First element >= 30 is " << *it_lower << std::endl;
    }

    // 30 초과인 첫 원소 찾기 (> 30)
    auto it_upper = sorted_nums.upper_bound(30);
    if (it_upper != sorted_nums.end()) {
        std::cout << "First element > 30 is " << *it_upper << std::endl;
    }

    // key보다 작거나 같은(<=) 마지막 원소 찾기
    int key = 35;
    auto it = sorted_nums.upper_bound(key); // key를 초과하는 첫 위치(40)를 찾고
    if (it != sorted_nums.begin()) {
        it--; // 한 칸 앞으로 이동
        std::cout << "Last element <= " << key << " is " << *it << std::endl;
    }

    return 0;
}
```

**실행 결과:**

```
First element >= 30 is 30
First element > 30 is 40
Last element <= 35 is 30
```

-----

## 컨테이너별 주요 특징 및 주의사항

### **1. `multiset`: 중복 원소 다루기** 🔑

`multiset`은 `set`과 거의 모든 것이 동일하지만 **원소의 중복을 허용**한다는 점이 다릅니다. 이 때문에 특정 원소의 모든 항목을 다룰 때 특별한 방법이 필요합니다.

  * `insert()`: 중복 여부와 상관없이 **항상 원소를 추가**합니다.
  * `count()`: 특정 원소의 **정확한 개수**를 알려줍니다.
  * **`equal_range(key)`**: `multimap`에서처럼, `key`에 해당하는 **모든 원소의 범위를 반환**하는 가장 중요한 함수입니다.
      * `pair.first`: `lower_bound(key)`와 동일
      * `pair.second`: `upper_bound(key)`와 동일

<!-- end list -->

```cpp
#include <iostream>
#include <set>

int main() {
    std::multiset<int> scores;
    scores.insert(85);
    scores.insert(90);
    scores.insert(85); // 중복 삽입
    scores.insert(92);
    scores.insert(85); // 중복 삽입

    std::cout << "Count of 85: " << scores.count(85) << std::endl;

    // 85점인 모든 항목을 순회
    auto range = scores.equal_range(85);
    std::cout << "All scores of 85: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

**실행 결과:**

```
Count of 85: 3
All scores of 85: 85 85 85
```

-----

## `set` / `multiset`만의 무기: 정렬 순서 커스터마이징 🌳

`set`은 기본적으로 오름차순(`std::less`)으로 원소를 정렬합니다. 만약 내림차순으로 정렬하거나, 사용자 정의 객체(struct, class)를 특정 기준에 따라 정렬하고 싶다면 \*\*비교자(Comparator)\*\*를 직접 지정해야 합니다.

### **1. 내림차순 정렬**

`set`을 선언할 때 템플릿 인자로 `std::greater<T>`를 넘겨주면 됩니다.

```cpp
#include <iostream>
#include <set>
#include <functional> // std::greater

int main() {
    std::set<int, std::greater<int>> descending_set;
    descending_set.insert(10);
    descending_set.insert(30);
    descending_set.insert(20);

    std::cout << "Descending set: ";
    for (int x : descending_set) {
        std::cout << x << " "; // 출력: 30 20 10 
    }
    std::cout << std::endl;
    return 0;
}
```

### **2. 사용자 정의 구조체 정렬**

`Point` 구조체를 `y`좌표 기준 오름차순, `y`가 같으면 `x`좌표 기준 오름차순으로 정렬하고 싶다고 가정해 봅시다.

비교 규칙을 담은 구조체(또는 람다)를 만들고, `set` 선언 시 템플릿 인자로 넘겨주어야 합니다.

```cpp
#include <iostream>
#include <set>

struct Point {
    int x, y;
};

// 비교 규칙을 정의하는 구조체
struct PointCmp {
    bool operator()(const Point& a, const Point& b) const {
        if (a.y != b.y) {
            return a.y < b.y; // y좌표 오름차순
        }
        return a.x < b.x; // y가 같으면 x좌표 오름차순
    }
};

int main() {
    std::set<Point, PointCmp> point_set;
    point_set.insert({10, 20});
    point_set.insert({5, 30});
    point_set.insert({15, 20});

    std::cout << "Sorted points (by y, then x):" << std::endl;
    for (const auto& p : point_set) {
        std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
    }
    return 0;
}
```

**실행 결과:**

```
Sorted points (by y, then x):
(10, 20)
(15, 20)
(5, 30)
```

-----

## `unordered_set`의 내부: 해시와 성능 🚀

`unordered_set`의 평균 $O(1)$ 속도는 **해시 테이블** 덕분입니다.

1.  **해싱(Hashing)**: 원소(`key`)를 해시 함수에 넣어 고유한 숫자(해시 값)를 얻습니다.
2.  **버킷(Bucket) 할당**: 해시 값을 배열의 인덱스로 변환하여, 해당 `key`를 배열(버킷)에 저장합니다.
3.  **탐색**: `key`를 찾을 때, 다시 해싱하여 해당 인덱스의 버킷만 확인하면 되므로 속도가 매우 빠릅니다.

### **해시 충돌과 최악의 경우**

서로 다른 `key`가 같은 해시 값을 갖는 것을 \*\*해시 충돌(Hash Collision)\*\*이라고 합니다. 충돌이 발생하면 하나의 버킷에 여러 원소가 연결 리스트(Linked List) 형태로 저장됩니다. 충돌이 매우 심해져 모든 원소가 하나의 버킷에 담기는 최악의 경우, 탐색은 연결 리스트를 처음부터 끝까지 순회하는 것과 같아져 $O(N)$의 시간 복잡도를 갖게 됩니다.

### **성능 튜닝: `load_factor`와 `rehash`**

  * **`load_factor()`**: 현재 `set`이 얼마나 찼는지 알려줍니다. (원소 개수 / 버킷 개수)
  * **`max_load_factor()`**: `load_factor`의 임계값. 이 값을 넘으면 자동으로 버킷 수를 늘리고 모든 원소를 재배치하는 \*\*리해싱(Rehashing)\*\*이 발생합니다.
  * **`rehash(n)`**: 버킷의 수를 최소 `n`개로 강제 설정하여 리해싱을 유도할 수 있습니다. 데이터 개수를 미리 아는 경우, 초반에 `rehash`를 호출해두면 중간에 발생하는 여러 번의 리해싱을 방지하여 성능을 향상시킬 수 있습니다.

<!-- end list -->

```cpp
std::unordered_set<int> s;
// 예상되는 원소 개수가 100만개라면, 미리 공간을 확보
s.rehash(1000000); 
```

-----  

### **2. `unordered_set`: 커스텀 타입 해싱하기** 🚀

`unordered_set`은 `unordered_map`과 마찬가지로 해시 테이블로 구현되어 있습니다. 따라서 Key로 사용하는 타입은 **반드시 해싱이 가능해야 합니다.**

사용자가 직접 만든 `struct`나 `class`를 원소로 사용하려면, 해당 타입에 대한 **해시 함수**와 \*\*비교 연산자(`==`)\*\*를 직접 정의해야 합니다. 이 과정은 `unordered_map`의 Key를 커스터마이징하는 방법과 100% 동일합니다.

```cpp
#include <iostream>
#include <unordered_set>
#include <string>

// 1. 사용할 사용자 정의 타입
struct Point {
    int x;
    int y;
};

// 2. 비교 연산자 정의 (두 객체가 같은지 판단)
bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

// 3. std::hash 템플릿 특수화 (해시 함수 정의)
namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const noexcept {
            size_t h1 = std::hash<int>{}(p.x);
            size_t h2 = std::hash<int>{}(p.y);
            return h1 ^ (h2 << 1); // 두 해시 값을 조합
        }
    };
}

int main() {
    std::unordered_set<Point> visited_points;
    Point p1 = {10, 20};
    visited_points.insert(p1);

    Point p2 = {10, 20};
    if (visited_points.count(p2)) {
        std::cout << "Point (10, 20) has already been visited." << std::endl;
    }
    return 0;
}
```

-----

## 알고리즘 문제 응용법 💡

### **응용 1: 중복 원소 제거 (Removing Duplicates)**

**상황**: 숫자 배열이나 문자열에서 중복된 것을 모두 제거하고 유일한 원소들만 남기고 싶을 때.
**도구**: `set` 또는 `unordered_set` (정렬이 필요하면 `set`, 아니면 `unordered_set`)

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <string>

int main() {
    std::vector<int> nums = {1, 2, 1, 3, 2, 1, 4, 5, 4};

    // vector를 이용해 set을 생성하면 자동으로 중복이 제거됨
    std::set<int> unique_nums(nums.begin(), nums.end());

    std::cout << "Unique sorted numbers: ";
    for (int num : unique_nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

**실행 결과:**

```
Unique sorted numbers: 1 2 3 4 5
```

### **응용 2: 존재 여부 빠르게 확인 (Fast Existence Check)**

**상황**: 어떤 아이템이 주어진 목록(예: 블랙리스트, 회원 명단)에 포함되어 있는지 빠르게 확인해야 할 때.
**도구**: **`unordered_set`** (정렬이 필요 없고 속도가 가장 중요하므로)

```cpp
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
    std::unordered_set<std::string> blacklist = {"spam_user1", "bot_user3", "hacker_x"};
    std::vector<std::string> incoming_users = {"user_a", "spam_user1", "user_b"};

    for (const auto& user : incoming_users) {
        if (blacklist.count(user)) {
            std::cout << "[ALERT] Blacklisted user detected: " << user << std::endl;
        } else {
            std::cout << "[OK] Welcome, " << user << std::endl;
        }
    }
    return 0;
}
```

**실행 결과:**

```
[OK] Welcome, user_a
[ALERT] Blacklisted user detected: spam_user1
[OK] Welcome, user_b
```

### **응용 3: 정렬된 고유 데이터 관리 및 탐색**

**상황**: 사용 가능한 자원 ID 목록을 오름차순으로 관리하고, 특정 ID보다 큰 것 중 가장 작은 ID(즉, 다음으로 사용 가능한 ID)를 찾고 싶을 때.
**도구**: **`set`** (ID가 자동 정렬되어야 하고, 범위 탐색이 필요하므로)

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> available_resources = {101, 105, 203, 301, 400};

    int requested_id = 200;
    auto next_available = available_resources.upper_bound(requested_id);

    if (next_available != available_resources.end()) {
        std::cout << "Requested ID " << requested_id << " is not available." << std::endl;
        std::cout << "Next available resource ID is: " << *next_available << std::endl;
    } else {
        std::cout << "No available resource found after ID " << requested_id << std::endl;
    }
    return 0;
}
```

**실행 결과:**

```
Requested ID 200 is not available.
Next available resource ID is: 203
```

### **최종 요약: 언제 무엇을 쓸까?**

  * **`unordered_set`**: 정렬이 필요 없고, **가장 빠른 속도**로 원소의 **존재 여부만 확인**하면 될 때. (대부분의 경우 **첫 번째 선택지**)
  * **`set`**: 원소들이 **자동으로 정렬**되어야 하거나, 특정 값보다 크거나 작은 원소를 찾는 **범위 기반 검색**이 필요할 때.
  * **`multiset`**: `set`의 모든 기능이 필요하지만, **중복된 원소도 저장**해야 하는 특별한 상황일 때.