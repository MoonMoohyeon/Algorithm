#include <iostream>
using namespace std;

int binary_search(int *arr, int start, int end, int fv);
int binary_nonrecursive(int *arr, int start, int end , int fv);

int main(void) {
    int arr[100];
    for(int i=0; i<100; i++) {
        arr[i] = i;
    }

    int fv = 0;
    cout << "find value : ";
    cin >> fv;
    int rv = binary_search(arr, 0, 99, fv);
    int rv2 = binary_nonrecursive(arr, 0, 99, fv);
    cout << "return value : " << rv << " " << rv2 << endl;

    return 0;
}

int binary_search(int *arr, int start, int end, int fv) {
    if (start > end) {
        return -1;
    }

    int mid = (start + end) / 2; // end - start, 오버플로우 방지

    if (arr[mid] == fv) {
        return mid;
    } else if (arr[mid] < fv) {
        return binary_search(arr, mid + 1, end, fv);
    } else {
        return binary_search(arr, start, mid - 1, fv);
    }
}

int binary_nonrecursive(int *arr, int start, int end , int fv) {
    while(1) { // start <= end
        int mid = (start + end) / 2;
        if (start > end) {
            return -1;
        }

        if(arr[mid] == fv) {
            return mid;
        } else if (arr[mid] < fv) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

}
