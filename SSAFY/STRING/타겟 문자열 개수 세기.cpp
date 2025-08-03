#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    string input[5];
    for (int i = 0; i < 5; i++) {
        cin >> input[i];
    }

    string target = "MCD";

    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        int start, pos;
        start = pos = 0;
        pos = -1;
        while (1) {
            start = input[i].find(target, pos + 1);
            if (start == -1) break;
            cnt++;
            pos = start + 1;
        }
    }
    cout << cnt;

    return 0;
}