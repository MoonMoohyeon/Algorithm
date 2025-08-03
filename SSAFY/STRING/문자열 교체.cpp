#include <iostream>
#include <string>
#include <vector>

void replaceAll(std::string& text, const std::string& from, const std::string& to) {
    if (from.empty()) {
        return;
    }

    size_t start_pos = 0;
    while (true) {
        // 1. start_pos 위치부터 'from' 문자열을 찾습니다.
        start_pos = text.find(from, start_pos);

        // 2. 만약 문자열을 찾지 못했다면 루프를 탈출합니다.
        if (start_pos == std::string::npos) {
            break;
        }

        // 3. (찾았다면) 'replace' 함수로 문자열을 교체합니다.
        text.replace(start_pos, from.length(), to);

        // 4. 다음 검색 위치를 업데이트합니다.
        start_pos += to.length();
    }
}

void replaceAllWithBreak(std::string& text, const std::string& from, const std::string& to) {
    if (from.empty()) {
        return;
    }

    size_t start_pos = 0;
    while (true) {
        // 1. start_pos 위치부터 'from' 문자열을 찾습니다.
        start_pos = text.find(from, start_pos);

        // 2. 만약 find가 std::string::npos를 반환하면, 더 이상 교체할 문자열이 없다는 의미입니다.
        if (start_pos == std::string::npos) {
            break; // 루프를 탈출합니다.
        }

        // 3. (찾았다면) 문자열을 교체합니다.
        text.erase(start_pos, from.length());
        text.insert(start_pos, to);

        // 4. 다음 검색 위치를 업데이트합니다.
        start_pos += to.length();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    const std::string originals[] = { "KFC", "MC", "BICMAC", "SHACK", "SONY" };
    const std::string targets[] = { "#BBQ#", "#BBQ#", "#MACBOOK#", "#SHOCK#", "#NONY#" };
    const int numRules = 5;

    std::string userInput;
    std::cout << "문자열을 입력하세요: ";
    std::cin >> userInput;

    for (int i = 0; i < numRules; ++i) {
        replaceAll(userInput, originals[i], targets[i]);
    }
    std::cout << "최종 결과: " << userInput << std::endl;

    return 0;
}