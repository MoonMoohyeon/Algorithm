#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;

int N, M;
vector<int> selected;

void NM(int cnt) {
    if (cnt == M) {
        for (auto i = selected.begin(); i != selected.end(); i++) {
            cout << *i << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = 1; i <= N; i++) {
        selected.push_back(i);
        NM(cnt + 1);
        selected.pop_back();
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    NM(0);

    return 0;
}