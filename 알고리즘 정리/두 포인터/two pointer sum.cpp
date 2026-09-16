#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <climits>
using namespace std;

long long arr[250001];

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    int i = 0, j = 0, cnt = 0;
    long long sum = 0;

    // j(오른쪽 포인터)를 하나씩 늘려가며 sum에 더하고,
    // sum > M이면 i(왼쪽 포인터)를 당겨주면서 부분합 M을 찾는다.
    while (j < N) {
        sum += arr[j];

        while (sum > M && i <= j) {
            sum -= arr[i++];
        }

        if (sum == M) {
            cnt++;
        }

        j++;
    }

    cout << cnt << "\n";


    return 0;
}