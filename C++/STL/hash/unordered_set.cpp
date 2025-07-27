#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    // 1. 선언: std::unordered_set<타입> 이름;
    std::unordered_set<std::string> mySet;

    // 2. 삽입
    mySet.insert("apple");
    mySet.insert("banana");
    mySet.insert("apple"); // 중복된 원소는 무시됨

    // 3. 탐색
    if (mySet.find("banana") != mySet.end()) {
        std::cout << "banana found!" << std::endl;
    }

    // C++20 부터는 contains() 사용 가능
    if (mySet.contains("cherry")) {
        std::cout << "cherry found!" << std::endl;
    } else {
        std::cout << "cherry not found." << std::endl;
    }

    // 4. 반복
    for (const auto& element : mySet) {
        std::cout << element << std::endl;
    }

    // 5. 삭제
    mySet.erase("banana");

    return 0;
}