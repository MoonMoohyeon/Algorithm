## 공통 핵심 멤버 함수 🤝

아래 함수들은 `map`과 `unordered_map` 모두에서 거의 동일하게 사용됩니다. 대부분의 경우 `unordered_map`을 사용한다고 가정하고 예시를 들겠습니다.

-----

### **1. 원소 추가 및 접근: `[]` 연산자**

가장 직관적이고 많이 쓰이는 방법입니다.

  * **기능**: Key에 해당하는 Value를 **접근**하거나, Key가 없다면 **새로운 원소를 추가**합니다.
  * **주의**: Key가 없을 때 자동으로 `(Key, 기본값)` 쌍을 만들어버리므로, 단순히 존재 여부만 확인할 때는 `find` 함수를 쓰는 것이 더 안전합니다.

<!-- end list -->

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> freq; // {단어, 빈도수}

    // 1. 값 추가 및 수정
    freq["apple"] = 3;      // {"apple", 3} 추가
    freq["banana"] = 5;     // {"banana", 5} 추가
    freq["apple"] = freq["apple"] + 1; // "apple"의 value를 1 증가 -> 4
    
    // 2. 값을 0으로 초기화하며 접근
    freq["orange"]++; // "orange"가 없었으므로 {"orange", 0}으로 생성 후 1 증가 -> {"orange", 1}

    std::cout << "apple: " << freq["apple"] << std::endl;     // 출력: 4
    std::cout << "orange: " << freq["orange"] << std::endl;   // 출력: 1
    
    return 0;
}
```

### **원소 추가 및 접근: `[]` 연산자 vs `insert`**
`[]` 연산자는 `insert`를 완벽하게 대체하지 않습니다. 둘은 비슷해 보이지만 **역할과 동작 방식에 중요한 차이**가 있어서 상황에 맞게 구별해서 써야 합니다.

결론부터 말하면, **`[]` 연산자는 편하게 값을 넣거나 수정할 때** 쓰고, **`insert`는 삽입 성공 여부를 확인하거나 기존 값을 덮어쓰지 않아야 할 때** 사용합니.

-----

### \#\# `[]` 연산자 vs. `insert` 함수의 핵심 차이

| 구분 | `[]` 연산자 | `insert()` 함수 |
| :--- | :--- | :--- |
| **기존 Key 존재 시** | **기존 값을 무조건 덮어쓴다.** | **기존 값을 덮어쓰지 않는다.** |
| **반환값** | Key에 해당하는 **Value의 참조(reference)** | `pair<iterator, bool>` |
| **주요 용도** | 간편한 삽입 및 수정 | **삽입 성공/실패 여부 확인**, 조건부 삽입 |
| **동작 방식** | 1. Key 탐색\<br\>2. 없으면 **(Key, 기본값) 생성**\<br\>3. Value 참조 반환 | 1. Key 탐색\<br\>2. 없으면 (Key, Value) 삽입 |

-----

### \#\# 언제 `insert`를 꼭 써야 할까?

`[]` 연산자만 쓰면 안 되는 대표적인 두 가지 상황이 있습니다.

#### **1. 기존 값을 덮어쓰면 안 될 때**

`[]` 연산자는 Key가 이미 존재하면 값을 **무조건 덮어씁니다**. 만약 Key가 없을 때만 값을 넣고, 있을 때는 기존 값을 유지하고 싶다면 `insert`를 써야 합니다.

`insert`는 삽입에 성공했는지(`true`), 아니면 이미 Key가 존재해서 실패했는지(`false`)를 알려주기 때문입니다.

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> student;

    // [] 연산자 사용
    student[10] = "Alice";  // {10, "Alice"} 삽입
    student[10] = "Bob";    // Key 10이 있으므로 값을 "Bob"으로 덮어씀
    std::cout << "Using []: student[10] is " << student[10] << std::endl;

    // insert 함수 사용
    student.insert({20, "Charlie"}); // {20, "Charlie"} 삽입

    // Key 20이 이미 있으므로 삽입에 실패하고, 기존 값은 변하지 않음
    auto result = student.insert({20, "David"}); 

    std::cout << "Using insert: student[20] is " << student[20] << std::endl;
    
    if (result.second == false) {
        std::cout << "Insertion failed, key 20 already exists." << std::endl;
    }

    return 0;
}
```

