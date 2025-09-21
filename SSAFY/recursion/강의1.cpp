#include <iostream>
using namespace std;

/*
    함수 : 코드를 기능 단위로 묶은 것, 반환 타입, 매개변수 유무
    스코프 : 파일 스코프, 블록 스코프{}
    전역 변수 : 파일 스코프 내 변수, 지역 변수 : 블록 스코프 내 변수

    재귀 함수 + 연산 전역변수 / 매개변수로 처리
    재귀 함수 : 함수를 호출했던 곳으로 돌아옴
    사전적 정의 : 자기 자신을 참조하여 문제 해결
    컴퓨터 사이언스 : 함수에서 자기 자신을 호출하여 하위 작업을 수행

    반드시 자기 자신 호출, 종료 조건 필수
    종료 조건 : 각 함수마다 넘버링, 특정 N값이 되면 종료한다.

    재귀 함수 -> 반복문 -> 재귀 함수
    이론 상으로만 가능
    ex)
    주사위 굴리기 N = 3
    111 ~ 666
*/

void func() {
    int a = 10;
}

void func(int now) {
    // 기저 조건, 종료 조건
    if(now >= 10) {
        return;
    }
    // 앞으로 가면서 실행
    cout <<"hello" << "\n";
    func(now+1);
    // 다시 돌아오면서 실행
    int de = -1;
}

void mc(int n) {
    if(n >= 5) {
        cout << "[" << n << "]";
        return;
    cout << n << " ";
    mc(n+1);
    cout << n << " ";
    }
}

int N;
int path[10]; // index : n번째, value: 어떤 눈금을 선택했는지
int sum = 0;

void dice(int n) {
    // 1. 기저조건
    if(n >= N) {
        for(int i=0; i<N; i++) {
            cout << path[i] << " ";
        }
        cout << " = " << sum;
        cout << "\n";
        return;
    }
    for(int i=1; i<=6; i++) {
        // 2-1. 전진 실행
        path[n] = i;
        sum += i; // 현재 선택한 눈금의 값을 누적
        // 2. 재귀함수
        dice(n+1);
        // 2-2. 후진 실행
        path[n] = 0;
        sum -= i;
    }
}

int main() {
    int a = 5;
    cout << a;
    func();
    cout << a;

    for(int i=1; i<=6; i++) {
        for(int j=1; j<=6; j++) {
            for(int k=1; k<=6; k++) {
                cout << i << j << k << "\n";
            }
        }
    }

    cin >> N;

    return 0;
}