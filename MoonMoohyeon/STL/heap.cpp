#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<utility>

using namespace std;


struct state{
	int a;
	int b;
};


struct comp{
	bool operator()(const struct state &s1, const struct state &s2){
		return s1.a <= s2.a;
	}
};
// a가 클수록 우선순위가 높다. 

priority_queue<struct state, vector<struct state>, comp> pq;

int main(){
	struct state s1;
	s1.a = 10;
	s1.b = 10;

	struct state s2;
	s2.a = 8;
	s2.b = 8;

	pq.push(s1);
	pq.push(s2);
	
	int end = pq.size();
	for(int i = 0; i<end; i++){
		cout << pq.top().a << '\n'; // front말고 top으로 참고한다
		pq.pop();
	}

	return 0;
}

// ______________________________________________________________________________________________________________
// state생성자를 이용하면 더 간단히 할 수 있다

struct state{
	int a;
	int b;
	state(int a, int b) : a(a), b(b) {}
};


struct comp{
	bool operator()(const state &s1, state &s2){
		return s1.a <= s2.a;
	}
};

priority_queue<state, vector<state>, comp> pq;

int main(){
	state s1(10,10);
	state s2(8,8);

	pq.push(s1);
	pq.push(s2);
	
	int end = pq.size();
	for(int i = 0; i<end; i++){
		cout << pq.top().a << '\n'; // front말고 top으로 참고한다
		pq.pop();
	}

	return 0;
}