//오름차순, 내림차순으로 정렬해주는 greater, less가 미리 구현되어 있다
//greater<int>, less<int>이렇게 사용한다.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool comp(int a, int b){
	return a < b; // 오름차순
}

// pair 정렬: first 기준 오름차순, first가 같으면 second 기준 오름차순
// 주의: '<='를 사용하면 Strict Weak Ordering 위반으로 런타임 에러(UB)가 발생할 수 있으므로 반드시 '<' 사용!
bool comp2(pair<int,int> p1, pair<int,int> p2){
	if(p1.first == p2.first){
		return p1.second < p2.second;	
	}
	return p1.first < p2.first;
}

int main(){
	int a[5] = {1, 5, 3, 2, 4};
	sort(a, a+5, comp); // 기본 오름차순 정렬

	sort(a, a+5, greater<int>()); // greater를 이용한 내림차순 정렬

    vector<pair<int,int>> v = {{3, 2}, {1, 4}, {3, 1}, {2, 5}};
    sort(v.begin(), v.end(), comp2); // comp2 기준 정렬
    
    for(auto p : v) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << "\n";

    return 0;
}