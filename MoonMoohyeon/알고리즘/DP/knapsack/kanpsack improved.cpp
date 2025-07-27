#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    // dp[w] : 현재까지 고려한 물건들로 무게 w를 채웠을 때의 최대 가치
    vector<int> dp(K + 1, 0);  // 메모리 사용량을 최적화

    for (int i = 0; i < N; ++i) {
        int W, V;
        cin >> W >> V;

        // 무게 K부터 현재 물건의 무게 W까지만 역순으로 탐색
        // (W보다 작은 무게에는 현재 물건을 넣을 수 없으므로 탐색 불필요)
        for (int w = K; w >= W; --w) {
            // 현재 물건을 '넣지 않는 경우'는 dp[w]의 기존 값.
            // 현재 물건을 '넣는 경우'는 V + dp[w - W].
            // 이 둘 중 더 큰 값으로 dp[w]를 갱신한다.
            dp[w] = max(dp[w], dp[w - W] + V);
        }
    }

    cout << dp[K] << "\n";

    return 0;
}