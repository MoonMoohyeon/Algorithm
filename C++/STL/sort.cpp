 //오름차순, 내림차순으로 정렬해주는 greater, less가 미리 구현되어 있다
//greater<int>, less<int>이렇게 사용한다.


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool comp(int a, int b){
	return a < b; // True or False
}

bool comp2(pair<int,int> p1, pair<int,int> p2){
	if(p1.first == p2.first){
		p1.second <= p2.second;	
	}
	return p1.first <= p2.first;
} // 

//퀵소트
int main(){
	int a[5] = {1, 5, 3, 2, 4};
	sort(a, a+5, comp); // sort은 시작주소와 끝주소+1을 쓰면 된다. comp에 따라 정렬된다.
	//오름차순으로 정렬된다. << comp가 true면 현상태 유지, false면 자리를 바꿔준다.

	sort(a, a+5, greater<int>()); // greater을 이용한 오름차순 정리

    vector<pair<int,int>> v;
    sort(v.begin(), v.end(), comp2);
    sort(v.rbegin(), v.rend(), comp2); // 내림차순 정렬
    
}