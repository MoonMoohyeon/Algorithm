#include<iostream>
#include<map>
#include<string>
using namespace std;


// 이진 탐색 트리를 기반으로 한다
// key, value의 정보를 담고, key을 기반으로 정렬한다. << 자동으로 오름차순으로 정렬한다.
// map<int,int, greater<int>> map 하면 key 순으로 내림차순으로 정렬한다. 
// 중복 key은 불가능하다 << 중복 key을 허용하기위해선 multimap을 사용해야 한다. ex) multimap<int,int, greater<int>> m[n_];
// value을 기준으로 정렬하는 방법



int main(void){
    
    map<int, string> m; 
    //pair을 입력으로 받는다.
    m.insert(pair<int, string>(40, "me"));
    m.insert(pair<int, string>(35, "Show"));
    m.insert(pair<int, string>(10, "Dok2"));

    m[15] = "showme";
   
	
    //반복자를 이용한 순회.
    map<int, string>::iterator iter;
    
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "[" << iter->first << ", " << iter->second << "]" << " " ;
    }
    cout << endl;
    
    //접근방법 2
    //key 오름차순으로 정렬된다.
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "[" << (*iter).first << ", " << (*iter).second << "]" << " " ;
    }
    cout << endl;
	
    
    iter = m.find(15);
    iter = m.find(20); //20 key은 존재하지 않음으로, m.end()을 반환.
    
    
    iter = m.lower_bound(20); //기준값 보다 이상인 값중 가장 가까운값.
    cout << (*iter).first << ' ' << (*iter).second; //35
    cout << endl; 
    
    iter = m.upper_bound(20); //기준값 보다 큰값 중 가장 가까운값.
    cout << (*iter).first << ' ' << (*iter).second; //35
    
    return 0;    
}

// 이진 탐색 트리는 중위순회를 이용하면, 오름차순으로 출력된다.
l < root < r이 반드시 성립하기 때문이다. 