**실행 결과:**

```
Using []: student[10] is Bob
Using insert: student[20] is Charlie
Insertion failed, key 20 already exists.
```

#### **2. 단순히 원소의 존재 여부만 확인하고 싶을 때**

`[]` 연산자는 **Key가 없으면 자동으로 `(Key, 기본값)` 쌍을 만들어버리는** 아주 중요한 특징이 있습니다. 이는 의도치 않은 원소 생성을 유발할 수 있습니다.

예를 들어, 맵에 특정 Key가 있는지 확인하려고 아래처럼 코드를 짜면, `"melon"`이 없었더라도 `{ "melon", 0 }`이라는 원소가 새로 생깁니다.

```cpp
std::unordered_map<std::string, int> fruits;
fruits["apple"] = 5;

// "melon"이 있는지 확인하려 했을 뿐인데...
if (fruits["melon"] == 0) {
    // 이 코드는 항상 참이 됩니다. "melon"이 없으면 { "melon", 0 }이 생기기 때문이죠.
}

// 맵 크기를 확인해보면 의도치 않게 2가 되어 있음
std::cout << "Map size: " << fruits.size() << std::endl; // 출력: Map size: 2
```

이런 부작용을 피하려면 \*\*`find()`\*\*나 **`count()`** 함수를 써서 존재 여부를 확인하는 것이 올바른 방법입니다.

### \#\# 정리

  * **`map[key] = value;`**

      * **"이 Key에 이 Value를 넣어줘. 이미 있으면 이걸로 바꿔줘."**
      * 가장 간단하고 직관적이지만, 값을 덮어쓰고 의도치 않은 원소를 생성할 수 있음.

  * **`map.insert({key, value});`**

      * **"이 (Key, Value) 쌍을 넣고 싶어. 근데 Key가 이미 있으면 넣지 말고 알려줘."**
      * 삽입 성공 여부를 명확히 알 수 있고, 기존 값을 보호할 수 있음.

따라서 `[]` 연산자는 `insert`의 편의 버전일 뿐, 서로의 역할이 명확히 다르다고 이해하는 것이 좋습니다.

### **2. 원소 검색: `find()`**

Key가 존재하는지 안전하게 확인할 때 사용합니다.

  * **기능**: Key를 검색하여 해당 원소를 가리키는 \*\*반복자(iterator)\*\*를 반환합니다.
  * **결과**:
      * Key를 찾으면: 해당 원소를 가리키는 반복자 반환.
      * Key를 못 찾으면: `map.end()` 반복자를 반환.

<!-- end list -->

```cpp
// ... 이전 코드에 이어서
if (freq.find("banana") != freq.end()) {
    std::cout << "banana's frequency is " << freq["banana"] << std::endl;
} else {
    std::cout << "banana is not in the map." << std::endl;
}

if (freq.find("grape") == freq.end()) {
    std::cout << "grape is not in the map." << std::endl;
}
```

### **3. 원소 삭제: `erase()`**

  * **기능**: 특정 Key에 해당하는 원소를 삭제합니다.

<!-- end list -->

```cpp
// ... 이전 코드에 이어서
freq.erase("apple"); // Key가 "apple"인 원소 삭제

if (freq.find("apple") == freq.end()) {
    std::cout << "apple was successfully erased." << std::endl;
}
```

### **4. 기타 유용한 함수**

  * `size()`: 맵에 저장된 (Key, Value) 쌍의 개수를 반환합니다.
  * `empty()`: 맵이 비어있는지 확인합니다 (비었으면 `true`).
  * `clear()`: 맵의 모든 원소를 삭제합니다.

-----

## `map` 전용 주요 함수 (정렬 특성 활용) 🌳

`map`은 Key가 정렬되어 있기 때문에 가능한 강력한 함수들입니다.

### **1. `lower_bound(key)`**

  * **기능**: `key` 값 **이상이 되는 첫 번째 원소**의 반복자를 반환합니다. 즉, `key`와 같거나 `key`보다 큰 첫 원소를 찾습니다.

