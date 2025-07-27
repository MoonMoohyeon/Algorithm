#include<iostream>
#include<map>
#include<string>
using namespace std;


// 이진 탐색 트리를 기반으로 한다(레드 블랙 트리)
// key, value의 정보를 담고, key을 기반으로 정렬한다. << 자동으로 오름차순으로 정렬한다.
// map<int,int, greater<int>> map 하면 key 순으로 내림차순으로 정렬한다.
// 중복 key은 불가능하다 << 중복 key을 허용하기위해선 multimap을 사용해야 한다. ex) multimap<int,int, greater<int>> m[n_];
// value을 기준으로 정렬하는 방법

// 키를 값에 매핑한다는 개념
// 원소를 키 값을 기준으로 정렬된 상태를 유지

int main(void){

    map<int, string> m;
    //pair을 입력으로 받는다.
    m.insert(pair<int, string>(40, "me"));
    m.insert(pair<int, string>(35, "Show"));
    m.insert(pair<int, string>(10, "Dok2"));

    m[15] = "showme";


    //반복자를 이용한 순회.
    map<int, string>::iterator iter;

    cout << "--- 초기 상태 ---" << endl;
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "[" << iter->first << ", " << iter->second << "]" << " " ;
    }
    cout << endl << endl;

    // --- find 예시 ---
    cout << "--- find 예시 ---" << endl;
    // 키가 15인 원소를 찾는다.
    iter = m.find(15);

    // find는 키를 찾으면 해당 원소의 반복자를, 찾지 못하면 m.end()를 반환한다.
    if (iter != m.end()) {
        cout << "키 15를 찾았습니다. 값: " << iter->second << endl;
    } else {
        cout << "키 15를 찾지 못했습니다." << endl;
    }

    iter = m.find(20); //20 key은 존재하지 않음으로, m.end()을 반환.

    // 존재하지 않는 키를 찾으려 할 때
    iter = m.find(100);
    if (iter != m.end()) {
        cout << "키 100을 찾았습니다. 값: " << iter->second << endl;
    } else {
        cout << "키 100을 찾지 못했습니다." << endl;
    }
    cout << endl;

    iter = m.lower_bound(20); //기준값 보다 이상인 값중 가장 가까운값.
    cout << (*iter).first << ' ' << (*iter).second; //35
    cout << endl; 
    
    iter = m.upper_bound(20); //기준값 보다 큰값 중 가장 가까운값.
    cout << (*iter).first << ' ' << (*iter).second; //35


    // --- erase 예시 ---
    cout << "--- erase 예시 ---" << endl;

    // 1. 키를 이용한 삭제
    // 키가 35인 원소를 삭제한다. erase는 삭제된 원소의 수를 반환한다. (map에서는 0 또는 1)
    int erased_count = m.erase(35);
    if (erased_count > 0) {
        cout << "키 35를 가진 원소를 삭제했습니다." << endl;
    } else {
        cout << "키 35를 가진 원소가 없어 삭제하지 못했습니다." << endl;
    }


    // 삭제 후 map 상태 출력
    cout << "키 35 삭제 후: ";
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "[" << iter->first << ", " << iter->second << "]" << " " ;
    }
    cout << endl << endl;


    // 2. 반복자를 이용한 삭제
    // find로 키가 10인 원소를 찾아서 해당 반복자로 삭제한다.
    iter = m.find(10);
    if (iter != m.end()) {
        m.erase(iter); // C++11 이전에는 erase가 void를 반환했지만, C++11부터는 삭제된 원소 다음 원소의 반복자를 반환한다.
        cout << "키 10을 가진 원소를 반복자를 이용해 삭제했습니다." << endl;
    }

    // 최종 map 상태 출력
    cout << "키 10 삭제 후: ";
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "[" << iter->first << ", " << iter->second << "]" << " " ;
    }
    cout << endl;


    return 0;
}