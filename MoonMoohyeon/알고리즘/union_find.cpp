#include <iostream>
using namespace std;

const int MAX = 100001;
int parent[MAX], rk[MAX];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rk[i] = 1;
    }
}

// Find 연산
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]); // 경로 압축
}

// Union 연산 (랭크 기반 합치기)
void union_sets(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (rk[a] < rk[b]) swap(a, b);
        parent[b] = a;
        if (rk[a] == rk[b]) rk[a]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    init(n);

    for (int i = 0; i < m; i++) {
        string op;
        int a, b;
        cin >> op >> a >> b;

        if (op == "union") {
            union_sets(a, b);
        } else if (op == "find") {
            if (find(a) == find(b)) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}
