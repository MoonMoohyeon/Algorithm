/*
https://jason9319.tistory.com/358
CCW(Counter Clock Wise)를 이용한 선분 교차 판별

A-B, C-D 두 선분이 존재한다고 가정:
A-B 선분에 대해 점 C, D를 각각 CCW 연산:
1) 두 방향이 서로 반대이다 == 교차 가능성이 존재
2) 두 방향이 서로 일치한다 == 교차 가능성이 없다

1)의 경우 같은 연산을 C-D 선분에 대해 점 A, B에 대해서 진행했을 때 두 방향이 반대이면 선분이 교차함.
즉, CCW(A,B,C) * CCW(A,B,D) <= 0 이면서 CCW(C,D,A) * CCW(C,D,B) <= 0 이면 교차.

예외: 일직선 상에 위치할 때 (A-B-C-D 처럼 겹쳐있는 경우)
-> a <= d && c <= b 형태로 범위가 겹치는지 추가 확인 필요.

CCW 값의 의미:
CCW > 0 : 반시계 방향 (좌회전)
CCW < 0 : 시계 방향 (우회전)
CCW == 0 : 일직선 (평행)
*/

#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<long long, long long> Point;

// 세 점의 방향성을 판별하는 CCW 함수
int ccw(Point a, Point b, Point c) {
    long long op = (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
    if (op > 0) return 1;      // 반시계
    else if (op < 0) return -1; // 시계
    else return 0;             // 일직선
}

// 두 선분 AB와 CD의 교차 여부를 판별하는 함수
int isIntersect(pair<Point, Point> x, pair<Point, Point> y) {
    Point a = x.first;
    Point b = x.second;
    Point c = y.first;
    Point d = y.second;

    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);

    // 네 점이 일직선 상에 있는 경우 (예외 처리)
    if (ab == 0 && cd == 0) {
        if (a > b) swap(a, b); // a <= b 보장
        if (c > d) swap(c, d); // c <= d 보장
        return (c <= b && a <= d); // 두 선분의 범위가 겹치는지 확인
    }

    return (ab <= 0 && cd <= 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 선분 1: (1, 1) - (5, 5)
    pair<Point, Point> line1 = {{1, 1}, {5, 5}};
    // 선분 2: (1, 5) - (5, 1)
    pair<Point, Point> line2 = {{1, 5}, {5, 1}};

    if (isIntersect(line1, line2)) {
        cout << "선분이 교차합니다.\n";
    } else {
        cout << "선분이 교차하지 않습니다.\n";
    }

    return 0;
}
