#include <iostream>
#include <memory> // 스마트 포인터를 사용하기 위해 반드시 포함해야 하는 헤더입니다.
#include <string>

// 모든 스마트 포인터 예제에서 공통으로 사용할 클래스입니다.
// 생성자와 소멸자에서 메시지를 출력하여 객체의 생성과 소멸 시점을 명확히 보여줍니다.
class Resource {
private:
    std::string name;

public:
    Resource(const std::string& n) : name(n) {
        std::cout << "Resource \"" << name << "\" 생성됨" << std::endl;
    }
    ~Resource() {
        std::cout << "Resource \"" << name << "\" 소멸됨 <<<<" << std::endl;
    }
    void greet() const {
        std::cout << "안녕하세요, 저는 \"" << name << "\"입니다." << std::endl;
    }
};

// ## 1. unique_ptr ##
// - 개념: 동적으로 할당된 객체에 대한 '독점적인 소유권'을 가집니다.
//         하나의 객체는 오직 하나의 unique_ptr만이 소유할 수 있습니다.
// - 특징:
//   1. '복사'는 불가능하지만, 소유권을 '이동(move)'시키는 것은 가능합니다.
//   2. 포인터가 범위를 벗어나면(소멸되면) 자동으로 메모리를 해제합니다.
//   3. 일반 포인터(raw pointer)와 성능 차이가 거의 없어 가볍습니다.
void demonstrate_unique_ptr() {
    std::cout << "\n--- unique_ptr 예제 시작 ---\n" << std::endl;

    // std::make_unique를 사용하여 Resource 객체를 생성하고 unique_ptr로 관리합니다.
    // 이것이 가장 안전하고 권장되는 방법입니다.
    std::unique_ptr<Resource> u_ptr1 = std::make_unique<Resource>("독점 자원 1");

    // 일반 포인터처럼 -> 연산자로 멤버 함수에 접근할 수 있습니다.
    u_ptr1->greet();

    // 복사 시도: 아래 코드의 주석을 해제하면 컴파일 에러가 발생합니다.
    // std::unique_ptr<Resource> u_ptr2 = u_ptr1; // 컴파일 에러!

    // 소유권 이전: std::move를 사용하여 u_ptr1의 소유권을 u_ptr3으로 옮깁니다.
    std::unique_ptr<Resource> u_ptr3 = std::move(u_ptr1);
    
    std::cout << "소유권이 u_ptr3으로 이전되었습니다." << std::endl;

    // 소유권을 넘겨준 u_ptr1은 이제 아무것도 가리키지 않는 nullptr 상태가 됩니다.
    if (!u_ptr1) {
        std::cout << "u_ptr1은 이제 비어있습니다." << std::endl;
    }

    // u_ptr3이 객체를 소유하고 있으므로, 이를 통해 멤버 함수를 호출할 수 있습니다.
    u_ptr3->greet();
    
    std::cout << "\n--- unique_ptr 예제 종료 (함수가 끝나면 u_ptr3이 소멸되어 자원이 자동 해제됩니다) ---\n" << std::endl;
} // 함수가 여기서 끝나면, u_ptr3이 소멸되고 "독점 자원 1" 객체도 함께 소멸됩니다.

// ## 2. shared_ptr ##
// - 개념: 하나의 객체를 여러 포인터가 '공동으로 소유'할 수 있게 합니다.
// - 특징:
//   1. '참조 카운트(reference count)'를 통해 객체를 몇 개의 shared_ptr가 가리키는지 셉니다.
//   2. shared_ptr가 복사되면 참조 카운트가 1 증가하고, 소멸되면 1 감소합니다.
//   3. 참조 카운트가 0이 되는 순간, 객체의 메모리가 자동으로 해제됩니다.
void demonstrate_shared_ptr() {
    std::cout << "\n--- shared_ptr 예제 시작 ---\n" << std::endl;

    // std::make_shared를 사용하여 Resource 객체를 생성하고 shared_ptr로 관리합니다.
    std::shared_ptr<Resource> s_ptr1 = std::make_shared<Resource>("공유 자원 1");
    std::cout << "현재 참조 카운트: " << s_ptr1.use_count() << std::endl; // 출력: 1

    s_ptr1->greet();

    // 내부 블록을 만들어 shared_ptr의 생명주기를 테스트합니다.
    {
        // s_ptr1을 s_ptr2에 복사합니다. 소유권이 공유됩니다.
        std::shared_ptr<Resource> s_ptr2 = s_ptr1;
        std::cout << "s_ptr2로 복사 후 참조 카운트: " << s_ptr1.use_count() << std::endl; // 출력: 2

        s_ptr2->greet();
    } // 이 블록이 끝나면 s_ptr2가 소멸되고, 참조 카운트가 1 감소합니다.

    std::cout << "내부 블록 종료 후 참조 카운트: " << s_ptr1.use_count() << std::endl; // 출력: 1

    std::cout << "\n--- shared_ptr 예제 종료 (함수가 끝나면 s_ptr1이 소멸되어 자원이 자동 해제됩니다) ---\n" << std::endl;
} // 함수가 여기서 끝나면, s_ptr1이 소멸되고 참조 카운트가 0이 되어 "공유 자원 1" 객체도 함께 소멸됩니다.


