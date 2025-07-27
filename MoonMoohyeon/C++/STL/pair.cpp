// pair 사용법

#include<utility> // <utility> 헤더 파일 필요
#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    pair<int,int> p(10,20); // 두 값을 그룹으로 묶는 클래스 템플릿

    pair<int,int> p;
    p.first = 2;
    p.second = 3;
    // 두 값의 타입이 서로 다를 수 있음
    // First, second 라는 데이터 멤버로 접근

    pair<int,int> p = make_pair(10,20); //<< make_pair함수를 이용해서 pair을 만들 수 있다.

    return 0;
}
