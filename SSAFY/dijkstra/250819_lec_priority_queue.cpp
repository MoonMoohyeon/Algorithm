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


		// ���Ŀ����� ���� �� �켱 -> �켱���� ť�� �����ϸ� ū �� �켱�� ��
		// -> sort �Լ��� ���� ���� �Լ��� ������ ���� �޸� 
		// ���� ���ʿ� ���� ���� �켱������ ����. 
		// ���İ��� !!�ݴ�!!�� �Լ� ������ �����
	};
};

struct Coord {
	int y, x;

	// �� struct�� ������ ���� ���� �ٲ� �� ������ struct ���ο� ����
	bool operator<(Coord right) const {
		// y ū�� �ſ켱
		if (y < right.y) return true;
		if (y > right.y) return false;

		// x ���� �� �켱
		if (x < right.x) return false;
		if (x > right.x) return true;
		return false;
	}
};


struct coordCmp {
	// ���� ���� �ٲ� �� ����ϸ� function object��
	bool operator() (Coord left, Coord right) const {
		// y ū �� �켱(�켱���� ť ���� ����, ū �� ���������� ����)
		if (left.y < right.y) return true;
		if (left.y > right.y) return false;

		// x ū �� �켱
		if (left.x < right.x) return true;
		return false;
	};
};

int main() {

	Plus p;
	int ans = p(1, 2);
	///////////////////////////////////////////////////////////////////////////////////
	/*

	�⺻ ������ Ÿ��
	 -> �⺻ ���� �ɼ� ������ ���� less, greater
	 -> function object ���(��ü�� �Լ�ó�� ���� ���)
	 -> operator< �����ε� �ȵ�
	*/
	
	priority_queue<int>pq1;	// �ִ밪 ��Ʈ
	
	// container adapter
	priority_queue<int, vector<int>, greater<>>pq2;	// �ּҰ� ��Ʈ
	priority_queue<int, vector<int>, cmp>pq3;	// �ִ밪 ��Ʈ

	// ������ �߰�
	// O(logN)
	//pq.push(1);
	//pq.push(5);
	//pq.push(3);
	//pq.push(2);

	//// ���� �켱���� ���� �� ����(�� ū �� default, MaxHeap ����)
	//// O(1)
	//cout << pq.top() << "\n";

	//// ������ ����(��Ʈ = ���� �켱���� ���� ��)
	//// O(logN)
	//pq.pop();
	//cout << pq.top();

	// ť�� ������� Ȯ��
	//pq.empty();

	// ������ ���� : �뷱�� -> heapify 
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

	struct ó�� ����� ���� ���
	 -> �⺻ ���� �ɼ� ������ X
	 -> function object ���ok
	 -> operator< �����ε� ok
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