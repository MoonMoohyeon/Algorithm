#include <iostream>
#include <vector>
#include <functional> // 함수 객체를 사용하기 위한 헤더
#include <algorithm>  // 표준 알고리즘을 사용하기 위한 헤더

// C++17부터 bind를 사용하기 위해 필요할 수 있음
#include <functional> 
using namespace std::placeholders; // _1, _2 등을 사용하기 위해

// 벡터를 출력하는 헬퍼 함수
void print_vector(const string& message, const vector<int>& v) {
    cout << message;
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    vector<int> v = {10, 50, 30, 40, 20};
    print_vector("초기 벡터: ", v);

    // 1. 비교 연산: sort()로 내림차순 정렬하기
    // sort의 세 번째 인자로 비교 조건을 함수 객체로 전달합니다.
    sort(v.begin(), v.end(), greater<int>());
    print_vector("내림차순 정렬 후: ", v); // 50 40 30 20 10

    cout << "---" << endl;

    // 2. 산술 연산: transform()으로 모든 원소의 부호 바꾸기
    vector<int> negated_v(v.size());
    // v의 각 원소에 negate<int>()를 적용하여 결과를 negated_v에 저장합니다.
    transform(v.begin(), v.end(), negated_v.begin(), negate<int>());
    print_vector("부호 반전 후: ", negated_v); // -50 -40 -30 -20 -10

    cout << "---" << endl;

    // 3. 조건부 카운트: count_if()로 특정 조건에 맞는 원소 개수 세기
    // 35보다 작은 원소의 개수를 셉니다.
    // bind는 함수와 인자를 묶어 새로운 함수를 만드는 도구입니다.
    // less<int>()는 인자 두 개(a, b)를 받지만, count_if는 인자 하나만 받는 함수가 필요합니다.
    // bind를 사용해 less<int>의 두 번째 인자를 35로 고정합니다.
    // _1은 count_if가 전달할 벡터의 원소를 받는 placeholder입니다.
    // 즉, less<int>(v[i], 35) 와 같은 형태로 호출됩니다.
    int count = count_if(v.begin(), v.end(), bind(less<int>(), _1, 35));
    cout << "35보다 작은 원소의 개수: " << count << endl; // 30, 20, 10 이므로 3개

    return 0;
}