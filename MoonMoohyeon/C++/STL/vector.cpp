#include<iostream>
#include<vector>

using namespace std;

int  main(){
	vector<int> v;
	
	v.push_back(1);
	v.push_back(1);

	v.clear(); //모든 원소제거

	v.push_back(1);
	v.push_back(1);
	v.push_back(1);

	v.pop_back(); // 마지막 원소 제거

	cout << v.size(); // 2
	cout << v.front(); // 1
	cout << v[0] << ' ' << v[1]; // 1 1
	
	v[0] = 10;
	
	cout << v[0]; // 10

	cout << '\n';
	
	for(vector<int>::iterator i = v.begin(); i < v.end(); i++){
		cout << *i << ' '; // 참조자를 반환하는 것임으로 간접주소 방식을 이용.
		*i = 2; //삽입가능.
	}


	for(vector<int>::const_iterator i = v.cbegin(); i < v.cend(); i++){ // 값을 변경하지 않을 경우
		cout << *i << ' '; // 참조자를 반환하는 것임으로 간접주소 방식을 이용.
	}

	
	return 0;
}