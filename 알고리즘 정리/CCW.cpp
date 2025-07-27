https://jason9319.tistory.com/358
ccw을 이용한 선분 교차

A-B, C-D 두 선분이 존재한다 하자

A-B선분에 대해 점 C, D을 각각 CCW을 한다 하자
1) 두 방향이 서로 반대이다 == 교차 가능성이 존재
2) 두 방향이 서로 일치한다 == 교차 가능성이 없다


1)의 경우 같은 연산을 C-D선분에 대해 점 A, B에 대해서 진행했을때 두방향이 반대이면
선분이 교차한다고 볼 수 있다

CCW(A,B,C)*CCW(A,B,D)<=0 이면서 CCW(C,D,A)*CCW(C,D,B)<=0이면 교차한다고 볼 수 있다.
<< 하지만 A-B ..... C-D와 같은 예외를 없애주어야 하는데
<< A------(C) --------(B)------D와 같이 겹쳐져 있는 경우임을 판별하도록 하면 된다
ex) A.y <= C.y <= B.y or A.y <= D.y <= B.y or B.y <= C.y <= A.y or B.y <= D.y <= A,y


즉, CCW을 선분 A-B에 대해 점 C, D가 오른쪽에 있는지, 왼쪽에 있는지로 접근한것이다(시계방향, 시계반대 방향이 아닌, 점의 위치를 판별하는 용도로 쓰인다)

CCW > 0이면, 왼쪽에, <0이면 오른쪽에 위치한다. (==0이면 평행하다.)
ccw가 양수 == 시계반대 방향
CCW가 음수 == 시계방향



int isIntersect(pair<pair<int, int>, pair<int, int>> x, pair<pair<int, int>, pair<int, int>> y) {
    pair<int, int> a = x.first;
    pair<int, int> b = x.second;
    pair<int, int> c = y.first;
    pair<int, int> d = y.second;
    int ab = ccw(a, b, c)*ccw(a, b, d);
    int cd = ccw(c, d, a)*ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        if (a > b)swap(a, b); // x or y가 크다. a < b유지 << pair의 <, > 연산의 동작을 판별해보자
        if (c > d)swap(c, d); // xor y가 크다. c < d유지.
        return c <= b&&a <= d; // x or y가 크다. a----(c)----b----(d)임을 보장. c-------(a)----(b)-------d도 보장. 
    }
    return ab <= 0 && cd <= 0;
}
