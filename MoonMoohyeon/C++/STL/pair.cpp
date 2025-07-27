// pair 사용법

#include<utility>
#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    pair<int,int> p(10,20);

    pair<int,int> p;
    p.first = 2;
    p.second = 3;

    pair<int,int> p = make_pair(10,20); //<< make_pair함수를 이용해서 pair을 만들 수 있다.

    return 0;
}
