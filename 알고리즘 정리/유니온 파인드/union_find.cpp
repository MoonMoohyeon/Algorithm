#include <iostream>
#include <string> // string 자료형을 사용하기 위해 필요합니다.
#include <algorithm> // swap 함수를 사용하기 위해 필요합니다.

using namespace std;

// --- 전역 변수 선언 ---
const int MAX = 100001; // 다룰 수 있는 원소의 최대 개수를 정의합니다.
int parent[MAX]; // 각 원소의 부모 노드를 저장하는 배열입니다. parent[i]는 i의 부모를 가리킵니다.
int rk[MAX];     // 트리의 랭크(높이에 대한 추정치)를 저장하는 배열입니다. 'Union by Rank' 최적화에 사용됩니다.

/**
 * @brief 유니온 파인드 자료구조를 초기화하는 함수입니다.
 * @param n 원소의 개수
 */
void init(int n) {
    // 1부터 n까지의 각 원소에 대해 초기 설정을 합니다.
    for (int i = 1; i <= n; i++) {
        // 처음에는 모든 원소가 자기 자신을 부모로 가리킵니다.
        // 이는 각 원소가 자신만을 포함하는 별개의 집합에 속해 있음을 의미합니다.
        parent[i] = i;
        
        // 모든 집합의 초기 랭크는 1입니다. (원소 1개짜리 트리)
        rk[i] = 1;
    }
}

/**
 * @brief 원소 x가 속한 집합의 대표(루트)를 찾는 함수입니다. (Find 연산)
 * @param x 루트를 찾을 원소
 * @return x가 속한 집합의 루트 번호
 */
int find(int x) {
    // 만약 x의 부모가 자기 자신이라면, x는 해당 집합의 루트입니다. (재귀의 기저 사례)
    if (parent[x] == x) {
        return x;
    }
    
    // 재귀적으로 부모를 찾아 올라가면서 루트를 찾습니다.
    // 이때 찾은 루트를 현재 원소 x의 부모로 직접 연결해줍니다. (경로 압축, Path Compression)
    // 이 최적화를 통해 트리의 높이가 낮아져, 다음 find 연산 시 속도가 매우 빨라집니다.
    return parent[x] = find(parent[x]);
}

/**
 * @brief 두 원소 a와 b가 속한 집합을 합치는 함수입니다. (Union 연산)
 * @param a 합칠 집합에 속한 원소
 * @param b 합칠 집합에 속한 다른 원소
 */
void union_sets(int a, int b) {
    // 먼저 각 원소가 속한 집합의 루트를 찾습니다.
    a = find(a);
    b = find(b);
    
    // 두 원소가 이미 같은 집합에 속해 있다면 (루트가 같다면) 아무것도 하지 않습니다.
    if (a != b) {
        // 'Union by Rank' 최적화: 랭크가 더 작은 트리를 랭크가 더 큰 트리에 붙입니다.
        // 이는 전체 트리의 높이가 불필요하게 길어지는 것을 방지하여 효율을 높입니다.
        // 항상 a가 b보다 랭크가 크거나 같도록 조정합니다.
        if (rk[a] < rk[b]) {
            swap(a, b); // a와 b의 역할을 바꿉니다.
        }
        
        // 랭크가 작은 트리의 루트(b)를 랭크가 큰 트리의 루트(a)의 자식으로 만듭니다.
        parent[b] = a;
        
        // 만약 두 트리의 랭크가 같았다면, 합쳐진 후의 트리 랭크는 1 증가합니다.
        if (rk[a] == rk[b]) {
            rk[a]++;
        }
    }
}

int main() {
    // C++ 표준 스트림과 C 표준 입출력의 동기화를 끊어 입출력 속도를 향상시킵니다.
    ios::sync_with_stdio(false);
    // cin과 cout의 묶음을 풀어 입력과 출력이 번갈아 일어날 때의 지연을 줄입니다.
    cin.tie(0);

    int n, m; // n: 원소의 개수, m: 연산의 개수
    cin >> n >> m;
    
    // n개의 원소로 유니온 파인드 자료구조를 초기화합니다.
    init(n);

    // m개의 연산을 하나씩 처리합니다.
    for (int i = 0; i < m; i++) {
        string op; // 연산의 종류 ("union" 또는 "find")
        int a, b;  // 연산에 사용할 두 원소
        cin >> op >> a >> b;

        if (op == "union") {
            // "union" 연산일 경우, a와 b가 속한 집합을 합칩니다.
            union_sets(a, b);
        } else if (op == "find") {
            // "find" 연산일 경우, a와 b가 같은 집합에 속하는지 확인합니다.
            // 두 원소의 루트를 찾아 비교하고, 루트가 같으면 같은 집합입니다.
            if (find(a) == find(b)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}