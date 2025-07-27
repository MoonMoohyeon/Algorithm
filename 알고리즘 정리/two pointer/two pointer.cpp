#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;

vector<int> arr;

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, x, input;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> input;
        arr.push_back(input);
    }
    cin >> x;

    sort(arr.begin(), arr.end());

    int fi, li, cnt;
    cnt = fi = 0;
    li = n - 1;

    while (fi < li) {
        if (arr[fi] + arr[li] < x) fi++;
        else if (arr[fi] + arr[li] > x) li--;
        else if (arr[fi] + arr[li] == x) {
            cnt++;
            li--;
            fi++;
        }
    }

    cout << cnt;

    return 0;
}