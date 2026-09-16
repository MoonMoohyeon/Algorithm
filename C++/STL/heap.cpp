#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 1. 기본형 priority_queue
// priority_queue<int> pq; // 기본: 최대 힙 (내림차순, 큰 값이 top)
// priority_queue<int, vector<int>, greater<int>> min_pq; // 최소 힙 (오름차순, 작은 값이 top)

// 2. 구조체와 커스텀 비교 연산자
struct state {
    int a;
    int b;
    state(int a, int b) : a(a), b(b) {}
};

// priority_queue의 비교자(Comparator) 작성 시 주의점:
// 1. Strict Weak Ordering: 반드시 '<' 또는 '>'를 사용해야 하며, '<=' 사용 시 힙 손상 등 미정의 동작(UB) 발생!
// 2. priority_queue는 기본이 less이므로, comp에서 s1.a < s2.a 이면 s2가 우선순위를 갖습니다 (최대 힙 동작).
//    반대로 s1.a > s2.a 이면 s1이 우선순위를 갖습니다 (최소 힙 동작).
struct comp {
    bool operator()(const state &s1, const state &s2) {
        // a가 클수록 우선순위가 높게 (최대 힙)
        if (s1.a == s2.a) {
            return s1.b < s2.b; // a가 같으면 b가 큰 순서
        }
        return s1.a < s2.a;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // --- 1. 기본 int 힙 ---
    cout << "--- 1. 기본 최대 힙 / 최소 힙 ---\n";
    priority_queue<int> max_pq;
    max_pq.push(10);
    max_pq.push(5);
    max_pq.push(20);

    cout << "최대 힙 (큰 순서): ";
    while (!max_pq.empty()) {
        cout << max_pq.top() << " ";
        max_pq.pop();
    }
    cout << "\n";

    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(10);
    min_pq.push(5);
    min_pq.push(20);

    cout << "최소 힙 (작은 순서): ";
    while (!min_pq.empty()) {
        cout << min_pq.top() << " ";
        min_pq.pop();
    }
    cout << "\n\n";

    // --- 2. 구조체 힙 ---
    cout << "--- 2. 커스텀 구조체 힙 ---\n";
    priority_queue<state, vector<state>, comp> pq;

    pq.push(state(10, 5));
    pq.push(state(8, 8));
    pq.push(state(10, 20));

    while (!pq.empty()) {
        cout << "a: " << pq.top().a << ", b: " << pq.top().b << "\n";
        pq.pop();
    }

    return 0;
}