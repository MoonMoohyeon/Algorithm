#include <iostream>  // cin, cout, endl 등 표준 입출력 스트림을 사용하기 위해 필요합니다.
#include <string>    // std::string, std::getline 등 문자열 관련 기능을 사용하기 위해 필요합니다.
#include <sstream>   // std::stringstream을 사용하여 메모리 기반의 문자열 스트림을 다루기 위해 필요합니다.
#include <limits>    // cin 버퍼를 비울 때, 숫자 한계값을 얻기 위해 사용합니다. (numeric_limits)

// -------------------------------------------------------------------
// 섹션 구분을 위한 도우미 함수
// -------------------------------------------------------------------
void print_divider(const std::string& title) {
    std::cout << "\n// ---------------------------------------------------\n";
    std::cout << "// " << title << "\n";
    std::cout << "// ---------------------------------------------------\n";
}

int main(int argc, char** argv) {
    // using namespace std;
    // C++의 표준 라이브러리 기능들은 'std'라는 이름 공간(namespace) 안에 있습니다.
    // 이 선언은 std::cout, std::cin 대신 cout, cin처럼 짧게 쓰도록 해줍니다.
    using namespace std;

    // -------------------------------------------------------------------
    // 표준 입력 1: >> 연산자 (공백 기준 입력)
    // -------------------------------------------------------------------
    print_divider("표준 입력 1: >> 연산자");

    cout << "숫자와 단어를 공백으로 구분하여 입력하세요 (예: 123 Hello): ";
    
    int input_num = 0;
    string input_str;
    
    // cin은 'character input stream'의 약자로, 키보드로부터 데이터가 들어오는 흐름입니다.
    // '>>' (스트림 추출 연산자)를 사용해 스트림에서 데이터를 꺼내 변수에 저장합니다.
    // >> 연산자는 공백(스페이스, 탭, 엔터)을 만나면 입력을 중단합니다.
    std::cin >> input_number;
    std::cout << "입력한 숫자: " << input_number << std::endl;

    std::string input_word;
    std::cout << "단어를 하나 입력하세요 (공백 없는 단어): ";
    std::cin >> input_word; // 'Hello World'를 입력하면 'Hello'만 저장됨
    std::cout << "입력한 단어: " << input_word << std::endl;


    // -------------------------------------------------------------------
    // 표준 입력 2: getline 함수 (한 줄 전체 입력)
    // -------------------------------------------------------------------
    print_divider("표준 입력 2: getline 함수");

    // !!! 아주 중요한 부분 !!!
    // 이전에 cin >> ... 을 사용하면, 입력 버퍼에는 '엔터' 키에 해당하는 줄바꿈 문자('\n')가 남아있습니다.
    // 이 상태에서 바로 getline을 호출하면, 남아있는 줄바꿈 문자를 읽고 바로 입력을 종료해버립니다.
    // 이를 방지하기 위해 cin.ignore()로 버퍼에 남아있는 불필요한 내용을 비워줘야 합니다.
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // std::cin.ignore(100, '\n'); 

    cout << "\n이제 공백을 포함한 한 줄의 문장을 입력하세요: ";
    string whole_line;

    // std::getline() 함수는 엔터 키를 누르기 전까지의 한 줄 전체를 읽어옵니다.
    // 공백을 포함한 문자열을 입력받을 때 매우 유용합니다.
    getline(cin, whole_line);
    cout << "입력된 문장 전체: \"" << whole_line << "\"" << endl;

    // 참고: C 스타일 문자 배열(char[])을 위한 cin.getline()도 있습니다.
    // char buf[100];
    // cin.getline(buf, 100); // buf 배열에 최대 99개의 문자를 읽어옴
    // 하지만 현대 C++에서는 std::string과 std::getline()을 사용하는 것이 훨씬 안전하고 편리합니다.


    // -------------------------------------------------------------------
    // 문자열 스트림 (stringstream) 활용
    // -------------------------------------------------------------------
    print_divider("문자열 스트림 (stringstream) 활용");

    // stringstream은 파일이나 키보드가 아닌, 메모리상의 문자열을 대상으로 입출력 작업을 하게 해줍니다.
    // 크게 '분석(Parsing)'과 '생성(Formatting)' 두 가지 목적에 매우 유용합니다.

    // --- 활용 1: 문자열에서 데이터 분석/추출 (Parsing) ---
    cout << "\n[활용 1: 문자열 분석하기]" << endl;
    string data = "사과 1500 3.5"; // 상품명, 가격, 무게 데이터가 한 줄에 있음
    stringstream ss1(data); // 분석할 문자열로 stringstream 객체 생성

    string name;
    int price;
    double weight;

    // 마치 cin처럼, 공백을 기준으로 데이터를 차례로 추출하여 각 변수에 저장
    ss1 >> name >> price >> weight;

    cout << "분석된 상품명: " << name << endl;
    cout << "분석된 가격: " << price << "원" << endl;
    cout << "분석된 무게: " << weight << "kg" << endl;

    // while 루프를 이용한 단어 단위 추출
    cout << "\n[while 루프로 단어 단위 추출]" << endl;
    stringstream ss2("이것은 C++ 문자열 스트림 예제입니다.");
    string word;
    while (ss2 >> word) {
        cout << word << endl;
    }

    // --- 활용 2: 여러 데이터를 조합해 하나의 문자열 생성 (Formatting) ---
    cout << "\n[활용 2: 문자열 생성하기]" << endl;
    stringstream ss3; // 비어있는 stringstream 객체 생성

    string item = "노트북";
    int year = 2025;
    
    // 마치 cout처럼, '<<' 연산자로 여러 타입의 데이터를 스트림에 넣습니다.
    ss3 << "제품명: " << item << ", 출시년도: " << year;

    // str() 메소드를 호출하면, 스트림에 쌓인 모든 내용이 하나의 string 객체로 합쳐져 반환됩니다.
    string result_str = ss3.str();
    cout << "생성된 문자열: \"" << result_str << "\"" << endl;

    return 0;
}
