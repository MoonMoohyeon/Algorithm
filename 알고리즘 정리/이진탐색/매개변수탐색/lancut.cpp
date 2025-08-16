#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 결정 문제: 랜선 길이를 'len'으로 잘랐을 때, 총 N개 이상을 만들 수 있는가?
bool check(long long len, int N, const vector<int>& cables) {
    long long count = 0;
    // 0으로 나누는 경우를 방지
    if (len == 0) return false;

    for (int cable : cables) {
        count += cable / len; // 각 랜선을 'len'으로 잘랐을 때 몇 개가 나오는지 계산
    }

    return count >= N; // 계산된 개수가 필요한 개수(N)보다 많거나 같으면 true (가능)
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K, N;
    cin >> K >> N;

    vector<int> cables(K);
    long long max_len = 0;
    for (int i = 0; i < K; ++i) {
        cin >> cables[i];
        if (cables[i] > max_len) {
            max_len = cables[i]; // 이분 탐색의 최대 범위 설정을 위해 가장 긴 랜선 길이 저장
        }
    }

    // --- 매개변수 탐색 (이분 탐색) 시작 ---
    long long low = 1;         // 가능한 랜선 길이의 최소값
    long long high = max_len;  // 가능한 랜선 길이의 최대값
    long long result = 0;      // 최종 결과를 저장할 변수

    while (low <= high) {
        long long mid = low + (high - low) / 2; // 중간 길이 계산 (오버플로우 방지)

        // check 함수를 통해 'mid' 길이로 잘랐을 때 N개 이상 만들 수 있는지 확인
        if (check(mid, N, cables)) {
            // [성공!] N개 이상 만들 수 있다면, 이건 일단 가능한 답이다.
            // 하지만 우리는 '최대' 길이를 원하므로, 더 긴 길이도 가능한지 탐색해본다.
            result = mid;       // 현재 길이를 정답 후보로 저장
            low = mid + 1;      // 탐색 범위를 오른쪽(더 긴 길이)으로 옮긴다.
        } else {
            // [실패!] N개 이상 만들 수 없다면, 길이가 너무 긴 것이다.
            // 더 짧은 길이로 잘라야 한다.
            high = mid - 1;     // 탐색 범위를 왼쪽(더 짧은 길이)으로 옮긴다.
        }
    }

    cout << result << endl;

    return 0;
}