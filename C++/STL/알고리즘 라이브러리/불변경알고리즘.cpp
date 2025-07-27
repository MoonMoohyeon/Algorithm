#include <iostream>
#include <vector>
#include <algorithm> // 모든 알고리즘 함수를 포함
#include <numeric>   // std::iota를 위해 포함

// 벡터의 모든 원소를 출력하는 헬퍼 함수
void print_vector(const std::string& title, const std::vector<int>& vec) {
    std::cout << title;
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

// find_if에 사용할 조건 함수
bool is_odd(int i) {
    return i % 2 != 0;
}

int main() {
    // --- 기본 데이터 준비 ---
    std::vector<int> v1 = {10, 20, 30, 40, 50, 20, 30};
    print_vector("v1 (원본 데이터):        ", v1);

    std::vector<int> pattern = {20, 30};
    print_vector("pattern (비교용 데이터): ", pattern);
    std::cout << "--------------------------------------------------------" << std::endl;

    // --- 알고리즘 실행 ---

    // 1. count: 범위 내에서 특정 값(20)의 개수를 셉니다.
    int n_20 = std::count(v1.begin(), v1.end(), 20);
    std::cout << "1. count(20): " << n_20 << "개" << std::endl;

    // 2. count_if: 조건(30보다 큰)을 만족하는 원소의 개수를 셉니다.
    int n_greater_than_30 = std::count_if(v1.begin(), v1.end(), [](int i){ return i > 30; });
    std::cout << "2. count_if(> 30): " << n_greater_than_30 << "개" << std::endl;

    // 3. find: 특정 값(30)을 가진 첫 번째 원소의 위치를 찾습니다.
    auto it_find = std::find(v1.begin(), v1.end(), 30);
    std::cout << "3. find(30): " << std::distance(v1.begin(), it_find) << "번 인덱스에서 찾음" << std::endl;

    // 4. find_if: 조건(홀수)을 만족하는 첫 번째 원소를 찾습니다.
    auto it_find_if = std::find_if(v1.begin(), v1.end(), is_odd);
    if (it_find_if != v1.end()) {
        std::cout << "4. find_if(홀수): " << *it_find_if << "을(를) " << std::distance(v1.begin(), it_find_if) << "번 인덱스에서 찾음" << std::endl;
    } else {
        std::cout << "4. find_if(홀수): 홀수를 찾지 못함" << std::endl;
    }

    // 5. search: 한 범위(v1) 내에서 다른 범위(pattern)가 처음 나타나는 위치를 찾습니다.
    auto it_search = std::search(v1.begin(), v1.end(), pattern.begin(), pattern.end());
    std::cout << "5. search({20, 30}): " << std::distance(v1.begin(), it_search) << "번 인덱스에서 시작됨" << std::endl;

    // 6. find_end: 한 범위(v1) 내에서 다른 범위(pattern)가 마지막으로 나타나는 위치를 찾습니다.
    auto it_find_end = std::find_end(v1.begin(), v1.end(), pattern.begin(), pattern.end());
    std::cout << "6. find_end({20, 30}): " << std::distance(v1.begin(), it_find_end) << "번 인덱스에서 마지막으로 나타남" << std::endl;

    // 7. search_n: 특정 값(20)이 n번(1번) 연속으로 나타나는 첫 위치를 찾습니다.
    auto it_search_n = std::search_n(v1.begin(), v1.end(), 1, 20);
    std::cout << "7. search_n(값: 20, 개수: 1): " << std::distance(v1.begin(), it_search_n) << "번 인덱스에서 찾음" << std::endl;

    // 8. binary_search: 정렬된 범위에서 값이 존재하는지 확인합니다. (원본을 복사하여 정렬 후 사용)
    std::vector<int> sorted_v1 = v1;
    std::sort(sorted_v1.begin(), sorted_v1.end());
    bool found_40 = std::binary_search(sorted_v1.begin(), sorted_v1.end(), 40);
    std::cout << "8. binary_search(40): " << (found_40 ? "정렬된 데이터에 존재함" : "존재하지 않음") << std::endl;

    // 9. equal: 두 범위의 원소들이 모두 동일한지 비교합니다.
    std::vector<int> v3 = {10, 20, 30};
    bool are_equal = std::equal(v3.begin(), v3.end(), v1.begin());
    std::cout << "9. equal(v3, v1 시작 부분): " << (are_equal ? "동일함" : "동일하지 않음") << std::endl;

    // 10. mismatch: 두 범위를 비교하여 처음으로 다른 원소를 찾습니다.
    std::vector<int> v4 = {10, 20, 35};
    auto pair_mismatch = std::mismatch(v1.begin(), v1.end(), v4.begin());
    std::cout << "10. mismatch(v1, v4): v1[" << std::distance(v1.begin(), pair_mismatch.first) << "]에서 처음으로 다름" << std::endl;

    // 11. lexicographical_compare: 두 범위를 사전 순서로 비교합니다.
    std::vector<int> v5 = {10, 20, 40};
    bool is_less = std::lexicographical_compare(v1.begin(), v1.end(), v5.begin(), v5.end());
    std::cout << "11. lexicographical_compare(v1, v5): v1이 v5보다 사전 순으로 " << (is_less ? "앞선다 (true)" : "앞서지 않는다 (false)") << std::endl;

    // 12. binary_search: 값이 범위에 존재하는지 여부(true/false)를 반환합니다.
    std::vector<int> v_search = {10, 20, 30, 30, 30, 40, 50};
    print_vector("정렬된 데이터: ", v_search);
    bool found = std::binary_search(v_search.begin(), v_search.end(), 30);
    std::cout << "1. binary_search(30): " << (found ? "찾음" : "못 찾음") << std::endl;

    // 13. lower_bound: 특정 값 이상인 첫 번째 원소의 위치(반복자)를 반환합니다.
    auto it_lower = std::lower_bound(v_search.begin(), v_search.end(), 30);
    std::cout << "2. lower_bound(30): " << std::distance(v_search.begin(), it_lower) << "번 인덱스" << std::endl;

    // 14. upper_bound: 특정 값을 초과하는 첫 번째 원소의 위치(반복자)를 반환합니다.
    auto it_upper = std::upper_bound(v_search.begin(), v_search.end(), 30);
    std::cout << "3. upper_bound(30): " << std::distance(v_search.begin(), it_upper) << "번 인덱스" << std::endl;


    // --- 최종 결과 확인 ---
    std::cout << "--------------------------------------------------------" << std::endl;
    print_vector("\n모든 작업 후 v1 (원본 데이터는 변경되지 않음): ", v1);

    return 0;
}