### **2. `upper_bound(key)`**

  * **기능**: `key` 값을 **초과하는 첫 번째 원소**의 반복자를 반환합니다. 즉, `key`보다 큰 첫 원소를 찾습니다.

<!-- end list -->

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> scores;
    scores[85] = "Alice";
    scores[92] = "Bob";
    scores[77] = "Charlie";
    scores[92] = "David"; // Key가 중복되면 Value가 덮어씌워짐 (Bob -> David)

    // 85점 이상인 첫 학생 찾기
    auto it = scores.lower_bound(85);
    if (it != scores.end()) {
        std::cout << "First student with score >= 85 is " << it->second << std::endl; 
        // it->first는 Key(점수), it->second는 Value(이름)
    }

    // 90점 초과인 첫 학생 찾기
    it = scores.upper_bound(90);
    if (it != scores.end()) {
        std::cout << "First student with score > 90 is " << it->second << std::endl;
    }
    return 0;
}
// 출력:
// First student with score >= 85 is Alice
// First student with score > 90 is David
```

아니요, `key` 값보다 작거나(`<`) 작거나 같은(`<=`) 원소를 **한 번에 직접 찾아주는 함수는 없습니다.**

하지만 `lower_bound`와 `upper_bound`의 결과를 응용하면 **쉽게 구현**할 수 있어요. 핵심은 \*\*"기준점을 찾은 뒤, 이터레이터(iterator)를 한 칸 뒤로 옮기는 것"\*\*입니다. ⏪

-----

### \#\# key보다 작은(\<) 마지막 원소 찾기

`key`보다 작은 원소 중 가장 큰 값을 찾으려면, \*\*`key` 값 이상(\>=)이 되는 첫 위치(`lower_bound`)\*\*를 찾은 다음, **그 바로 전 원소**를 보면 됩니다.

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> m = {{10, "A"}, {20, "B"}, {40, "D"}, {50, "E"}};

    int key = 30;

    // 1. key(30) 이상이 되는 첫 위치를 찾는다. -> 40을 가리킴
    auto it = m.lower_bound(key);

    // 2. 이터레이터가 맨 앞이 아니라면, 한 칸 뒤로 이동한다.
    if (it != m.begin()) {
        it--; // 40의 이전 원소인 20을 가리킴
        std::cout << "Key " << key << "보다 작은 마지막 원소는 ";
        std::cout << "{" << it->first << ", " << it->second << "} 입니다." << std::endl;
    } else {
        std::cout << "Key " << key << "보다 작은 원소는 없습니다." << std::endl;
    }

    return 0;
}
```

**실행 결과:**

```
Key 30보다 작은 마지막 원소는 {20, B} 입니다.
```

-----

### \#\# key보다 작거나 같은(\<=) 마지막 원소 찾기

