#include<iostream>
#include<cstdio>
#include<queue>
#include<utility>

using namespace std;

struct state{
	int a;
	int b;
};

queue<int> q;
queue<struct state> q1;

int main(){
	q.push(1);
	q.push(2);
	
	struct state s;
	s.a = 1;
	s.b = 2;
	q1.push(s);
	
	int a  = q.front(); //참조한다
	q.pop(); //처음 넣은것을 삭제한다
	
	cout << a;
	cout << q.size();

	if(!q.empty()){
		cout << "not empty";	
	}

	return 0;
}