// ## 3. weak_ptr ##
// - 개념: shared_ptr가 관리하는 객체를 가리키지만, 소유권은 갖지 않는 '관찰자' 포인터입니다.
// - 특징:
//   1. 참조 카운트에 영향을 주지 않습니다. (순환 참조 문제를 해결하는 데 사용됩니다.)
//   2. 객체에 직접 접근할 수 없으며, 접근하려면 lock() 메서드를 통해 유효한 shared_ptr를 얻어야 합니다.
//   3. lock()을 통해 객체가 아직 살아있는지 안전하게 확인할 수 있습니다. 객체가 소멸되었다면 lock()은 빈 shared_ptr를 반환합니다.
void demonstrate_weak_ptr() {
    std::cout << "\n--- weak_ptr 예제 시작 ---\n" << std::endl;

    // weak_ptr은 스스로 객체를 생성할 수 없으므로, 관찰할 shared_ptr가 필요합니다.
    std::weak_ptr<Resource> w_ptr;

    {
        auto s_ptr = std::make_shared<Resource>("임시 공유 자원");

        // w_ptr이 s_ptr이 관리하는 객체를 관찰하도록 합니다.
        w_ptr = s_ptr;

        // weak_ptr는 참조 카운트를 증가시키지 않습니다.
        std::cout << "weak_ptr 할당 후 참조 카운트: " << s_ptr.use_count() << std::endl; // 출력: 1

        // weak_ptr로 객체에 접근하려면 lock()을 사용해야 합니다.
        // lock()은 shared_ptr을 반환합니다.
        if (auto locked_ptr = w_ptr.lock()) { // locked_ptr는 이 if문 내에서만 유효한 shared_ptr입니다.
            std::cout << "lock() 성공! 객체가 아직 살아있습니다." << std::endl;
            locked_ptr->greet();
            std::cout << "lock()으로 shared_ptr 생성 후 참조 카운트: " << locked_ptr.use_count() << std::endl; // 출력: 2
        } else {
            std::cout << "lock() 실패. 객체가 이미 소멸되었습니다." << std::endl;
        }

    } // 이 블록이 끝나면 s_ptr이 소멸됩니다. 참조 카운트가 0이 되면서 "임시 공유 자원" 객체도 함께 소멸됩니다.

    std::cout << "\nshared_ptr가 범위를 벗어난 후..." << std::endl;
    
    // 이제 w_ptr이 가리키던 객체는 사라졌습니다.
    // expired() 함수로 객체가 소멸되었는지 확인할 수 있습니다.
    if (w_ptr.expired()) {
        std::cout << "w_ptr이 가리키는 객체는 소멸되었습니다." << std::endl;
    }

    // 다시 lock()을 시도하면, 객체가 없으므로 비어있는 shared_ptr가 반환됩니다.
    if (auto locked_ptr = w_ptr.lock()) {
        std::cout << "lock() 성공." << std::endl;
    } else {
        std::cout << "lock() 실패. 객체에 더 이상 접근할 수 없습니다." << std::endl;
    }
    
    std::cout << "\n--- weak_ptr 예제 종료 ---\n" << std::endl;
}

int main() {
    // 각 스마트 포인터의 동작을 보여주는 함수들을 순서대로 호출합니다.
    demonstrate_unique_ptr();
    demonstrate_shared_ptr();
    demonstrate_weak_ptr();

    return 0;
}