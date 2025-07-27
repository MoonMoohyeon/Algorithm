#include <iostream>
#include <queue>   // 큐를 사용하기 위해 헤더를 포함합니다.
#include <string>

using namespace std;

int main() {
    // 정수를 저장하는 큐를 선언합니다.
    queue<int> q;

    // --- push(): 큐의 맨 뒤에 원소를 추가합니다. ---
    cout << "Pushing 10, 20, 30 into the queue..." << endl;
    q.push(10); // [10]
    q.push(20); // [10, 20]
    q.push(30); // [10, 20, 30]

    // --- size(): 큐의 크기를 반환합니다. ---
    cout << "Queue size: " << q.size() << endl; // 출력: 3

    // --- front() & back(): 큐의 앞/뒤 원소를 확인합니다. ---
    cout << "Front element is: " << q.front() << endl; // 출력: 10 (가장 먼저 들어온 원소)
    cout << "Back element is: " << q.back() << endl;  // 출력: 30 (가장 나중에 들어온 원소)
    cout << endl;

    // --- pop(): 큐의 맨 앞 원소를 제거합니다. ---
    cout << "Popping the front element..." << endl;
    q.pop(); // 10이 제거됩니다.

    cout << "After pop(), new front element is: " << q.front() << endl; // 출력: 20
    cout << "Queue size is now: " << q.size() << endl;                 // 출력: 2
    cout << endl;

    // --- empty(): 큐가 비어있는지 확인합니다. ---
    cout << "Popping all elements from the queue:" << endl;
    while (!q.empty()) {
        // 가장 앞의 원소를 출력하고
        cout << q.front() << " ";
        // 큐에서 제거합니다.
        q.pop();
    }
    cout << endl; // 출력: 20 30 (FIFO 순서)

    if (q.empty()) {
        cout << "Queue is now empty." << endl;
    }

    return 0;
}