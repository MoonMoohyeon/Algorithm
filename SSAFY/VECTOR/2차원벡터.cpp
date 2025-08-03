#include<iostream>
#include<vector>


using namespace std;


// 벡터 생성 + 초기화
//vector<int>v(5);	// 크기는 5, 초기화 값 0
//vector<int>v1(5, 3); // 크기는 5, 초기화 값 3


//2차원 벡터
vector<vector<int>> v2(5); // 행을 5로 고정
vector<vector<int>> v3; //행렬 모두 가변



int main() {


	// 2차원 벡터 초기화 case 1(고정 행일 시)
	for (int i = 0; i < 5; i++) {
		v2[i] = vector<int>(5, 3);
	}

	// 2차원 벡터 초기화 case 2(행렬 모두 가변일 시)
	for (int i = 0; i < 5; i++) {
		v3.push_back(vector<int>(5, 3));
	}



	// 선언
	vector<int> v;

	// 삽입
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);

	// 삭제
	v.pop_back();

	// size 확인
	cout << v.size();



	// 런타임 중 초기화
	v.clear(); // 모든 내용 삭제
	v.resize(10, 3); // 10으로 크기 조정 (새로 할당된 공간은 3값이 추가됨)

	v.assign(15, 7); // 초기화 + 재할당




	//int du = -1; // 디버깅용

	//// 디버깅
	//// F11: 코드 한 줄씩 확인
	//// F10: 함수가 중간에 있으면, 코드 한줄로 봄(프로시저 단위 실행)
	//// F9: 중단점(break point) 어디까지 확인할 것인가?
	//// F5: resume -> 중단점을 만날 때까지 실행



	return 0;
}