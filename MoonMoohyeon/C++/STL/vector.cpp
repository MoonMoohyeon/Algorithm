#include <iostream> // 표준 입출력 스트림을 사용하기 위해 포함합니다.
#include <vector>   // std::vector를 사용하기 위해 포함합니다.
#include <iterator> // std::iterator 관련 도구를 사용하기 위해 포함합니다.

int main() {
    // 1. 벡터 생성하기
    // int 타입을 저장할 수 있는 비어있는 벡터 'numbers'를 생성합니다.
    std::vector<int> numbers;
    std::cout << "## 1. 비어있는 벡터를 생성했습니다." << std::endl;

    // ---

    // 2. 벡터에 요소 추가하기 (push_back)
    // push_back() 함수는 벡터의 맨 뒤에 새로운 요소를 추가합니다.
    numbers.push_back(10); // [10]
    numbers.push_back(20); // [10, 20]
    numbers.push_back(30); // [10, 20, 30]
    std::cout << "\n## 2. 세 개의 정수를 추가했습니다: 10, 20, 30" << std::endl;

    // ---

    // 3. 반복자(iterator)를 사용하여 벡터 순회하기
    // std::vector<int>::iterator는 'numbers' 벡터의 요소를 가리키는 포인터와 같은 역할을 합니다.
    // begin()은 벡터의 첫 번째 요소를 가리키는 반복자를 반환합니다.
    // end()는 벡터의 마지막 요소 바로 다음 위치를 가리키는 반복자를 반환합니다.
    std::cout << "\n## 3. 반복자를 이용한 기본 순회" << std::endl;
    for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        // it은 포인터처럼 행동하므로, 역참조 연산자(*)를 사용하여 실제 값을 가져옵니다.
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // ---

    // 4. 범위 기반 for문 (Range-based for loop)을 사용한 순회 (C++11 이상)
    // 이 방법은 코드가 더 간결하고 읽기 쉬워 현대 C++에서 가장 권장되는 방식입니다.
    // 내부적으로는 반복자를 사용하여 동작합니다.
    std::cout << "\n## 4. 범위 기반 for문을 이용한 순회 (더 간편한 방법!)" << std::endl;
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // ---

    // 5. 반복자를 사용하여 특정 위치에 요소 삽입하기 (insert)
    // numbers.begin() + 1은 벡터의 두 번째 위치를 가리킵니다.
    // 이 위치에 정수 15를 삽입합니다.
    std::vector<int>::iterator insert_it = numbers.begin() + 1;
    numbers.insert(insert_it, 15); // [10, 15, 20, 30]
    std::cout << "\n## 5. 두 번째 위치에 15를 삽입했습니다." << std::endl;
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // ---

    // 6. 반복자를 사용하여 특정 위치의 요소 삭제하기 (erase)
    // numbers.begin() + 2는 이제 세 번째 요소(20)를 가리킵니다.
    // 이 위치의 요소를 삭제합니다.
    // erase()는 삭제된 요소의 다음 요소를 가리키는 반복자를 반환합니다.
    std::vector<int>::iterator erase_it = numbers.begin() + 2;
    numbers.erase(erase_it); // [10, 15, 30]
    std::cout << "\n## 6. 세 번째 위치의 요소를 삭제했습니다." << std::endl;
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // ---
    
    // 7. const_iterator 사용하기
    // 벡터의 요소를 변경하지 않고 읽기만 할 때 사용합니다.
    // cbegin()과 cend()는 const_iterator를 반환합니다.
    std::cout << "\n## 7. const_iterator를 이용한 읽기 전용 순회" << std::endl;
    for (std::vector<int>::const_iterator cit = numbers.cbegin(); cit != numbers.cend(); ++cit) {
        // *cit = 50; // 이 코드는 컴파일 에러를 발생시킵니다. const_iterator는 값을 변경할 수 없습니다.
        std::cout << *cit << " ";
    }
    std::cout << std::endl;


    return 0; // 프로그램이 성공적으로 종료되었음을 의미합니다.
}