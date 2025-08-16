#include <iostream>
#include <vector>
#include <numeric>   // accumulate 사용
#include <algorithm> // max_element 사용

using namespace std;

// 결정 문제: 인출 금액을 'k'로 했을 때, M번 이하로 인출이 가능한가?
bool check(long long k, int M, const vector<int>& daily_spend) {
    long long current_money = 0;
    int withdrawals = 0;

    for (int spend : daily_spend) {
        // 하루 사용 금액이 인출액보다 크면 그 자체로 불가능
        if (spend > k) return false;

        if (current_money < spend) {
            // 돈이 부족하면 인출
            withdrawals++;
            current_money = k;
        }
        current_money -= spend;
    }
    return withdrawals <= M;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<int> daily_spend(N);
    long long total_spend = 0;
    int max_daily_spend = 0;
    for (int i = 0; i < N; ++i) {
        cin >> daily_spend[i];
        total_spend += daily_spend[i];
        if (daily_spend[i] > max_daily_spend) {
            max_daily_spend = daily_spend[i];
        }
    }

    // --- 매개변수 탐색 (이분 탐색) 시작 ---
    long long low = max_daily_spend; // 최소 인출액은 '하루 최대 사용 금액' 이상이어야 함
    long long high = total_spend;    // 최대 인출액은 '총 사용 금액'이면 충분함
    long long result = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (check(mid, M, daily_spend)) {
            // [성공!] M번 이하로 가능하다면, 이건 일단 가능한 답이다.
            // 하지만 우리는 '최소' 금액을 원하므로, 더 작은 금액도 가능한지 탐색해본다.
            result = mid;       // 현재 금액을 정답 후보로 저장
            high = mid - 1;     // 탐색 범위를 왼쪽(더 작은 금액)으로 옮긴다.
        } else {
            // [실패!] M번 이하로 불가능하다면, 돈이 너무 적은 것이다.
            // 더 많은 금액을 인출해야 한다.
            low = mid + 1;      // 탐색 범위를 오른쪽(더 큰 금액)으로 옮긴다.
        }
    }

    cout << result << endl;

    return 0;
}