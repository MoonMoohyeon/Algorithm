#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // std::iota

// 벡터의 상태를 출력하는 헬퍼 함수
void print_state(const std::string& name, const std::vector<int>& vec) {
    std::cout << name << ":\t";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 1. fill: 모든 원소를 특정 값(7)으로 채웁니다.
    std::vector<int> v_fill(5);
    print_state("fill (전)", v_fill);
    std::fill(v_fill.begin(), v_fill.end(), 7);
    print_state("fill (후)", v_fill);
    std::cout << "---" << std::endl;

    // 2. generate: 함수가 생성하는 값으로 모든 원소를 채웁니다.
    std::vector<int> v_gen(5);
    int current = 0;
    print_state("generate (전)", v_gen);
    std::generate(v_gen.begin(), v_gen.end(), [&current] { return (current += 2); });
    print_state("generate (후)", v_gen);
    std::cout << "---" << std::endl;

    // 3. for_each: 모든 원소에 함수를 적용합니다. (원소 수정 가능)
    std::vector<int> v_for_each = {1, 2, 3, 4, 5};
    print_state("for_each (전)", v_for_each);
    std::for_each(v_for_each.begin(), v_for_each.end(), [](int& n){ n *= 2; });
    print_state("for_each (후)", v_for_each);
    std::cout << "---" << std::endl;

    // 3-2. for_each_n: 범위의 시작부터 n개의 원소에 대해 함수를 적용합니다.
    std::vector<int> v_fe_n = {10, 20, 30, 40, 50};
    print_state("for_each_n (전): ", v_fe_n);
    // 앞 3개 원소에 1을 더함
    std::for_each_n(v_fe_n.begin(), 3, [](int& n){ n += 1; });
    print_state("for_each_n (후): ", v_fe_n);
    std::cout << "---" << std::endl;

    // 4. transform: 모든 원소에 연산을 적용한 결과를 덮어씁니다.
    std::vector<int> v_trans = {1, 2, 3, 4, 5};
    print_state("transform (전)", v_trans);
    std::transform(v_trans.begin(), v_trans.end(), v_trans.begin(), [](int n){ return n * n; });
    print_state("transform (후)", v_trans);
    std::cout << "---" << std::endl;

    // 5. copy: 한 컨테이너의 내용을 다른 컨테이너로 복사합니다.
      std::vector<int> v_src = {1, 2, 3, 4, 5};
    std::vector<int> v_dest1(5), v_dest2(5);
    print_state("copy (목적지, 전)", v_dest1);
    std::copy(v_src.begin(), v_src.end(), v_dest1.begin());
    print_state("copy (목적지, 후)", v_dest1);
    std::cout << "---" << std::endl;

    // 5-2. copy_backward: 뒤에서부터 원소를 복사합니다.
    std::copy_backward(v_src.begin(), v_src.end(), v_dest2.end());
    print_state("copy_backward 결과:", v_dest2);
    std::cout << "---" << std::endl;


    std::vector<std::string> v_move_src = {"apple", "banana", "cherry"};
    std::vector<std::string> v_move_dest(3);
    // 6. move: copy와 유사하지만, 복사 대신 소유권을 이전합니다. 원본의 자원은 비워지므로 더 효율적입니다.
    // move_backward도 동일하게 동작합니다.
    std::cout << "move (원본, 전): " << v_move_src[0] << std::endl;
    std::move(v_move_src.begin(), v_move_src.end(), v_move_dest.begin());
    std::cout << "move (대상, 후): " << v_move_dest[0] << std::endl;
    std::cout << "move (원본, 후): " << (v_move_src[0].empty() ? "비었음" : v_move_src[0]) << std::endl;

    // 7. remove: 특정 값(3)을 뒤로 보내고, 유효 범위의 끝을 반환합니다. (erase와 함께 사용)
    // vector::erase 멤버 함수는 이 위치부터 끝까지의 원소를 물리적으로 삭제하여 벡터 크기를 줄입니다.
    // 이 조합을 erase-remove idiom이라고 합니다.
    std::vector<int> v_rem = {1, 9, 2, 9, 3, 9, 4};
    print_state("remove (전): ", v_rem);
    // 9를 논리적으로 제거
    auto new_end = std::remove(v_rem.begin(), v_rem.end(), 9);
    // 물리적으로 제거
    v_rem.erase(new_end, v_rem.end()); // erase-remove idiom
    print_state("remove (후): ", v_rem);
    std::cout << "---" << std::endl;

    // 8. unique: 정렬된 상태에서 연속된 중복 원소를 제거합니다. (erase와 함께 사용)
    std::vector<int> v_uniq = {1, 2, 2, 3, 3, 3, 4, 2};
    std::sort(v_uniq.begin(), v_uniq.end()); // unique는 정렬된 상태에서만 의미가 있음
    print_state("unique (정렬 후)", v_uniq);
    auto unique_end = std::unique(v_uniq.begin(), v_uniq.end());
    v_uniq.erase(unique_end, v_uniq.end());
    print_state("unique (후)", v_uniq);
    std::cout << "---" << std::endl;

    // 9. replace: 특정 값(3)을 다른 값(99)으로 모두 바꿉니다.
    std::vector<int> v_rep = {1, 2, 3, 4, 3, 5};
    print_state("replace (전)", v_rep);
    std::replace(v_rep.begin(), v_rep.end(), 3, 99);
    print_state("replace (후)", v_rep);
    std::cout << "---" << std::endl;
    
    // 10. sort: 원소들을 오름차순으로 정렬합니다.
    std::vector<int> v_sort = {5, 2, 8, 1, 9};
    print_state("sort (전)", v_sort);
    std::sort(v_sort.begin(), v_sort.end());
    print_state("sort (후)", v_sort);
    std::cout << "---" << std::endl;

    // 10-2. stable_sort: 일반 sort와 같지만, 값이 같은 원소들의 상대적인 순서를 유지합니다.
    std::vector<std::pair<int, char>> v_stable = {{2, 'a'}, {1, 'b'}, {2, 'c'}, {1, 'd'}};
    std::cout << "stable_sort (전): ";
    for(const auto& p : v_stable) std::cout << "{" << p.first << "," << p.second << "} ";
    std::cout << std::endl;
    
    std::stable_sort(v_stable.begin(), v_stable.end(), 
        [](const auto& a, const auto& b){ return a.first < b.first; });

    std::cout << "stable_sort (후): "; // 2a가 2c보다, 1b가 1d보다 앞에 위치 유지
    for(const auto& p : v_stable) std::cout << "{" << p.first << "," << p.second << "} ";
    std::cout << "\n---\n";

    // 10-3. partial_sort: 범위의 일부([begin, middle))만 정렬합니다. 나머지 부분은 정렬되지 않은 상태로 남습니다.
    std::vector<int> v_partial = {8, 2, 6, 4, 3, 5, 1, 7};
    print_state("partial_sort (전): ", v_partial);
    // 앞 4개 원소만 정렬
    std::partial_sort(v_partial.begin(), v_partial.begin() + 4, v_partial.end());
    print_state("partial_sort (후): ", v_partial);
    std::cout << "---" << std::endl;

    // 11. partition: 조건을 만족하는 원소는 앞으로, 아닌 원소는 뒤로 보냅니다.
    std::vector<int> v_part = {1, 2, 3, 4, 5, 6, 7, 8};
    print_state("partition (전)", v_part);
    std::partition(v_part.begin(), v_part.end(), [](int n){ return n % 2 == 0; }); // 짝수를 앞으로
    print_state("partition (후)", v_part);
    std::cout << "---" << std::endl;

    // 12. accumulate: 지정된 범위의 원소들을 누적하여 단일 값을 만드는 역할을 합니다.
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    // 1. 기본 합계
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    // 연산 과정: ((((0 + 10) + 20) + 30) + 40) + 50
    std::cout << "기본 합계: " << sum << std::endl; // 출력: 150
    // 초기값을 다르게 지정
    int sum_with_initial = std::accumulate(numbers.begin(), numbers.end(), 100);
    // 연산 과정: ((((100 + 10) + 20) + 30) + 40) + 50
    std::cout << "초기값 100을 더한 합계: " << sum_with_initial << std::endl; // 출력: 250

    // 2. 곱셈 구하기
    // 람다 함수 사용
    long long product = std::accumulate(numbers.begin(), numbers.end(), 1LL, 
        [](long long acc, int val) {
            return acc * val;
        });
    // 표준 함수 객체 사용
    // long long product = std::accumulate(numbers.begin(), numbers.end(), 1LL, std::multiplies<long long>());
    std::cout << "모든 원소의 곱: " << product << std::endl; // 출력: 120

    // 3. 문자열 연결
    std::vector<std::string> words = {"C++", "is", "powerful", "and", "fun!"};
    std::string sentence = std::accumulate(
        // 마지막 원소에는 공백을 붙이지 않기 위해 end()-1까지 먼저 처리
        words.begin(), words.end() - 1,
        // 초기값으로 첫 번째 단어를 사용
        words.front(), 
        // 누적된 문장에 공백과 다음 단어를 이어 붙이는 람다 함수
        [](const std::string& acc, const std::string& word) {
            return acc + " " + word;
        }
    );
    std::cout << "연결된 문장: " << sentence << std::endl; // 출력: C++ is powerful and fun!   
    
    


    return 0;
}