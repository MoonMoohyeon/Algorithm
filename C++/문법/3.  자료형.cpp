#include <iostream>
#include <bitset>
using namespace std;

/*
    열거체

    자동 값 할당: 특별히 값을 지정하지 않으면 0부터 시작하여 1씩 자동으로 증가
    암시적 변환: 열거자(예: MONDAY)가 int 타입으로 자동으로 변환
    이름 충돌 가능성: 만약 다른 enum에 SUNDAY와 같은 이름의 열거자를 정의하면 컴파일 오류가 발생
*/

// 요일을 나타내는 열거체
enum Day {
    SUNDAY,     // 0
    MONDAY,     // 1
    TUESDAY,    // 2
    WEDNESDAY,  // 3
    THURSDAY,   // 4
    FRIDAY,     // 5
    SATURDAY    // 6
};

/*
    범위 지정 열거체 

    강력한 타입 검사: enum class 타입은 다른 타입으로 암시적 변환이 불가능합니다. 정수로 사용하려면 static_cast를 통해 명시적으로 변환해야 합니다.
    이름 충돌 방지: 열거자를 사용하려면 Color::RED, Status::RUNNING과 같이 범위(Scope)를 지정해야 하므로 다른 열거체와 이름이 겹치지 않습니다.
    코드 명확성: 코드를 읽는 사람이 Color::BLUE만 봐도 이것이 Color 타입에 속한 값임을 명확히 알 수 있습니다.
*/

// 색상을 나타내는 범위 지정 열거체
enum class Color {
    RED,
    GREEN,
    BLUE
};

int main() {
    // 초기화
    // 복사 초기화
    int i = 10;
    char c = 'A';
    long l = 12345L;
    float f = 3.14f;
    double d = 2.71828;
    bool b = true;

    // 직접 초기화
    int i(10);
    char c('A');
    long l(12345L);
    float f(3.14f);
    double d(2.71828);
    bool b(true);

    // 유니폼 초기화
    // 데이터 손실이 발생할 수 있는 축소 변환(narrowing conversion)을 방지
    // 예를 들어, int 변수에 소수점 값을 넣으려고 하면 컴파일 오류가 발생하여 실수를 방지
    int i{10};
    char c{'A'};
    long l{12345L};
    float f{3.14f};
    double d{2.71828};
    bool b{true};


    // 비트셋
    // 8비트 크기의 bitset을 0으로 초기화
    bitset<8> bits1; 
    cout << "1. 초기 상태: " << bits1 << endl; // 출력: 00000000

    // 특정 위치의 비트 조작
    bits1[1] = 1; // 1번 인덱스 비트를 1로 설정 (오른쪽에서 두 번째)
    bits1.set(4);   // 4번 인덱스 비트를 1로 설정
    cout << "2. 비트 설정 후: " << bits1 << endl; // 출력: 00010010

    // 비트 초기화
    bits1.reset(1); // 1번 인덱스 비트를 0으로 설정
    cout << "3. 비트 초기화 후: " << bits1 << endl; // 출력: 00010000

    // 모든 비트 조작
    bits1.flip();   // 모든 비트를 반전 (0->1, 1->0)
    cout << "4. 모든 비트 반전: " << bits1 << endl; // 출력: 11101111

    // 문자열이나 숫자로 초기화
    bitset<8> bits2("11000101");
    bitset<8> bits3(42); // 10진수 42를 2진수로 변환하여 저장
    cout << "5. 문자열로 초기화: " << bits2 << endl; // 출력: 11000101
    cout << "6. 숫자로 초기화 (42): " << bits3 << endl; // 출력: 00101010

    // 비트 정보 확인
    cout << "7. bits3의 크기: " << bits3.size() << endl; // 출력: 8
    cout << "8. bits3에서 1의 개수: " << bits3.count() << endl; // 출력: 3
    
    if (bits3.any()) { // 하나라도 1인 비트가 있는가?
        cout << "9. bits3에는 1인 비트가 있습니다." << endl;
    }
    
    // 정수형으로 변환
    unsigned long value = bits3.to_ulong();
    cout << "10. bits3를 정수로 변환: " << value << endl; // 출력: 42

    // 열거체
    Day today = MONDAY;

    // 범위 지정 열거체
    Color myColor = Color::BLUE;
    switch (myColor) {
        case Color::RED:
            std::cout << "선택한 색상: 빨강 🔴" << std::endl;
            break;
        case Color::GREEN:
            std::cout << "선택한 색상: 초록 🟢" << std::endl;
            break;
        case Color::BLUE:
            std::cout << "선택한 색상: 파랑 🔵" << std::endl;
            break;
    }

    // 정수로 사용하려면 명시적 캐스팅 필요
    int colorValue = static_cast<int>(myColor);

    return 0;
}