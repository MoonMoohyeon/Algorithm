#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 결정 문제: 공유기 사이의 최소 거리를 'dist'로 했을 때, C개 이상 설치할 수 있는가?
bool check(int dist, int C, const vector<int>& houses) {
    int count = 1; // 첫 번째 집에는 무조건 설치
    int last_pos = houses[0];

    for (size_t i = 1; i < houses.size(); ++i) {
        if (houses[i] - last_pos >= dist) {
            // 마지막 설치 위치에서 현재 집까지의 거리가 'dist' 이상이면 설치
            count++;
            last_pos = houses[i];
        }
    }
    return count >= C;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, C;
    cin >> N >> C;

    vector<int> houses(N);
    for (int i = 0; i < N; ++i) {
        cin >> houses[i];
    }

    sort(houses.begin(), houses.end()); // 좌표 정렬이 필수

    // --- 매개변수 탐색 (이분 탐색) 시작 ---
    int low = 1; // 최소 거리는 1
    int high = houses.back() - houses.front(); // 최대 거리는 맨 끝 집 사이의 거리
    int result = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (check(mid, C, houses)) {
            // [성공!] C개 이상 설치 가능하다면, 이건 일단 가능한 답이다.
            // 하지만 우리는 '최대' 거리를 원하므로, 거리를 더 늘려본다.
            result = mid;
            low = mid + 1;
        } else {
            // [실패!] C개 이상 설치 불가능하다면, 거리가 너무 먼 것이다.
            // 거리를 좁혀야 한다.
            high = mid - 1;
        }
    }

    cout << result << endl;

    return 0;
}