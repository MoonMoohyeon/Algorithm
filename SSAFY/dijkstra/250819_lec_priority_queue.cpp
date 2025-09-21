#include<iostream>
#include<queue>
using namespace std;


struct Plus {
	int operator()(int left, int right) const {
		return left + right;
	};
};

struct cmp {
	bool operator() (int left, int right) const {

		if (left < right) return true;
		return false;


		// 정렬에서는 작은 값 우선 -> 우선순위 큐에 적용하면 큰 값 우선이 됨
		// -> sort 함수에 정렬 기준 함수를 정해줄 때와 달리 
		// 가장 왼쪽에 가는 값이 우선순위가 낮음. 
		// 정렬과는 !!반대!!로 함수 기준이 적용됨
	};
};

struct Coord {
	int y, x;

	// 이 struct에 ㅐ대한 정렬 기준 바뀔 일 없으면 struct 내부에 구현
	bool operator<(Coord right) const {
		// y 큰ㅋ 거우선
		if (y < right.y) return true;
		if (y > right.y) return false;

		// x 작은 거 우선
		if (x < right.x) return false;
		if (x > right.x) return true;
		return false;
	}
};


struct coordCmp {
	// 정렬 기준 바뀔 일 고려하면 function object로
	bool operator() (Coord left, Coord right) const {
		// y 큰 것 우선(우선순위 큐 적용 기준, 큰 게 오른쪽으로 가게)
		if (left.y < right.y) return true;
		if (left.y > right.y) return false;

		// x 큰 것 우선
		if (left.x < right.x) return true;
		return false;
	};
};

int main() {

	Plus p;
	int ans = p(1, 2);
	///////////////////////////////////////////////////////////////////////////////////
	/*

	기본 데이터 타입
	 -> 기본 제공 옵셔 ㄴ적용 가능 less, greater
	 -> function object 방식(객체를 함수처럼 ㅆ는 방식)
	 -> operator< 오버로딩 안됨
	*/
	
	priority_queue<int>pq1;	// 최대값 루트
	
	// container adapter
	priority_queue<int, vector<int>, greater<>>pq2;	// 최소값 루트
	priority_queue<int, vector<int>, cmp>pq3;	// 최대값 루트

	// 데이터 추가
	// O(logN)
	//pq.push(1);
	//pq.push(5);
	//pq.push(3);
	//pq.push(2);

	//// 가장 우선순위 높은 값 보기(값 큰 게 default, MaxHeap 구조)
	//// O(1)
	//cout << pq.top() << "\n";

	//// 데이터 삭제(루트 = 가장 우선순위 높은 값)
	//// O(logN)
	//pq.pop();
	//cout << pq.top();

	// 큐가 비었는지 확인
	//pq.empty();

	// 데이터 관리 : 밸런싱 -> heapify 
	// O(logN)


	/*pq.push(1);
	pq.push(11);
	pq.push(13);
	pq.push(14);
	pq.push(19);
	pq.push(21);
	pq.push(51);

	while (!pq.empty()) {
		int now = pq.top(); pq.pop();
		cout << now << " ";
	}*/

	///////////////////////////////////////////////////////////////////////////////////
	/*

	struct 처럼 멤버를 갖는 경우
	 -> 기본 제공 옵셔 ㄴ적용 X
	 -> function object 방식ok
	 -> operator< 오버로딩 ok
	*/

	priority_queue<Coord, vector<Coord>, coordCmp> pq;

	pq.push({ 4, 2 });
	pq.push({ 14, 2 });
	pq.push({ 4, 12 });
	pq.push({ 134, 2 });
	pq.push({ 44, 12 });
	pq.push({ 64, 2 });
	pq.push({ 4,72 });



	while (!pq.empty()) {
		Coord now = pq.top(); pq.pop();
		cout << now.y << ", " << now.x << "  ";

	}
	return 0;
}