#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int left, int right) {
    // 오름차순 정렬
    if(left < right) return true;
    if(left > right) return false;

    // return left < right;

    return false;
}

bool cmp2(int left, int right) {
    // 내림차순 정렬
    if(left > right) return true;
    if(left < right) return false;

    // return left > right;

    return false;
}

bool cmp3(int left, int right) {
    /*
        1. 짝수 우선
        2. 큰 수 우선
    */

    if(left % 2 && !right % 2) return false;
    if(!left % 2 && right % 2) return true;
    if(left > right) return true;
    if(left < right) return false;
    
    return false;
}

struct coord {
    int x, y;
    bool operator<(coord right) { // 구조체 내에서 정의
        if(y > right.y) return true;
        if(y < right.y) return false;
        if(x < right.x) return true;
        if(x > right.x) return false;
    }
};

coord operator+(coord left, coord right) { // 구조체 밖에서 정의
    return{left.y + right.y, left.x +  right.x};
}

bool cmp_coord(coord left, coord right) {
    if(left.y > right.y) return true;
    if(left.y < right.y) return false;

    if(left.x < right.x) return true;
    if(left.x > right.x) return false;

    return false;
}

int main(void) {
    int arr[10] = {27,42,37,10,88,20,77,77,1,100};

    sort(arr, arr+10, less<>()); // 오름차순

    for(int i=0; i<10; i++) {
        cout << arr[i] << " ";
    }

    sort(arr, arr+10, greater<>()); // 내림차순

    /*
        옵션 함수 만들기
        cmp 함수 또는 함수 객체 사용
    */

    // 구조체 정렬
    coord co[4] = {
        {1,4},
        {4,3},
        {2,5},
        {6,7},
    };

    sort(co, co+4);
    for(int i=0; i<4; i++) {
        cout << co[i].y << ", " << co[i].x << "\n";
    }

}