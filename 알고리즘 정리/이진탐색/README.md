## 📜 개념 및 원리

이진 탐색의 핵심 원리는 **"나눠서 정복하기(Divide and Conquer)"** 입니다. 마치 사전을 찾을 때, 중간 페이지를 펼쳐보고 찾으려는 단어가 그 앞에 있는지 뒤에 있는지 판단하여 탐색할 부분을 절반으로 줄여나가는 것과 같습니다.

동작 방식은 다음과 같습니다.

1.  탐색 범위의 **중간 원소(middle element)**를 선택합니다.
2.  중간 원소의 값과 찾고자 하는 값을 비교합니다.
    * **값이 같으면** 탐색을 성공적으로 마칩니다.
    * **찾고자 하는 값이 더 작으면**, 중간 원소의 왼쪽 절반(더 작은 값들이 있는 곳)을 새로운 탐색 범위로 지정합니다.
    * **찾고자 하는 값이 더 크면**, 중간 원소의 오른쪽 절반(더 큰 값들이 있는 곳)을 새로운 탐색 범위로 지정합니다.
3.  탐색 범위가 더 이상 존재하지 않을 때까지(시작 지점이 끝 지점보다 커질 때까지) 위 과정을 반복합니다.

이러한 방식 때문에 이진 탐색은 반드시 데이터가 **오름차순 또는 내림차순으로 정렬**되어 있어야 한다는 전제 조건이 있습니다.

---

## ⚙️ 동작 과정

정렬된 배열 `[2, 5, 8, 12, 16, 23, 38, 56, 72, 91]`에서 값 `23`을 찾는 과정을 예시로 살펴보겠습니다.

1.  **1단계**
    * **탐색 범위**: `[2, 5, 8, 12, 16, 23, 38, 56, 72, 91]` (인덱스 0 ~ 9)
    * **중간 값**: 인덱스 `(0 + 9) / 2 = 4`의 값인 `16`
    * **비교**: `16 < 23` 이므로, 탐색 범위를 오른쪽 절반으로 좁힙니다.

2.  **2단계**
    * **새로운 탐색 범위**: `[23, 38, 56, 72, 91]` (인덱스 5 ~ 9)
    * **중간 값**: 인덱스 `(5 + 9) / 2 = 7`의 값인 `56`
    * **비교**: `56 > 23` 이므로, 탐색 범위를 왼쪽 절반으로 좁힙니다.

3.  **3단계**
    * **새로운 탐색 범위**: `[23, 38]` (인덱스 5 ~ 6)
    * **중간 값**: 인덱스 `(5 + 6) / 2 = 5`의 값인 `23`
    * **비교**: `23 == 23` 이므로, 값을 찾았습니다. 탐색을 종료하고 인덱스 `5`를 반환합니다.

---

## ✅ 정확성 증명

이진 탐색의 정확성은 **루프 불변성(Loop Invariant)**을 통해 증명할 수 있습니다. 루프 불변성이란 반복문이 실행되는 동안 항상 참으로 유지되는 조건을 의미합니다.

**루프 불변성 정의**: `while (start <= end)` 루프의 매 반복이 시작될 때, 만약 찾고자 하는 값 `x`가 배열 내에 존재한다면, 그 값은 반드시 현재 탐색 범위인 `arr[start...end]` 내에 존재한다.

1.  **초기 조건 (Initialization)**
    * 루프가 처음 시작될 때, 탐색 범위는 `start = 0`, `end = n-1` (배열 전체)입니다.
    * 만약 값 `x`가 배열에 존재한다면, 당연히 배열 전체 범위 안에 있으므로 루프 불변성은 성립합니다.

2.  **유지 조건 (Maintenance)**
    * 루프의 한 반복이 시작될 때 루프 불변성이 참이라고 가정합니다. (즉, `x`가 존재한다면 `arr[start...end]` 안에 있음)
    * 루프 내에서 `arr[mid]`와 `x`를 비교합니다.
        * `x < arr[mid]`일 경우: 배열이 정렬되어 있으므로, `x`는 `arr[mid...end]` 범위에는 절대 존재할 수 없습니다. 따라서 탐색 범위를 `end = mid - 1`로 좁혀도, `x`가 존재한다면 여전히 새로운 `arr[start...end]` 범위 안에 있게 됩니다.
        * `x > arr[mid]`일 경우: 마찬가지로, `x`는 `arr[start...mid]` 범위에는 절대 존재할 수 없습니다. 탐색 범위를 `start = mid + 1`로 좁혀도, `x`가 존재한다면 여전히 새로운 `arr[start...end]` 범위 안에 있게 됩니다.
    * 따라서 어떤 경우든 탐색 범위가 좁혀진 후에도 루프 불변성은 계속 유지됩니다.

3.  **종료 조건 (Termination)**
    * 루프는 다음 두 가지 경우에 종료됩니다.
        * `arr[mid] == x`: 값을 찾았으므로 올바른 인덱스를 반환하며 종료됩니다.
        * `start > end`: 탐색 범위가 비어있게 됩니다. 루프 불변성에 따라, "만약 `x`가 존재했다면, 비어있는 이 범위 안에 있어야 한다"는 모순에 도달합니다. 이는 `x`가 원래 배열에 존재하지 않았다는 것을 의미합니다. 따라서 `-1`을 반환하는 것은 올바른 동작입니다.

위의 세 단계를 통해 루프 불변성이 항상 유지됨을 알 수 있으며, 따라서 이진 탐색 알고리즘은 항상 정확한 결과를 반환함을 증명할 수 있습니다.