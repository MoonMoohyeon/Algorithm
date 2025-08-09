#include <iostream>
#include <string>
#include <vector>

// -------------------------------------------------------------------
// 섹션 구분을 위한 함수
// -------------------------------------------------------------------
void print_divider(const std::string& title) {
    std::cout << "\n// ---------------------------------------------------\n";
    std::cout << "// " << title << "\n";
    std::cout << "// ---------------------------------------------------\n";
}

// dynamic_cast 예제를 위한 클래스 정의
class Base {
public:
    // dynamic_cast는 가상 함수가 하나 이상 포함된 '다형적 클래스'에만 사용 가능합니다.
    virtual void print() const { std::cout << "Base 클래스입니다." << std::endl; }
    // 가상 소멸자는 다형적 클래스의 좋은 습관입니다.
    virtual ~Base() {} 
};

class Derived : public Base {
public:
    void print() const override { std::cout << "Derived 클래스입니다." << std::endl; }
    void unique_derived_method() const { std::cout << "Derived 클래스만의 고유 메소드입니다." << std::endl; }
};

// constexpr 예제를 위한 함수
constexpr int get_compile_time_value(int a, int b) {
    return a * b;
}


int main() {
    /////////////////////////////////////////////////////////////////////
    //
    // PART 1: 참조자 (References)
    //
    /////////////////////////////////////////////////////////////////////

    // -------------------------------------------------------------------
    // 1. 참조 변수와 참조자
    // -------------------------------------------------------------------
    print_divider("1. 참조 변수와 참조자");
    // 참조자는 이미 존재하는 변수에 대한 '별명' 또는 '다른 이름'입니다.
    // 변수 자체의 주소를 공유하므로, 참조자를 수정하면 원본 변수도 수정됩니다.
    int original_value = 10;
    int& ref_value = original_value; // original_value에 대한 참조자(별명) ref_value 선언

    std::cout << "원본 값: " << original_value << std::endl;
    std::cout << "참조자 값: " << ref_value << std::endl;

    ref_value = 20; // 참조자를 통해 값을 변경

    std::cout << "참조자 수정 후 원본 값: " << original_value << std::endl; // 원본 값도 변경됨!


    // -------------------------------------------------------------------
    // 2. 포인터 변수 대상의 참조자
    // -------------------------------------------------------------------
    print_divider("2. 포인터 변수 대상의 참조자");
    int num1 = 100;
    int num2 = 200;

    int* ptr = &num1; // ptr은 num1의 주소를 가리킴
    int*& ref_ptr = ptr; // '포인터 변수 ptr'에 대한 참조자 ref_ptr를 선언 (int* 에 대한 참조)

    std::cout << "ptr이 가리키는 값: " << *ptr << std::endl; // 100 출력

    // 포인터 참조자를 통해 원본 포인터가 가리키는 대상을 변경
    ref_ptr = &num2;

    std::cout << "참조자로 대상 변경 후, ptr이 가리키는 값: " << *ptr << std::endl; // 200 출력


    // -------------------------------------------------------------------
    // 3. const 참조자
    // -------------------------------------------------------------------
    print_divider("3. const 참조자");
    // const 참조자는 '읽기 전용' 별명입니다. 이 참조자를 통해 원본 데이터를 수정할 수 없습니다.
    // 함수에 인자를 전달할 때, 값 복사에 드는 비용을 줄이면서 원본 데이터의 수정을 막기 위해 널리 사용됩니다.
    int non_const_val = 50;
    const int& const_ref = non_const_val;

    std::cout << "const 참조자로 값 읽기: " << const_ref << std::endl;
    // const_ref = 60; // 컴파일 에러! const 참조자로는 값을 수정할 수 없습니다.

    // 또한, const 참조자는 임시 값(리터럴)에 대한 별명을 만들 수 있습니다.
    const int& ref_to_literal = 77;
    std::cout << "리터럴에 대한 const 참조자: " << ref_to_literal << std::endl;
    // int& ref_to_literal_error = 77; // 컴파일 에러! non-const 참조자는 리터럴을 참조할 수 없습니다.


    // -------------------------------------------------------------------
    // 4. 참조자의 선언 가능 범위 (불가능한 참조자 예시)
    // -------------------------------------------------------------------
    print_divider("4. 불가능한 참조자 예시");
    // 1. 참조자는 선언과 동시에 반드시 초기화되어야 합니다.
    // int& no_init_ref; // 컴파일 에러!

    // 2. NULL을 참조할 수 없습니다.
    // int& null_ref = *static_cast<int*>(nullptr); // 매우 위험하며, 미정의 동작을 유발합니다.

    // 3. 함수 내의 지역 변수를 참조자로 반환하면 안 됩니다.
    // 함수가 종료되면 지역 변수는 사라지므로, 반환된 참조자는 '댕글링 참조(dangling reference)'가 되어
    // 존재하지 않는 메모리를 가리키게 되어 매우 위험합니다.
    // (아래와 같은 함수는 절대로 만들면 안 됩니다.)
    /*
    int& dangling_reference_func() {
        int local_var = 10;
        return local_var; // 컴파일 경고! 함수 종료 후 local_var는 소멸됨
    }
    */


    /////////////////////////////////////////////////////////////////////
    //
    // PART 2: 형변환 (Type Casting)
    //
    /////////////////////////////////////////////////////////////////////

    // -------------------------------------------------------------------
    // 1. const_cast
    // -------------------------------------------------------------------
    print_divider("1. const_cast");
    // const_cast는 포인터나 참조자의 const 속성을 제거할 때 사용합니다.
    // 매우 주의해서 사용해야 하며, 원래 const였던 변수의 값을 수정하려 하면 미정의 동작(undefined behavior)이 발생합니다.
    const int const_val = 123;
    const int* const_ptr_val = &const_val;
    
    // const_ptr_val을 통해 *const_ptr_val의 값을 바꿀 수 없음
    // *const_ptr_val = 456; // 컴파일 에러

    int* non_const_ptr = const_cast<int*>(const_ptr_val);
    // non_const_ptr = 456; // 위험! 원래 const였던 변수를 수정 시도. 미정의 동작 발생 가능.
    std::cout << "const_cast로 변환된 포인터를 통해 읽은 값: " << *non_const_ptr << std::endl;


    // -------------------------------------------------------------------
    // 2. static_cast
    // -------------------------------------------------------------------
    print_divider("2. static_cast");
    // static_cast는 컴파일 시간에 타입을 변환하며, 논리적으로 변환 가능한 경우에 사용됩니다. 가장 일반적인 형변환입니다.
    // 예: 숫자 타입 간 변환, 포인터의 상속 관계 변환 등
    double d = 3.14;
    int i = static_cast<int>(d); // double을 int로 변환. 소수점 이하 데이터 손실 발생.
    std::cout << "double " << d << " -> static_cast -> int " << i << std::endl;

    // 부모 -> 자식 클래스로의 다운캐스팅 (안전성 보장 안됨)
    Base* b_ptr = new Derived();
    Derived* d_ptr_static = static_cast<Derived*>(b_ptr); // 컴파일러는 이게 맞다고 믿지만, 런타임에 틀릴 수 있음
    d_ptr_static->unique_derived_method();
    delete b_ptr;


    // -------------------------------------------------------------------
    // 3. reinterpret_cast
    // -------------------------------------------------------------------
    print_divider("3. reinterpret_cast");
    // reinterpret_cast는 비트 수준의 재해석을 수행하는, 가장 위험한 형변환입니다.
    // 전혀 관련 없는 타입 간의 포인터 변환 등 저수준(low-level) 작업에 사용됩니다.
    int some_int = 65;
    int* p_int = &some_int;
    // int 포인터를 char 포인터로 재해석
    char* p_char = reinterpret_cast<char*>(p_int);
    std::cout << "int " << some_int << "의 첫 바이트를 char로 재해석: " << *p_char << " (ASCII 'A')" << std::endl;
    // 시스템(엔디안)에 따라 결과가 다를 수 있습니다.


    // -------------------------------------------------------------------
    // 4. dynamic_cast
    // -------------------------------------------------------------------
    print_divider("4. dynamic_cast");
    // dynamic_cast는 런타임에 타입을 검사하여 안전하게 다운캐스팅을 수행합니다.
    // 다형적 클래스(가상 함수가 있는 클래스)에만 사용할 수 있습니다.
    Base* base_ptr1 = new Derived(); // 부모 포인터가 자식 객체를 가리킴
    Base* base_ptr2 = new Base();    // 부모 포인터가 부모 객체를 가리킴

    // 사례 1: 안전한 다운캐스팅 (성공)
    Derived* derived_ptr1 = dynamic_cast<Derived*>(base_ptr1);
    if (derived_ptr1 != nullptr) {
        std::cout << "base_ptr1은 Derived로 다운캐스팅 성공!" << std::endl;
        derived_ptr1->unique_derived_method();
    }

    // 사례 2: 안전하지 않은 다운캐스팅 (실패)
    Derived* derived_ptr2 = dynamic_cast<Derived*>(base_ptr2);
    if (derived_ptr2 == nullptr) {
        std::cout << "base_ptr2는 Derived 객체가 아니므로 다운캐스팅 실패 (nullptr 반환)" << std::endl;
    }
    
    delete base_ptr1;
    delete base_ptr2;


    /////////////////////////////////////////////////////////////////////
    //
    // PART 3: 타입 관련 기능 (Type features)
    //
    /////////////////////////////////////////////////////////////////////

    // -------------------------------------------------------------------
    // 1. 타입 앨리어스 (Type Alias)
    // -------------------------------------------------------------------
    print_divider("1. 타입 앨리어스");
    // 복잡한 타입 이름에 간단한 별명을 붙여 코드 가독성을 높입니다.
    // C++11부터는 'using'을 사용하는 것이 권장됩니다.
    typedef std::vector<std::string> StringVector_old; // C 스타일 typedef
    using StringVector = std::vector<std::string>;    // C++11 'using' (더 선호됨)

    StringVector names;
    names.push_back("Alice");
    names.push_back("Bob");
    std::cout << "타입 앨리어스 'StringVector' 사용: " << names[0] << std::endl;


    // -------------------------------------------------------------------
    // 2. 변수형 결정 (auto, decltype)
    // -------------------------------------------------------------------
    print_divider("2. 변수형 결정 (auto, decltype)");
    // auto: 변수 선언 시 초기화 값을 보고 컴파일러가 타입을 자동으로 추론합니다.
    auto my_integer = 10;     // int로 추론
    auto my_double = 3.14;    // double로 추론
    auto my_string = std::string("hello"); // std::string으로 추론
    std::cout << "auto로 추론된 타입의 변수: " << my_integer << ", " << my_double << ", " << my_string << std::endl;

    // decltype (declared type): 변수나 표현식의 타입을 그대로 가져와 새 변수를 선언합니다.
    int original_x = 0;
    decltype(original_x) new_x; // new_x는 original_x와 같은 타입(int)으로 선언됨

    const int& ref_x = original_x;
    decltype(ref_x) another_ref_x = original_x; // another_ref_x는 ref_x와 같은 타입(const int&)으로 선언됨
    std::cout << "decltype으로 선언된 변수 타입 테스트 완료" << std::endl;


    // -------------------------------------------------------------------
    // 3. 기호 상수 (const, constexpr)
    // -------------------------------------------------------------------
    print_divider("3. 기호 상수 (const, constexpr)");
    // const: 런타임에 값이 결정될 수 있는 '읽기 전용' 변수(상수)를 만듭니다.
    const int run_time_const = i + 5; // i는 런타임에 값이 정해지므로, run_time_const도 런타임 상수
    std::cout << "const 상수: " << run_time_const << std::endl;
    // run_time_const = 10; // 컴파일 에러!

    // constexpr (constant expression): 컴파일 시간에 값이 결정되는 '진짜' 상수를 만듭니다.
    // 배열 크기, 템플릿 인자 등 컴파일 시간에 값이 확정되어야 하는 곳에 사용할 수 있습니다.
    constexpr int COMPILE_TIME_CONST = 10 * 20;
    int my_array[COMPILE_TIME_CONST]; // OK! 배열 크기는 컴파일 시간 상수여야 함.
    // int my_array2[run_time_const]; // 컴파일 에러! (일부 컴파일러 확장 기능 제외)

    constexpr int calculated_const = get_compile_time_value(5, 4); // constexpr 함수는 컴파일 시간에 실행 가능
    std::cout << "constexpr 상수: " << COMPILE_TIME_CONST << std::endl;
    std::cout << "constexpr 함수 결과: " << calculated_const << std::endl;

    return 0;
}