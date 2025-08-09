#include <iostream>
#include <string>   // C++ 문자열 기능을 사용하기 위해 꼭 포함해야 하는 헤더 파일입니다.
#include <vector>   // stringstream 예제에서 사용할 vector 헤더입니다.
#include <sstream>  // stringstream을 사용하기 위해 필요한 헤더입니다.
#include <algorithm> // std::for_each를 사용하기 위해 필요한 헤더입니다.

// 함수 선언
void print_divider();

int main() {
    // C++의 모든 표준 라이브러리 기능은 std 네임스페이스 안에 있습니다.
    // 'using namespace std;'를 사용하면 std::를 생략할 수 있지만,
    // 충돌을 피하기 위해 std:: 접두사를 명시적으로 사용하는 것이 좋은 습관입니다.

    // -------------------------------------------------------------------
    // 1. basic_string 클래스
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "## 1. basic_string 클래스 ##" << std::endl;

    // std::string은 사실 basic_string<char>의 별칭(alias)입니다.
    // 즉, char 타입을 다루는 basic_string 템플릿 클래스라는 의미죠.
    // 다른 문자 타입(wchar_t, char16_t 등)을 위한 문자열도 만들 수 있습니다.
    std::string s1 = "안녕하세요, C++ 세상!"; // 가장 일반적인 문자열 생성 방법
    std::wstring ws1 = L"이것은 와이드 문자열입니다."; // wchar_t 타입의 와이드 문자열

    std::cout << "std::string: " << s1 << std::endl;
    // std::wcout << L"std::wstring: " << ws1 << std::endl; // 와이드 문자열 출력 (환경에 따라 깨질 수 있음)


    // -------------------------------------------------------------------
    // 2. 문자열 비교는 == 연산자로
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "\n## 2. 문자열 비교 (== 연산자) ##" << std::endl;
    std::string str_a = "apple";
    std::string str_b = "banana";
    std::string str_c = "apple";

    // == 연산자는 두 문자열의 내용이 완전히 같은지 비교합니다.
    if (str_a == str_c) {
        std::cout << "'" << str_a << "'와 '" << str_c << "'는 같습니다." << std::endl;
    }

    // != 연산자는 두 문자열이 다른지 비교합니다.
    if (str_a != str_b) {
        std::cout << "'" << str_a << "'와 '" << str_b << "'는 다릅니다." << std::endl;
    }


    // -------------------------------------------------------------------
    // 3. 문자열의 순서는 compare
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "\n## 3. 문자열 순서 비교 (compare) ##" << std::endl;

    // compare() 메소드는 사전 순서를 비교하여 결과를 정수로 반환합니다.
    // - 반환값이 0: 두 문자열이 같음
    // - 반환값이 음수(-): 현재 문자열이 비교 문자열보다 앞에 나옴 (예: "a".compare("b"))
    // - 반환값이 양수(+): 현재 문자열이 비교 문자열보다 뒤에 나옴 (예: "b".compare("a"))
    if (str_a.compare(str_b) < 0) {
        std::cout << "'" << str_a << "'는 사전 순으로 '" << str_b << "'보다 앞에 있습니다." << std::endl;
    }
    if (str_b.compare(str_a) > 0) {
        std::cout << "'" << str_b << "'는 사전 순으로 '" << str_a << "'보다 뒤에 있습니다." << std::endl;
    }
    if (str_a.compare(str_c) == 0) {
        std::cout << "'" << str_a << "'와 '" << str_c << "'는 사전 순으로 같습니다." << std::endl;
    }


    // -------------------------------------------------------------------
    // 4. String 클래스의 C 언어와의 호환성
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "\n## 4. C 언어와의 호환성 ##" << std::endl;

    std::string cpp_string = "C++ 문자열";
    const char* c_string = cpp_string.c_str(); // c_str() 메소드는 C 스타일 문자열 포인터(const char*)를 반환합니다.

    // C 언어의 문자열 함수(printf, strlen 등)에 C++ 문자열을 전달할 때 유용합니다.
    printf("c_str()로 변환된 C 스타일 문자열: %s\n", c_string);

    // C 스타일 문자열로 C++ string 객체를 쉽게 만들 수도 있습니다.
    const char* c_str_literal = "C 스타일 문자열 리터럴";
    std::string new_cpp_string = c_str_literal;
    std::cout << "C 스타일 문자열로 만든 C++ string: " << new_cpp_string << std::endl;


    // -------------------------------------------------------------------
    // 5. String 변환 함수
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "\n## 5. 문자열 변환 함수 ##" << std::endl;

    // 숫자 -> 문자열 변환
    int number = 2025;
    std::string num_to_str = std::to_string(number); // to_string() 함수 사용
    std::cout << "숫자 " << number << " -> 문자열 \"" << num_to_str << "\"" << std::endl;

    // 문자열 -> 숫자 변환
    std::string str_to_num = "12345";
    int parsed_number = std::stoi(str_to_num); // stoi (string to integer) 함수 사용
    double parsed_double = std::stod("3.141592"); // stod (string to double)
    std::cout << "문자열 \"" << str_to_num << "\" -> 숫자 " << parsed_number << std::endl;
    std::cout << "문자열 \"3.141592\" -> 숫자 " << parsed_double << std::endl;

    // (참고) stringstream을 이용한 복합적인 변환
    std::stringstream ss;
    int age = 30;
    std::string name = "홍길동";
    ss << "이름: " << name << ", 나이: " << age; // 스트림에 여러 데이터를 넣고
    std::string result = ss.str(); // str() 메소드로 합쳐진 문자열을 얻습니다.
    std::cout << "stringstream 결과: " << result << std::endl;


    // -------------------------------------------------------------------
    // 6. Capacity (용량) 관련 메소드
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "\n## 6. Capacity 관련 메소드 ##" << std::endl;
    std::string cap_str = "용량 테스트";

    // size() 또는 length(): 문자열의 현재 길이를 반환합니다. (두 함수는 동일하게 동작)
    std::cout << "문자열: \"" << cap_str << "\"" << std::endl;
    std::cout << "size(): " << cap_str.size() << std::endl;
    std::cout << "length(): " << cap_str.length() << std::endl;

    // capacity(): 문자열에 재할당 없이 담을 수 있는 최대 문자 수를 반환합니다.
    std::cout << "capacity(): " << cap_str.capacity() << std::endl;

    // empty(): 문자열이 비어있는지 확인합니다. (길이가 0이면 true)
    std::cout << "empty()? " << (cap_str.empty() ? "네, 비어있습니다." : "아니요, 비어있지 않습니다.") << std::endl;

    std::string empty_str;
    std::cout << "빈 문자열 empty()? " << (empty_str.empty() ? "네, 비어있습니다." : "아니요, 비어있지 않습니다.") << std::endl;

    // reserve(): 메모리를 미리 할당하여 capacity를 늘립니다. 문자열이 길어질 것을 예상할 때 사용하면 성능에 도움이 됩니다.
    cap_str.reserve(100);
    std::cout << "reserve(100) 후 capacity(): " << cap_str.capacity() << std::endl;

    // shrink_to_fit(): 사용하지 않는 여유 메모리를 해제하여 capacity를 size에 가깝게 줄입니다.
    cap_str.shrink_to_fit();
    std::cout << "shrink_to_fit() 후 capacity(): " << cap_str.capacity() << std::endl;


    // -------------------------------------------------------------------
    // 7. Element access (요소 접근) 관련 메소드
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "\n## 7. Element access 관련 메소드 ##" << std::endl;
    std::string access_str = "ABCDE";

    // []: 배열처럼 인덱스로 각 문자에 접근합니다. (범위 검사 없음)
    std::cout << "[] 연산자: " << access_str[0] << ", " << access_str[2] << ", " << access_str[4] << std::endl;

    // at(): 인덱스로 문자에 접근합니다. (범위를 벗어나면 예외 발생)
    std::cout << "at() 메소드: " << access_str.at(1) << ", " << access_str.at(3) << std::endl;
    // std::cout << access_str.at(10); // 주석 해제 시 std::out_of_range 예외 발생

    // front(): 첫 번째 문자를 참조합니다.
    std::cout << "front(): " << access_str.front() << std::endl;

    // back(): 마지막 문자를 참조합니다.
    std::cout << "back(): " << access_str.back() << std::endl;


    // -------------------------------------------------------------------
    // 8. Modifiers (수정자) 메소드
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "\n## 8. Modifiers 메소드 ##" << std::endl;
    std::string mod_str = "C++";
    std::cout << "원본 문자열: \"" << mod_str << "\"" << std::endl;

    // += 연산자 또는 append(): 문자열 뒤에 다른 문자열을 덧붙입니다.
    mod_str += " 프로그래밍";
    std::cout << "+= 연산 후: \"" << mod_str << "\"" << std::endl;
    mod_str.append("은 재미있다!");
    std::cout << "append() 후: \"" << mod_str << "\"" << std::endl;

    // push_back(): 문자열 끝에 문자 하나를 추가합니다.
    mod_str.push_back('!');
    std::cout << "push_back('!') 후: \"" << mod_str << "\"" << std::endl;

    // insert(): 특정 위치에 문자열을 삽입합니다.
    mod_str.insert(3, " (Standard)"); // 3번 인덱스 위치에 문자열 삽입
    std::cout << "insert() 후: \"" << mod_str << "\"" << std::endl;

    // erase(): 특정 위치의 문자들을 삭제합니다.
    mod_str.erase(14, 11); // 14번 인덱스부터 11개의 문자 ("은 재미있다!!") 삭제
    std::cout << "erase() 후: \"" << mod_str << "\"" << std::endl;

    // replace(): 특정 부분을 다른 문자열로 교체합니다.
    mod_str.replace(0, 3, "씨플플"); // 0번 인덱스부터 3개의 문자("C++")를 "씨플플"로 교체
    std::cout << "replace() 후: \"" << mod_str << "\"" << std::endl;

    // pop_back(): 마지막 문자를 제거합니다.
    mod_str.pop_back(); // 마지막의 ')' 제거
    mod_str.pop_back(); // 마지막의 'd' 제거
    std::cout << "pop_back() 2회 후: \"" << mod_str << "\"" << std::endl;

    // clear(): 문자열의 모든 내용을 지웁니다.
    mod_str.clear();
    std::cout << "clear() 후 문자열 길이: " << mod_str.length() << ", 비었는가? " << (mod_str.empty() ? "Yes" : "No") << std::endl;


    // -------------------------------------------------------------------
    // 9. String operations (문자열 연산)
    // -------------------------------------------------------------------
    print_divider();
    std::cout << "\n## 9. String operations ##" << std::endl;
    std::string op_str = "The quick brown fox jumps over the lazy dog.";
    std::cout << "원본 문자열: \"" << op_str << "\"" << std::endl;

    // find(): 특정 문자열이나 문자를 찾고, 그 시작 위치(인덱스)를 반환합니다.
    // 찾지 못하면 std::string::npos 라는 특별한 상수를 반환합니다.
    size_t found_pos = op_str.find("fox");
    if (found_pos != std::string::npos) {
        std::cout << "\"fox\"는 " << found_pos << "번 인덱스에서 발견되었습니다." << std::endl;
    } else {
        std::cout << "\"fox\"를 찾지 못했습니다." << std::endl;
    }

    // rfind(): 문자열의 뒤에서부터 검색합니다.
    size_t last_the_pos = op_str.rfind("the");
    if (last_the_pos != std::string::npos) {
        std::cout << "마지막 \"the\"는 " << last_the_pos << "번 인덱스에서 발견되었습니다." << std::endl;
    }

    // substr(): 부분 문자열을 추출합니다. (시작 위치, 길이)
    std::string sub = op_str.substr(16, 3); // 16번 인덱스부터 3개의 문자 ("fox")
    std::cout << "substr(16, 3) 결과: \"" << sub << "\"" << std::endl;

    // find_first_of(): 인자로 주어진 문자들 중 하나라도 처음으로 발견되는 위치를 찾습니다.
    size_t vowel_pos = op_str.find_first_of("aeiou");
    if (vowel_pos != std::string::npos) {
        std::cout << "첫 번째 모음('" << op_str[vowel_pos] << "')은 " << vowel_pos << "번 인덱스에 있습니다." << std::endl;
    }

    // C++20부터는 starts_with() 와 ends_with() 가 추가되어 매우 편리합니다.
    // (컴파일러와 설정에 따라 지원 여부가 다를 수 있습니다.)
    #if __cplusplus >= 202002L
        std::cout << "starts_with('The'): " << (op_str.starts_with("The") ? "true" : "false") << std::endl;
        std::cout << "ends_with('dog.'): " << (op_str.ends_with("dog.") ? "true" : "false") << std::endl;
    #else
        std::cout << "C++20 starts_with/ends_with는 지원되지 않는 환경입니다." << std::endl;
        // C++20 이전 버전에서는 substr과 compare를 이용해 직접 구현할 수 있습니다.
        if (op_str.rfind("dog.", 0) == 0){
             //...
        }
    #endif

    // -------------------------------------------------------------------
    // 10. 문자열 스트림 (stringstream)
    // -------------------------------------------------------------------
    print_divider();
    
    // stringstream은 실제 파일이나 콘솔이 아닌, 메모리상의 문자열(string)을 입출력 대상으로 삼는 스트림입니다.
    // 크게 두 가지 용도로 매우 유용하게 사용됩니다.

    // 1. 문자열 파싱 (Parsing): 문자열에서 원하는 타입의 데이터를 추출하기
    std::string data_str = "apple 1500 3"; // 상품명, 가격, 수량 정보가 담긴 문자열
    std::stringstream ss(data_str); // stringstream 객체를 만들 때, 분석할 문자열을 전달

    std::string name;
    int price;
    int quantity;

    // 마치 cin을 사용하듯 '>>' 연산자로 공백을 기준으로 데이터를 차례로 추출할 수 있습니다.
    ss >> name >> price >> quantity;
    
    std::cout << "stringstream으로 파싱한 결과:" << std::endl;
    std::cout << "상품명: " << name << std::endl;
    std::cout << "가 격: " << price << "원" << std::endl;
    std::cout << "수 량: " << quantity << "개" << std::endl;

    // 2. 문자열 포매팅 (Formatting): 여러 타입의 데이터를 조합하여 하나의 문자열 만들기
    std::stringstream builder_ss;
    std::string item = "노트북";
    double weight = 1.57;
    int year = 2025;
    
    // 마치 cout을 사용하듯 '<<' 연산자로 여러 데이터를 스트림에 넣습니다.
    builder_ss << "제품명: " << item << ", 무게: " << weight << "kg, 출시년도: " << year;

    // str() 메소드를 호출하면, 지금까지 스트림에 쌓인 모든 내용이 하나의 string 객체로 합쳐져 반환됩니다.
    std::string result_str = builder_ss.str();

    std::cout << "\nstringstream으로 포매팅한 결과:" << std::endl;
    std::cout << result_str << std::endl;
    return 0;
}

// 각 섹션을 구분하기 위한 간단한 함수
void print_divider() {
    std::cout << "--------------------------------------------------------" << std::endl;
}