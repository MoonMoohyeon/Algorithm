#include <iostream>
using namespace std;

int binary_search(int *arr, int start, int end, int fv);
int binary_nonrecursive(int *arr, int start, int end, int fv);

int main(void) {

    int arr[100];
    // 이진 탐색은 반드시 정렬된 배열을 대상으로 해야 합니다.
    for(int i = 0; i < 100; i++) {
        arr[i] = i;
    }

    int fv = 0;
    cout << "찾을 값을 입력하세요 : ";
    cin >> fv;

    int rv = binary_search(arr, 0, 99, fv);
    int rv2 = binary_nonrecursive(arr, 0, 99, fv);
    
    cout << "재귀 방식 결과: " << rv << ", 반복 방식 결과: " << rv2 << endl;

    return 0;
}

/**
 * @brief 재귀 호출을 이용한 이진 탐색 함수 🔍
 * @param arr 정렬된 원본 배열
 * @param start 탐색을 시작할 인덱스
 * @param end 탐색을 마칠 인덱스
 * @param fv 찾고자 하는 값
 * @return 값이 있으면 해당 인덱스를, 없으면 -1을 반환
 */
int binary_search(int *arr, int start, int end, int fv) {
    // 재귀 호출의 종료 조건: 시작 인덱스가 끝 인덱스보다 커지면
    // 탐색 범위가 더 이상 없다는 뜻이므로, 찾는 값이 배열에 존재하지 않습니다.
    if (start > end) {
        return -1;
    }

    // 탐색 범위의 중간 인덱스를 계산합니다.
    // (start + end)가 int의 표현 범위를 넘는 오버플로우를 방지하기 위해
    // int mid = start + (end - start) / 2; 와 같이 계산하는 것이 더 안전합니다.
    int mid = (start + end) / 2;

    if (arr[mid] == fv) { // 1. 중간 값이 찾으려는 값과 같은 경우
        return mid; // 값을 찾았으므로 해당 인덱스를 반환하고 종료
    } else if (arr[mid] < fv) { // 2. 중간 값이 찾으려는 값보다 작은 경우
        // 찾는 값은 중간 지점의 오른쪽에 있을 것이므로, 탐색 범위를 오른쪽 절반으로 좁힙니다.
        return binary_search(arr, mid + 1, end, fv); // mid 다음 위치부터 end까지 재귀 호출
    } else { // 3. 중간 값이 찾으려는 값보다 큰 경우
        // 찾는 값은 중간 지점의 왼쪽에 있을 것이므로, 탐색 범위를 왼쪽 절반으로 좁힙니다.
        return binary_search(arr, start, mid - 1, fv); // start부터 mid 이전 위치까지 재귀 호출
    }
}

/**
 * @brief 반복문(while)을 이용한 이진 탐색 함수 🔄
 * @param arr 정렬된 원본 배열
 * @param start 탐색을 시작할 인덱스
 * @param end 탐색을 마칠 인덱스
 * @param fv 찾고자 하는 값
 * @return 값이 있으면 해당 인덱스를, 없으면 -1을 반환
 */
int binary_nonrecursive(int *arr, int start, int end, int fv) {
    // while(1)은 무한 루프입니다. 루프 내에서 return을 만나야 종료됩니다.
    // 일반적으로는 while(start <= end) 와 같이 조건을 명시하는 것이 더 직관적입니다.
    while(start <= end) { 
        int mid = (start + end) / 2; // 탐색 범위의 중간 인덱스 계산

        if(arr[mid] == fv) { // 1. 중간 값이 찾으려는 값과 같은 경우
            return mid; // 값을 찾았으므로 해당 인덱스를 반환하고 루프 종료
        } else if (arr[mid] < fv) { // 2. 중간 값이 찾으려는 값보다 작은 경우
            // 오른쪽 부분을 탐색하기 위해 시작점을 mid 다음으로 변경합니다.
            start = mid + 1;
        } else { // 3. 중간 값이 찾으려는 값보다 큰 경우
            // 왼쪽 부분을 탐색하기 위해 끝점을 mid 이전으로 변경합니다.
            end = mid - 1;
        }
    }
    
    // while 루프가 종료되었다는 것은 start > end 가 되어
    // 탐색 범위 내에 값이 없다는 의미입니다.
    return -1;
}