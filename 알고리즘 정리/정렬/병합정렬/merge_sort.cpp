#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

void merge(int a[], int left, int mid, int right); // 두 부분으로 나뉜 배열을 정렬하며 병합하는 함수
void divide(int a[], int left, int right);       // 배열을 계속해서 두 부분으로 나누는 함수

int main(void) {
    int arr[10] = {1, 16, 8, 4, 17, 9, 3, 7, 2, 11};

    divide(arr, 0, 9);

    cout << "정렬된 배열: ";
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

/**
 * @brief 배열을 재귀적으로 두 부분으로 나누는 함수 (Divide 쪼개기)
 * @param a 정렬할 원본 배열
 * @param left 분할할 배열의 시작 인덱스
 * @param right 분할할 배열의 끝 인덱스
 */
void divide(int a[], int left, int right) {
    // 재귀 호출의 종료 조건: 배열의 크기가 1 이하이면 더 이상 나눌 수 없으므로 함수를 종료합니다.
    // (right - left + 1)은 현재 배열 부분의 크기를 나타냅니다.
    if ((right - left + 1) <= 1) return;

    // 배열의 중간 지점 인덱스를 계산합니다.
    // (left + right) / 2는 정수 나눗셈을 통해 중간 인덱스를 구합니다.
    int mid = (left + right) / 2;

    // 재귀 호출을 통해 왼쪽 부분을 다시 나눕니다. (left ~ mid)
    divide(a, left, mid);

    // 재귀 호출을 통해 오른쪽 부분을 다시 나눕니다. (mid + 1 ~ right)
    divide(a, mid + 1, right);

    // 나누어진 두 부분을 정렬하면서 다시 하나로 병합합니다. (Conquer & Combine 합치기)
    merge(a, left, mid, right);
}

/**
 * @brief 두 개의 정렬된 부분 배열을 하나의 정렬된 배열로 병합하는 함수 (Merge 합치기)
 * @param a 정렬할 원본 배열
 * @param left 왼쪽 부분 배열의 시작 인덱스
 * @param mid 왼쪽 부분 배열의 끝 인덱스 (경계선)
 * @param right 오른쪽 부분 배열의 끝 인덱스
 */
void merge(int a[], int left, int mid, int right) {
    // 왼쪽과 오른쪽 부분 배열의 크기를 계산합니다.
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // 🔹 임시 배열 생성
    // 정렬된 결과를 담을 임시 배열을 C++ vector를 사용해 만듭니다.
    vector<int> leftArr(leftSize);
    vector<int> rightArr(rightSize);

    // 🔹 데이터 복사
    // memcpy를 사용하여 원본 배열(a)의 데이터를 임시 배열로 빠르게 복사합니다.
    // leftArr.data()는 vector의 내부 배열 포인터를 반환합니다.
    memcpy(leftArr.data(), a + left, leftSize * sizeof(int));
    memcpy(rightArr.data(), a + mid + 1, rightSize * sizeof(int));

    int i = 0;      // leftArr의 인덱스
    int j = 0;      // rightArr의 인덱스
    int k = left;   // 원본 배열 a에 정렬된 값을 채워넣을 위치의 인덱스

    // 🔹 병합 과정 (Merge)
    // 두 임시 배열의 요소를 비교하며 작은 값을 원본 배열 a에 순서대로 넣습니다.
    while (i < leftSize && j < rightSize) {
        // 왼쪽 배열의 현재 값이 오른쪽 배열의 현재 값보다 작거나 같으면
        if (leftArr[i] <= rightArr[j]) {
            a[k++] = leftArr[i++]; // 왼쪽 값을 원본 배열에 넣고, 인덱스 i와 k를 1 증가시킵니다.
        } else { // 오른쪽 배열의 현재 값이 더 작으면
            a[k++] = rightArr[j++]; // 오른쪽 값을 원본 배열에 넣고, 인덱스 j와 k를 1 증가시킵니다.
        }
    }

    // 🔹 남은 요소 복사
    // 위 while문이 끝난 후, 둘 중 하나의 배열에는 아직 요소가 남아있을 수 있습니다.
    // 남아있는 요소들을 원본 배열 a의 뒷부분에 순서대로 복사합니다.

    // 왼쪽 배열에 요소가 남아있다면
    while (i < leftSize) {
        a[k++] = leftArr[i++];
    }
    // 오른쪽 배열에 요소가 남아있다면
    while (j < rightSize) {
        a[k++] = rightArr[j++];
    }
}