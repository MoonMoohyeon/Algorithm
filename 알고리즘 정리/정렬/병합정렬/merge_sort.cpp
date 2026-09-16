#include <iostream>

using namespace std;

/*
===================================================================
 [병합 정렬 (Merge Sort)]
 시간 복잡도: O(N log N) 보장 (최선, 평균, 최악 모두 동일)
 안정 정렬(Stable Sort): 값이 같은 원소들의 상대적 순서 유지
 분할 정복 (Divide and Conquer):
   1. Divide: 배열을 절반으로 분할 (크기 1이 될 때까지)
   2. Conquer & Combine: 두 정렬된 부분 배열을 임시 버퍼를 이용해 하나로 병합
 
 ※ 주의: merge() 함수 내부에서 매번 vector나 동적 배열을 생성하면
          메모리 할당 오버헤드로 인해 시간 초과(TLE)가 발생할 수 있습니다.
          따라서 전역 임시 배열(temp)을 1회만 할당하여 재사용하는 것이 표준입니다.
===================================================================
*/

const int MAX = 100005;
int arr[MAX];
int temp[MAX]; // 병합 시 사용할 전역 임시 배열

// 두 정렬된 부분 배열 [left, mid]와 [mid+1, right]를 병합
void merge(int left, int mid, int right) {
    int i = left;      // 왼쪽 부분 배열 포인터
    int j = mid + 1;   // 오른쪽 부분 배열 포인터
    int k = left;      // temp 배열에 채워넣을 위치

    // 두 부분 배열에서 작은 값을 골라 temp에 저장
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) { // <= 조건을 통해 안정 정렬(Stable) 보장
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // 왼쪽 배열에 남은 원소들 복사
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // 오른쪽 배열에 남은 원소들 복사
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 정렬된 임시 배열(temp)의 내용을 원본 배열(arr)에 복사
    for (int idx = left; idx <= right; idx++) {
        arr[idx] = temp[idx];
    }
}

// 분할 정복 재귀 함수
void merge_sort(int left, int right) {
    // 기저 조건: 크기가 1 이하이면 이미 정렬된 상태
    if (left >= right) return;

    int mid = left + (right - left) / 2; // 오버플로우 방지 중간점 계산

    merge_sort(left, mid);      // 왼쪽 분할
    merge_sort(mid + 1, right);  // 오른쪽 분할
    merge(left, mid, right);    // 병합
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int sample[10] = {1, 16, 8, 4, 17, 9, 3, 7, 2, 11};
    int N = 10;

    for (int i = 0; i < N; i++) {
        arr[i] = sample[i];
    }

    merge_sort(0, N - 1);

    cout << "정렬 결과: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}