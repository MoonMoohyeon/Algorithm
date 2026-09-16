#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

/*
    우선순위 큐(Priority Queue) 코딩테스트 실전 가이드
    
    1. 기본 최대 힙 (큰 값이 top)
    2. 기본 최소 힙 (작은 값이 top)
    3. 절댓값 힙 (절댓값이 작은 순, 같으면 실제 값이 작은 순)
    4. 다중 조건 커스텀 구조체 힙
*/

// 절댓값 힙 비교자
struct AbsCompare {
    bool operator()(int a, int b) {
        if (abs(a) == abs(b)) {
            return a > b; // 실제 값이 작은 것이 우선 (최소 힙)
        }
        return abs(a) > abs(b); // 절댓값이 작은 것이 우선 (최소 힙)
    }
};

// 학생 정보 구조체
struct Student {
    int id;
    int score;
    int age;

    Student(int id, int score, int age) : id(id), score(score), age(age) {}

    // 1순위: 점수 높은 순 (내림차순)
    // 2순위: 나이 적은 순 (오름차순)
    // 3순위: id 작은 순 (오름차순)
    bool operator<(const Student& other) const {
        if (score != other.score) return score < other.score; // 점수 높은 것이 top
        if (age != other.age) return age > other.age;       // 나이 적은 것이 top
        return id > other.id;                               // id 작은 것이 top
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 절댓값 힙 테스트
    cout << "=== 1. 절댓값 힙 ===\n";
    priority_queue<int, vector<int>, AbsCompare> abs_pq;
    abs_pq.push(1);
    abs_pq.push(-1);
    abs_pq.push(2);
    abs_pq.push(-2);
    abs_pq.push(0);

    while (!abs_pq.empty()) {
        cout << abs_pq.top() << " ";
        abs_pq.pop();
    }
    cout << "\n\n"; // 0, -1, 1, -2, 2 순으로 출력

    // 2. 구조체 다중 조건 정렬 테스트
    cout << "=== 2. 다중 조건 학생 힙 ===\n";
    priority_queue<Student> student_pq;
    student_pq.push(Student(1, 90, 20));
    student_pq.push(Student(2, 95, 22));
    student_pq.push(Student(3, 90, 19));
    student_pq.push(Student(4, 90, 20));

    while (!student_pq.empty()) {
        auto s = student_pq.top();
        student_pq.pop();
        cout << "점수: " << s.score << ", 나이: " << s.age << ", ID: " << s.id << "\n";
    }

    return 0;
}
