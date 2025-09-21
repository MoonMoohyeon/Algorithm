#include <iostream>
using namespace std;

/*
    그룹을 관리하는 알고리즘 = 쿼리형 처리
    
    그룹 합치기 = 유니온
    그룹 찾기 = 파인드
    최초 부모 배열 초기화 필요

    find 과정에서 트리가 편향되면 비효율적으로 변함
*/

int cntNode;
int cntQuery;
int parent[21];
int ran[21] = {0,};

int find2(int x) {
        if(parent[x] == x) return x;
        int root = find(parent[x]);
        parent[x] = root;
        return root;
}


int find(int x) {
    if(parent[x] == x) return x;

    return parent[x] = find(parent[x]);
}

int isunion(int a,int b) {
    if(find(a) == find(b)) return 1;
    return 0;
}

void Union(int A, int B) {
    int roota = find(A);
    int rootb = find(B);

    if(roota != rootb) {
        if(ran[roota] < ran[rootb]) {
            swap(roota, rootb);
        }

        parent[rootb] = roota;

        if(ran[roota] == ran[rootb]) ran[roota]++;
    }
}

int main(void) {

    for(int i=1; i <= cntNode; i++) {
        parent[i] = i;
    }

    cin >> cntNode >> cntQuery;
    for(int i = 0; i < cntQuery; i++) {
        int A, B;
        cin >> A >> B;
        Union(A, B);
    }

    for(int i=1; i <= cntNode; i++) {
        cout << parent[i] << " ";
    }
}