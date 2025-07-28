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

    int N, X;
    cin >> N >> X;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    long long sum, max ,cnt;
    max = sum = 0;
    for (int i = 0; i < X; i++) {
        sum += arr[i];
    }
    max = sum;
    cnt = 1;

    for (int i = X; i < N; ++i) {
        sum += arr[i] - arr[i - X];

        if (sum > max) {
            max = sum;
            cnt = 1;
        }
        else if (sum == max) {
            cnt++;
        }
    }

    if (!max) cout << "SAD";
    else cout << max << "\n" << cnt;

    return 0;
}