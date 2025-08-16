#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 결정 문제: 절단기 높이를 'h'로 했을 때, M미터 이상 얻을 수 있는가?
bool check(long long h, long long M, const vector<int>& trees) {
    long long total_wood = 0;
    for (int tree_height : trees) {
        if (tree_height > h) {
            total_wood += tree_height - h;
        }
    }
    return total_wood >= M;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long M;
    cin >> N >> M;

    vector<int> trees(N);
    int max_h = 0;
    for (int i = 0; i < N; ++i) {
        cin >> trees[i];
        if (trees[i] > max_h) {
            max_h = trees[i];
        }
    }

    // --- 매개변수 탐색 (이분 탐색) 시작 ---
    long long low = 0; // 최소 높이는 0
    long long high = max_h; // 최대 높이는 가장 높은 나무의 높이
    long long result = 0;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (check(mid, M, trees)) {
            // [성공!] M미터 이상 얻을 수 있다면, 이건 일단 가능한 답이다.
            // 하지만 우리는 '최대' 높이를 원하므로, 높이를 더 높여본다.
            result = mid;
            low = mid + 1;
        } else {
            // [실패!] M미터 이상 얻을 수 없다면, 너무 높게 자른 것이다.
            // 높이를 낮춰야 한다.
            high = mid - 1;
        }
    }

    cout << result << endl;

    return 0;
}