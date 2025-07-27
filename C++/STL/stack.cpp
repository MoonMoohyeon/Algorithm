#include <iostream>
#include <stack> // 스택을 사용하기 위해 헤더를 포함합니다.
#include <string>

using namespace std;

int main() {
    // 정수를 저장하는 스택을 선언합니다.
    stack<int> s;

    // --- push(): 스택의 가장 위에 원소를 추가합니다. ---
    cout << "Pushing 10, 20, 30 onto the stack..." << endl;
    s.push(10); // [10]
    s.push(20); // [10, 20]
    s.push(30); // [10, 20, 30]

    // --- size(): 스택의 크기를 반환합니다. ---
    cout << "Stack size: " << s.size() << endl; // 출력: 3

    // --- top(): 스택의 가장 위 원소를 확인합니다. (제거하지 않음) ---
    cout << "Top element is: " << s.top() << endl; // 출력: 30
    cout << endl;

    // --- pop(): 스택의 가장 위 원소를 제거합니다. ---
    cout << "Popping the top element..." << endl;
    s.pop(); // 30이 제거됩니다.

    cout << "After pop(), new top element is: " << s.top() << endl;   // 출력: 20
    cout << "Stack size is now: " << s.size() << endl; // 출력: 2
    cout << endl;

    // --- empty(): 스택이 비어있는지 확인합니다. ---
    cout << "Popping all elements from the stack:" << endl;
    while (!s.empty()) {
        // 가장 위의 원소를 출력하고
        cout << s.top() << " ";
        // 스택에서 제거합니다.
        s.pop();
    }
    cout << endl; // 출력: 20 10 (LIFO 순서)

    if (s.empty()) {
        cout << "Stack is now empty." << endl;
    }

    return 0;
}