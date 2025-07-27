#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;


int main(int argc, char** argv) {
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