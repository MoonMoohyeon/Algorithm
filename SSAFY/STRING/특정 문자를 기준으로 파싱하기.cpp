#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cctype>
#include <cstring>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    string str;
    cin >> str;

    int start = 0;
    int cur = -1;
    int cnt = 0;
    str += "_";
    while(1) {
        cur = str.find('_', start);
        if (cur == -1) break;
        string temp = str.substr(start, cur - start);
        if (temp != "") {
            cnt++;
            cout << cnt << "#" << temp << "\n";
        }
        start = cur + 1;
    }

    return 0;
}