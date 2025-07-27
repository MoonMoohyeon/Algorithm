#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;


int main(int argc, char** argv) {
    cout << "Hello World" << endl;
    // C++ 기본 제공 내장 스트림, 콘솔(표준출력)에 값을 출력
    // 출력 스트림은 버퍼에 보관 후 블록 단위로 묶어서 처리

    cout.flush(); // 버퍼에 있는 데이터를 모두 내보내고 비움
    // 버퍼를 비우는 경우 = endl 등 경계값 도달, 스트림이 스코프를 벗어나 소멸, 버퍼가 가득 찼을 때, 입력 스트림 요청, flush() 호출

    // '<<' 스트림 삽입 연산자
    // 산술 시프트 연산자가 삽입 연산자로 재정의, osream 클래스에 구현
    // 오른쪽 피연산자를 왼쪽 스트림 객체에 삽입한다.
    // 문자열, 기본 데이터 타입 출력, 함수 호출 가능

    // cout 조작 연산자
    int number = 123;

    // #include <iomanip> 헤더파일 필요
    // setfill을 사용하지 않은 경우 (기본값: 공백)
    cout << "Default: |" << setw(10) << number << "|" << endl;

    // setfill을 사용하여 빈 칸을 '0'으로 채우는 경우
    cout << setfill('0'); // 채울 문자를 '0'으로 설정
    cout << "setfill('0'): |" << setw(10) << number << "|" << endl;
    
    // 채우기 설정은 유지되므로 setw만 다시 호출하면 됩니다.
    cout << "Still '0': |" << setw(10) << 45 << "|" << endl;

    // 채울 문자를 '*'로 변경
    cout << setfill('*');
    cout << "setfill('*'): |" << setw(10) << number << "|" << endl;

    cout << setw(6); // setw는 효과가 1회에 한정됨.
    for(int i=0; i<1000; i*=10) {
        cout << i << endl;
    }

    return 0;
}