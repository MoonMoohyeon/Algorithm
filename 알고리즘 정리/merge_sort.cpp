#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

void merge(int a[], int left, int mid, int right);
void divide(int a[], int left, int right);

int main(void) {
    int arr[10] = {1, 16, 8, 4, 17, 9, 3, 7, 2, 11};

    divide(arr, 0, 9);

    // 정렬된 배열 출력
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

void divide(int a[], int left, int right) {
    if ((right - left + 1) <= 1) return; // 배열 크기가 1이면 종료

    int mid = (left + right) / 2;
    divide(a, left, mid);
    divide(a, mid + 1, right);
    merge(a, left, mid, right);
}

void merge(int a[], int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // 🔹 vector<int> 사용 (동적 할당)
    vector<int> leftArr(leftSize);
    vector<int> rightArr(rightSize);

    // 원본 배열에서 데이터 복사
    memcpy(leftArr.data(), a + left, leftSize * sizeof(int));
    memcpy(rightArr.data(), a + mid + 1, rightSize * sizeof(int));

    int i = 0, j = 0, k = left;

    // 🔹 병합 과정
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            a[k++] = leftArr[i++];
        } else {
            a[k++] = rightArr[j++];
        }
    }

    // 🔹 남은 요소 복사
    while (i < leftSize) {
        a[k++] = leftArr[i++];
    }
    while (j < rightSize) {
        a[k++] = rightArr[j++];
    }
}
