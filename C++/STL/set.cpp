#include <iostream>
#include <set>
#include <string>

using namespace std;

// key만 저장 가능
int main() {
    // set을 선언한다. 자동으로 오름차순으로 정렬된다.
    // set<int, greater<int>> s; -> 내림차순으로 정렬
    set<int> s;

    // --- insert(): 원소 추가 ---
    // set은 중복된 값을 허용하지 않는다.
    s.insert(30);
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(10); // 10은 이미 있으므로 추가되지 않는다.

    cout << "--- 전체 원소 출력 ---" << endl;
    // 반복자를 이용해 순회하면 정렬된 순서로 출력된다.
    for (set<int>::iterator iter = s.begin(); iter != s.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl << endl; // 출력 결과: 10 20 30 50

    // --- find(): 원소 탐색 ---
    cout << "--- find() 예시 ---" << endl;
    // find()는 해당 원소를 가리키는 반복자를 반환한다.
    // 원소가 없으면 s.end()를 반환한다.
    set<int>::iterator find_iter = s.find(20);

    if (find_iter != s.end()) {
        cout << "값 20을 찾았습니다." << endl;
    } else {
        cout << "값 20을 찾지 못했습니다." << endl;
    }

    find_iter = s.find(100);
    if (find_iter != s.end()) {
        cout << "값 100을 찾았습니다." << endl;
    } else {
        cout << "값 100을 찾지 못했습니다." << endl;
    }
    cout << endl;

    // --- erase(): 원소 삭제 ---
    cout << "--- erase() 예시 ---" << endl;
    // 값으로 원소를 삭제한다. 삭제된 원소의 개수를 반환한다.
    int erased_count = s.erase(30);
    if (erased_count > 0) {
        cout << "값 30을 삭제했습니다." << endl;
    }

    // 삭제 후 set 상태 출력
    cout << "30 삭제 후: ";
    for (int val : s) { // 범위 기반 for문 사용 가능
        cout << val << " ";
    }
    cout << endl << endl;

    // --- count(): 원소 개수 확인 ---
    // set에서는 특정 값의 개수가 0 또는 1이다.
    cout << "--- count() 예시 ---" << endl;
    cout << "50의 개수: " << s.count(50) << endl;
    cout << "99의 개수: " << s.count(99) << endl;

    return 0;
}