`key`보다 작거나 같은 원소 중 가장 큰 값을 찾으려면, \*\*`key` 값을 초과(\>)하는 첫 위치(`upper_bound`)\*\*를 찾은 다음, **그 바로 전 원소**를 보면 됩니다.

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> m = {{10, "A"}, {20, "B"}, {30, "C"}, {50, "E"}};

    int key = 30;

    // 1. key(30)를 초과하는 첫 위치를 찾는다. -> 50을 가리킴
    auto it = m.upper_bound(key);

    // 2. 이터레이터가 맨 앞이 아니라면, 한 칸 뒤로 이동한다.
    if (it != m.begin()) {
        it--; // 50의 이전 원소인 30을 가리킴
        std::cout << "Key " << key << "보다 작거나 같은 마지막 원소는 ";
        std::cout << "{" << it->first << ", " << it->second << "} 입니다." << std::endl;
    } else {
        std::cout << "Key " << key << "보다 작거나 같은 원소는 없습니다." << std::endl;
    }
    
    return 0;
}
```

**실행 결과:**

```
Key 30보다 작거나 같은 마지막 원소는 {30, C} 입니다.
```

### **핵심 정리**

  * **`< key` 찾기**: `lower_bound(key)`를 찾고 **한 칸 뒤로**
  * **`<= key` 찾기**: `upper_bound(key)`를 찾고 **한 칸 뒤로**

**주의할 점**: 이터레이터를 뒤로 옮기기 전에는 반드시 `it != m.begin()`인지 확인해야 합니다. 만약 `lower_bound`나 `upper_bound`가 첫 번째 원소를 가리키고 있다면, 그 이전 원소는 존재하지 않으므로 에러가 발생합니다.

-----

## 알고리즘 문제 응용법 💡

### **응용 1: 빈도수 계산 (Frequency Counting)**

**상황**: 숫자 배열에서 각 숫자가 몇 번 등장했는지 세고 싶을 때.
**도구**: **`unordered_map`** (정렬이 필요 없고 속도가 가장 중요하므로)

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    std::vector<int> nums = {1, 2, 1, 3, 2, 1, 4, 5, 4};
    std::unordered_map<int, int> counts; // {숫자, 등장 횟수}

    for (int num : nums) {
        counts[num]++;
    }

    // 결과 출력
    for (auto const& [num, count] : counts) { // C++17 구조적 바인딩
        std::cout << num << ": " << count << " times" << std::endl;
    }
    return 0;
}
/* 출력 (순서는 실행할 때마다 다를 수 있음):
5: 1 times
4: 2 times
3: 1 times
2: 2 times
1: 3 times
*/
```

### **응용 2: 룩업 테이블 (Lookup Table) / 자료 매칭**

**상황**: 두 집단의 데이터가 주어질 때, 한쪽 데이터를 기준으로 다른 쪽 데이터를 빠르게 찾고 싶을 때. (예: 참가자 명단과 완주자 명단 비교)
**도구**: **`unordered_map`** (참가자 이름을 Key로 사용해 빠른 조회가 목적)

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main() {
    std::vector<std::string> participant = {"leo", "kiki", "eden"};
    std::vector<std::string> completion = {"eden", "kiki"};
    std::unordered_map<std::string, int> p_map;

    // 참가자 명단을 맵에 넣어 빈도수 체크
    for (const auto& name : participant) {
        p_map[name]++;
    }

    // 완주자 명단을 맵에서 제외
    for (const auto& name : completion) {
        p_map[name]--;
    }

    // 완주하지 못한 선수 찾기
    for (const auto& pair : p_map) {
        if (pair.second > 0) {
            std::cout << "The one who did not finish is " << pair.first << std::endl;
            break;
        }
    }
    return 0;
}
// 출력: The one who did not finish is leo
```

### **응용 3: 정렬된 데이터 관리 및 범위 탐색**

**상황**: 일정(시간, 값)을 저장하고, 특정 시간(값) 이후의 첫 일정을 찾고 싶을 때.
**도구**: **`map`** (시간(Key)을 기준으로 자동 정렬되어야 하므로)

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> schedule; // {시간, 할 일}
    schedule[9] = "Morning Meeting";
    schedule[14] = "Code Review";
    schedule[11] = "Team Lunch";
    schedule[18] = "Project Deadline";

    std::cout << "--- Full Schedule (Sorted by time) ---" << std::endl;
    for (const auto& [time, task] : schedule) {
        std::cout << time << ":00 -> " << task << std::endl;
    }

    int currentTime = 13;
    auto next_event = schedule.upper_bound(currentTime);

    if (next_event != schedule.end()) {
        std::cout << "\nAfter " << currentTime << ":00, the next event is at " 
                  << next_event->first << ":00 (" << next_event->second << ")" << std::endl;
    }
    return 0;
}
/* 출력:
--- Full Schedule (Sorted by time) ---
9:00 -> Morning Meeting
11:00 -> Team Lunch
14:00 -> Code Review
18:00 -> Project Deadline

After 13:00, the next event is at 14:00 (Code Review)
*/
```

### **결론**

  * **속도가 최우선**이고 **정렬이 필요 없다면**? → \*\*`unordered_map`\*\*을 씁니다. (대부분의 경우)
  * **Key를 기준으로 정렬**해야 하거나, **범위 기반 검색**이 필요하다면? → \*\*`map`\*\*을 씁니다.