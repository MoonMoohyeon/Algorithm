#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    // 1. 선언: std::unordered_map<키_타입, 값_타입> 이름;
    std::unordered_map<std::string, int> myMap;

    // 2. 삽입
    myMap["apple"] = 1;
    myMap["banana"] = 2;
    myMap.insert({"orange", 3});

    // 3. 접근 및 탐색
    std::cout << "apple: " << myMap["apple"] << std::endl;

    // find()를 사용한 안전한 탐색
    if (myMap.find("banana") != myMap.end()) {
        std::cout << "banana found: " << myMap["banana"] << std::endl;
    }

    // C++20 부터는 contains() 사용 가능
    if (myMap.contains("cherry")) {
        std::cout << "cherry found!" << std::endl;
    } else {
        std::cout << "cherry not found." << std::endl;
    }

    // 4. 반복
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 5. 삭제
    myMap.erase("banana");

    return 0;
}