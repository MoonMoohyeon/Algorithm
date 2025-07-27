#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // sort, find_if, for_each
#include <functional> // std::function (비교용)


/*
사용법
[lambda-introducer](< Arguments>) -> <Return type>{ }(<input>)
[람다 선언자] (받는 인자) -> 반환형 {함수 몸체} (입력 값)

lambda introducer ( 람다 선언자 )
– 람다 함수에서 외부의 값에 대한 명세

[] : 아무것도 캡처하지 않음
[x] : x 만 Capture by value
[&x] : x 만 Capture by reference
[x, y] : x, y 를 capture by value
[&x, y] : x 는 capture by reference, y 는 capture by value
*/

// 예제에서 사용할 간단한 Person 구조체
struct Person {
    std::string name;
    int age;
};

// ----------------------------------------------------
// 람다를 사용하지 않는 경우 (C++11 이전 스타일)
// ----------------------------------------------------

// 1-1. 정렬을 위한 비교 "함수"
bool compareByAge(const Person& a, const Person& b) {
    return a.age < b.age; // 나이 오름차순
}

// 1-2. 정렬을 위한 비교 "함수 객체(Functor)"
struct CompareByNameDesc {
    bool operator()(const Person& a, const Person& b) const {
        return a.name > b.name; // 이름 내림차순
    }
};

// 2. 찾기 조건을 위한 "함수 객체(Functor)"
class FindByAge {
private:
    int ageToFind;
public:
    FindByAge(int age) : ageToFind(age) {} // 찾을 나이를 생성자로 받음

    bool operator()(const Person& person) const {
        return person.age == ageToFind;
    }
};


// 벡터를 출력하기 위한 헬퍼 함수
void printPeople(const std::string& title, const std::vector<Person>& people) {
    std::cout << "--- " << title << " ---" << std::endl;
    for (const auto& p : people) {
        std::cout << "이름: " << p.name << ", 나이: " << p.age << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    std::vector<Person> people = {
        {"철수", 25},
        {"영희", 22},
        {"민준", 30},
        {"서연", 22}
    };

    printPeople("원본 데이터", people);

    // ===================================================================
    // 예제 1: 정렬 (Sort)
    // ===================================================================

    // 방법 1: 람다 미사용 - 일반 함수 포인터 전달
    std::vector<Person> people1 = people;
    std::sort(people1.begin(), people1.end(), compareByAge);
    printPeople("람다 미사용 (일반 함수) - 나이 오름차순", people1);

    // 방법 2: 람다 미사용 - 함수 객체(Functor) 전달
    std::vector<Person> people2 = people;
    std::sort(people2.begin(), people2.end(), CompareByNameDesc());
    printPeople("람다 미사용 (함수 객체) - 이름 내림차순", people2);

    // 방법 3: 람다 사용 ✨
    // 별도의 함수나 구조체 정의 없이, 코드가 필요한 위치에 바로 논리를 작성
    std::vector<Person> people3 = people;
    std::sort(people3.begin(), people3.end(), [](const Person& a, const Person& b) {
        // 만약 나이가 같다면 이름으로 오름차순 정렬
        if (a.age == b.age) {
            return a.name < b.name;
        }
        return a.age < b.age; // 기본은 나이 오름차순
    });
    printPeople("람다 사용 - 나이(같으면 이름) 오름차순", people3);


    // ===================================================================
    // 예제 2: 조건에 맞는 원소 찾기 (Find_if)
    // ===================================================================

    int ageToFind = 30;

    // 방법 1: 람다 미사용 - 함수 객체(Functor) 사용
    // 찾으려는 값을 Functor의 생성자로 넘겨줘야 함
    auto it1 = std::find_if(people.begin(), people.end(), FindByAge(ageToFind));
    std::cout << "--- 람다 미사용 (함수 객체) ---" << std::endl;
    if (it1 != people.end()) {
        std::cout << "나이가 " << ageToFind << "인 사람을 찾았습니다: " << it1->name << std::endl;
    }
    std::cout << std::endl;

    // 방법 2: 람다 사용 ✨
    // 외부 변수(ageToFind)를 캡처([=])하여 간결하게 사용
    auto it2 = std::find_if(people.begin(), people.end(), [=](const Person& p) {
        return p.age == ageToFind;
    });
    std::cout << "--- 람다 사용 ---" << std::endl;
    if (it2 != people.end()) {
        std::cout << "나이가 " << ageToFind << "인 사람을 찾았습니다: " << it2->name << std::endl;
    }
    std::cout << std::endl;

    return 0;
}