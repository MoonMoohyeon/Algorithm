# 🌳 트리 순회 (Tree Traversal)

**트리 순회**란 그래프 순회의 한 종류로, 트리의 모든 노드를 한 번씩 체계적으로 방문하는 과정을 말합니다. 어떤 순서로 노드를 방문하느냐에 따라 여러 가지 순회 방법이 있으며, 각각의 방법은 특정 문제를 해결하는 데 유용하게 사용됩니다.

가장 대표적인 순회 방법으로는 **전위 순회**, **중위 순회**, **후위 순회**가 있습니다.

\<br\>

## 예시 트리 구조

아래의 모든 순회 예시는 다음 트리 구조를 기준으로 설명합니다.

```
      (1)
      / \
    (2) (3)
    / \
  (4) (5)
```

\<br\>

-----

## 1\. 전위 순회 (Pre-order Traversal)

**루트(Root) 노드를 가장 먼저** 방문하는 방식입니다.

  * **방문 순서:** **루트** ➔ **왼쪽 서브트리** ➔ **오른쪽 서브트리**
  * **주요 특징 및 사용 예시:**
      * 트리를 복사(copy)할 때 주로 사용됩니다.
      * 폴더/파일 트리 구조를 그대로 출력할 때 유용합니다.
      * 수식 트리(Expression Tree)에서 접두사(Prefix) 표기법을 얻을 수 있습니다.
  * **순회 결과:** `1 ➔ 2 ➔ 4 ➔ 5 ➔ 3`

### C++ 구현 코드

```cpp
void preorderTraversal(Node* root) {
    if (root == nullptr) return;
    
    std::cout << root->data << " "; // 1. 루트 노드 방문
    preorderTraversal(root->left);  // 2. 왼쪽 서브트리 순회
    preorderTraversal(root->right); // 3. 오른쪽 서브트리 순회
}
```

-----

## 2\. 중위 순회 (In-order Traversal)

**루트(Root) 노드를 중간에** 방문하는 방식입니다.

  * **방문 순서:** **왼쪽 서브트리** ➔ **루트** ➔ **오른쪽 서브트리**
  * **주요 특징 및 사용 예시:**
      * \*\*이진 탐색 트리(Binary Search Tree)\*\*를 중위 순회하면, 노드의 값들이 **오름차순으로 정렬**되어 출력됩니다.
  * **순회 결과:** `4 ➔ 2 ➔ 5 ➔ 1 ➔ 3`

### C++ 구현 코드

```cpp
void inorderTraversal(Node* root) {
    if (root == nullptr) return;
    
    inorderTraversal(root->left);  // 1. 왼쪽 서브트리 순회
    std::cout << root->data << " "; // 2. 루트 노드 방문
    inorderTraversal(root->right); // 3. 오른쪽 서브트리 순회
}
```

-----

## 3\. 후위 순회 (Post-order Traversal)

**루트(Root) 노드를 가장 마지막에** 방문하는 방식입니다.

  * **방문 순서:** **왼쪽 서브트리** ➔ **오른쪽 서브트리** ➔ **루트**
  * **주요 특징 및 사용 예시:**
      * 트리의 모든 노드를 안전하게 \*\*삭제(메모리 해제)\*\*할 때 사용됩니다. (자식 노드를 먼저 삭제하고 부모 노드를 삭제)
      * 폴더의 용량을 계산할 때 유용합니다. (하위 폴더들의 용량을 모두 계산한 후, 현재 폴더의 용량을 확정)
      * 수식 트리에서 후위(Postfix) 표기법을 얻을 수 있습니다.
  * **순회 결과:** `4 ➔ 5 ➔ 2 ➔ 3 ➔ 1`

### C++ 구현 코드

```cpp
void postorderTraversal(Node* root) {
    if (root == nullptr) return;
    
    postorderTraversal(root->left);  // 1. 왼쪽 서브트리 순회
    postorderTraversal(root->right); // 2. 오른쪽 서브트리 순회
    std::cout << root->data << " "; // 3. 루트 노드 방문
}
```

-----

## 🧐 한눈에 보기

| 순회 방식        | 방문 순서 (루트 기준)             | 예시 트리 순회 결과 | 주요 사용처                          |
| ---------------- | --------------------------------- | ------------------- | ------------------------------------ |
| **전위 (Pre-order)** | **`루트`** → 왼쪽 → 오른쪽        | `1 2 4 5 3`         | 트리 복사, 접두사 표기법             |
| **중위 (In-order)** | 왼쪽 → **`루트`** → 오른쪽        | `4 2 5 1 3`         | 이진 탐색 트리의 오름차순 정렬       |
| **후위 (Post-order)**| 왼쪽 → 오른쪽 → **`루트`** | `4 5 2 3 1`         | 트리 삭제(메모리 해제), 후위 표기법 |


---

## 💡 코딩테스트 실전 팁 (Cheat Sheet)
1. **순회 순서 한눈에 외우기 (루트의 위치 기준)**:
   - **전위(Pre-order)**: **루트** $\to$ 왼쪽 $\to$ 오른쪽
   - **중위(In-order)**: 왼쪽 $\to$ **루트** $\to$ 오른쪽 (이진 탐색 트리 순회 시 오름차순 정렬됨!)
   - **후위(Post-order)**: 왼쪽 $\to$ 오른쪽 $\to$ **루트** (자식 노드들의 계산 결과를 취합하는 수식 계산, 서브트리 크기 계산에 사용)
2. **배열 기반 완전 이진 트리 표현**:
   - 노드 $i$의 왼쪽 자식: $2i$
   - 노드 $i$의 오른쪽 자식: $2i + 1$
   - 노드 $i$의 부모: $i / 2$

---

## 🎯 추천 연습 문제 (SWEA & Programmers & BOJ)

| 플랫폼 | 문제 번호 및 제목 | 난이도 | 핵심 풀이 포인트 |
| :--- | :--- | :---: | :--- |
| **SWEA** | [1231. [S/W 문제해결 기본] 9일차 - 중위순회](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV140YnqAIECFAYD) | D4 | 완전 이진 트리에서 중위 순회를 수행하여 알파벳 단어를 복원하는 SWEA 대표 문제 |
| **SWEA** | [1232. [S/W 문제해결 기본] 9일차 - 사칙연산](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV1415rKb1ECFAYD) | D4 | 사칙연산 수식 트리를 후위 순회 방식으로 계산하는 대표 응용 문제 |
| **SWEA** | [1233. [S/W 문제해결 기본] 9일차 - 사칙연산 유효성 검사](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV1411qmAIACFAYD) | D4 | 단말 노드는 피연산자, 내부 노드는 연산자여야 한다는 트리 순회 유효성 검사 |
| **백준** | [1991. 트리 순회](https://www.acmicpc.net/problem/1991) | 실버 1 | 전위, 중위, 후위 순회 결과를 모두 출력하는 기본 정석 문제 |
| **Programmers** | [길 찾기 게임](https://school.programmers.co.kr/learn/courses/30/lessons/42892) | Lv.3 | 2019 카카오 블라인드 기출. 좌표로부터 이진 트리 구성 후 전위/후위 순회 결과 반환 |
