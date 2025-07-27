#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
    /*
    string 클래스 특징
    1. null 문자 포함되지 않음
    2. 배열처럼 한 문자씩 다룰 수 있음
    3. string 클래스끼리는 + 연산자로 합칠 수 있음
    4. 사전순으로 정렬할 때 편리함
    */

    string str = "SSAFY";
    char a = str[2]; // A 반환
    char b = str.at(3); // F 반환

    str.front(); // 맨 앞 문자 반환
    str.back(); // 맨 끝 문자 반환

    str.size(); // 문자열의 길이 반환, 같은 기능
    str.length(); // 

    int a = 7;
    string str1;
    str1 = to_string(a); // 정수가 문자열로 변환됨
    
    // 문자열 형변환
    stoi(str1);
    stod(str1);
    stof(str1);
    stol(str1);
    
    // 객체 할당 메모리 크기 확인 및 재할당
    str.capacity();
    str.reserve(200);

    // 기타 유용한 함수
    str.empty();
    swap(str, str1);
    str.clear();
    str.append(str1);
    str.find(str1);
    string str2 = str.substr(3, 2);
    str.replace(1,2,str1);
    
    // 문자열 사전 순서 비교 = 부등호로 가능
    cout << (str < str1); // 1 또는 0 반환


    return 0;
}