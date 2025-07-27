#include <iostream>
#include <deque>

// deque의 모든 원소를 출력하는 함수
void print_deque(const std::deque<int>& dq) {
    for (int n : dq) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

/*
언제 사용할까요? 🤔
큐(Queue)와 스택(Stack)의 기능을 모두 사용하고 싶을 때

데이터의 앞과 뒤 모두에서 삽입과 삭제가 빈번하게 일어날 때 유용합니다.

vector는 뒤에서만 삽입/삭제가 효율적이고, list는 중간 삽입/삭제는 효율적이지만 인덱스 접근이 불가능합니다. deque는 이 둘의 장점을 절충한 컨테이너입니다.
*/

int main() {
    // 1. deque 선언
    std::deque<int> dq;

    // 2. 원소 추가 (뒤쪽)
    dq.push_back(10);
    dq.push_back(20);
    std::cout << "push_back(10), push_back(20) 후: ";
    print_deque(dq); // 결과: 10 20

    // 3. 원소 추가 (앞쪽) - deque의 핵심 기능!
    dq.push_front(5);
    dq.push_front(1);
    std::cout << "push_front(5), push_front(1) 후:  ";
    print_deque(dq); // 결과: 1 5 10 20

    // 4. 원소 접근
    std::cout << "\n가장 앞 원소: " << dq.front() << std::endl; // 1
    std::cout << "가장 뒤 원소: " << dq.back() << std::endl;  // 20
    std::cout << "인덱스 2의 원소: " << dq[2] << std::endl;    // 10

    // 5. 크기 확인 및 반복
    std::cout << "\n현재 크기: " << dq.size() << std::endl;
    std::cout << "전체 원소 순회: ";
    print_deque(dq); // 결과: 1 5 10 20

    // 6. 원소 제거 (앞/뒤)
    dq.pop_front(); // 앞쪽 원소(1) 제거
    std::cout << "\npop_front() 후: ";
    print_deque(dq); // 결과: 5 10 20

    dq.pop_back(); // 뒤쪽 원소(20) 제거
    std::cout << "pop_back() 후:  ";
    print_deque(dq); // 결과: 5 10

    // 7. 비어있는지 확인
    if (!dq.empty()) {
        std::cout << "\nDeque는 비어있지 않습니다." << std::endl;
    }

    return 0;
}