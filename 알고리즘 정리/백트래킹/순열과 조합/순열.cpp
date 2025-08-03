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
#include <unordered_set>
using namespace std;

int N, M;

int isunique(vector<int> v) {
    unordered_set<int> s;
    for (int value : v) { // v의 각 '값'에 대해 반복
        if (s.count(value)) return 0; // 값이 이미 있는지 확인
        s.insert(value);              // 값을 set에 추가
    }
    return 1;
}

void NM(vector<int> v) {
    /*
        1부터 N까지 중복 없이 M개를 고른 수열
        사전 순으로 증가하는 순서로 출력한다.
     */
    
    if (v.size() == M) {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << "\n";
    }
    else {
        for (int i = 1; i <= N; i++) {
            v.push_back(i);
            if (isunique(v)) {
                NM(v);
            }
            v.pop_back();
        }
    }
}

int main(int argv, char** argc) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    vector<int> v;
    NM(v);


    return 0;
}