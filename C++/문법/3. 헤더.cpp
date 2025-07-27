#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
// 전처리기에게 컴파일 전에 소스에 확장하도록 지시
// 표준 입출력을 위한 클래스, 객체, 변수 등이 선언됨

using namespace std;
// std = 과거 스타일과 구분하기 위해 사용하는 이름 공간
// 이름 충돌을 방지하기 위해 개발자가 이름 공간을 생성할 수 있다.
// std:: 접두사를 사용한다.

// 앨리어스 사용, 네임스페이스는 중첩 가능
// namespace MyFTP = MyLibraries ::Networking::
// 범위 지정 연산자 :: 사용
// using  = 네임스페이스 안에 있는 특정한 항목을 가리킴


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

    int input = 0;
    cin >> input; // 표준 입력 장치인 키보드를 연결하는 C++ 입력 스트림 객체
    // 입력 버퍼를 내장, Enter 키가 입력될 때까지 입력된 키를 버퍼에 저장

    string str;
    cin >> str;
    // >> 연산자는 공백, 탭, 엔터에 의해 문자열을 구분

    char buf[100];
    cin.getline(buf, 100, '\n');
    // cin.getline은 char[]에 입력을 size만큼 받음, delimitChar를 만나면 입력 중단. 디폴트는 개행 문자.
    getline(cin, str); // 전역 함수 getline()은 엔터 전까지 라인 전체를 입력 받는다.

    // stringstream = 인메모리 스트림
    // 텍스트 데이터를 메모리에서 스트림 형태로 표현
    // <sstream> 헤더 파일 사용
    double price;
    int quantity;
    stringstream(str) >> price; // stod(str);
    stringstream(str) >> quantity; // stoi(str);
    // 문자열 데이터 타입을 변경할 수 있다.

    // stringstream을 이용한 string 추출
    stringstream ss;
    ss.str(str);
    stringstream ss2(str);
    string data;
    while(ss >> data) {
        cout << data << endl;
    }

    // stringstream을 이용한 string 만들기
    ss << price << quantity; // to_string(price)

    return 0;
}