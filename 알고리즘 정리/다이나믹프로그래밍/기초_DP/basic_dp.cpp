#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
    코딩테스트 필수 기초 DP 3대 유형
    
    1. 1차원 선형 DP: 1로 만들기 / 계단 오르기
    2. 동전 교환 문제 (Coin Change): 최소 동전 개수 구하기
    3. 최장 증가 부분 수열 (LIS - Longest Increasing Subsequence)
       - O(N^2) 기본 DP
       - O(N log N) 이분탐색(lower_bound) 최적화
*/

// 1. 1로 만들기 (1D 선형 DP)
// n을 1로 만드는 최소 연산 횟수 (3으로 나누기, 2로 나누기, 1 빼기)
int make_one(int n) {
    vector<int> dp(n + 1, 0);

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + 1; // 1을 빼는 경우

        if (i % 2 == 0) dp[i] = min(dp[i], dp[i / 2] + 1);
        if (i % 3 == 0) dp[i] = min(dp[i], dp[i / 3] + 1);
    }

    return dp[n];
}

// 2. 동전 교환 (Coin Change)
// 주어진 동전들로 금액 target을 만들 때 필요한 최소 동전 개수 (불가시 -1)
int coin_change(const vector<int>& coins, int target) {
    vector<int> dp(target + 1, 1e9);
    dp[0] = 0; // 0원은 0개 필요

    for (int coin : coins) {
        for (int w = coin; w <= target; w++) {
            if (dp[w - coin] != 1e9) {
                dp[w] = min(dp[w], dp[w - coin] + 1);
            }
        }
    }

    return (dp[target] == 1e9 ? -1 : dp[target]);
}

// 3. LIS - Longest Increasing Subsequence
// 방식 A: O(N^2) DP
int lis_n2(const vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    vector<int> dp(n, 1); // dp[i]: arr[i]를 마지막으로 하는 LIS 길이

    int max_len = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_len = max(max_len, dp[i]);
    }
    return max_len;
}

// 방식 B: O(N log N) 이분탐색(lower_bound) 활용
int lis_n_logn(const vector<int>& arr) {
    vector<int> lis; // LIS의 형태를 유지하는 대체 배열

    for (int x : arr) {
        auto it = lower_bound(lis.begin(), lis.end(), x);
        if (it == lis.end()) {
            lis.push_back(x); // x가 가장 크면 뒤에 추가
        } else {
            *it = x; // x 이상인 첫 위치의 값을 x로 대체
        }
    }
    return lis.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 1로 만들기
    cout << "=== 1. 1로 만들기 ===\n";
    cout << "10을 1로 만드는 최소 연산: " << make_one(10) << "회\n\n"; // 10 -> 9 -> 3 -> 1 (3회)

    // 2. 동전 교환
    cout << "=== 2. 동전 교환 ===\n";
    vector<int> coins = {1, 4, 5};
    int target = 12;
    cout << "동전 {1, 4, 5}로 12원 만들기 최소 동전 개수: " << coin_change(coins, target) << "개\n\n"; // 4*3 = 3개

    // 3. LIS
    cout << "=== 3. LIS (최장 증가 부분 수열) ===\n";
    vector<int> seq = {10, 20, 10, 30, 20, 50};
    cout << "O(N^2) 결과: " << lis_n2(seq) << "\n";
    cout << "O(N log N) 결과: " << lis_n_logn(seq) << "\n"; // {10, 20, 30, 50} -> 4

    return 0;
}
