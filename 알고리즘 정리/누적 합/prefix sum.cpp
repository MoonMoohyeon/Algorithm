#include <iostream>
#include <vector>

using namespace std;

/*
===================================================================
 [누적 합 (Prefix Sum) 핵심 템플릿]
 
 1. 1차원 누적 합
    - psum[i] = psum[i-1] + arr[i] (1-based index 권장)
    - 구간 [L, R]의 합 = psum[R] - psum[L-1]  (O(1))

 2. 2차원 누적 합 (SWEA 2001 파리 퇴치, BOJ 11660 필수 패턴)
    - psum[i][j] = psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1] + arr[i][j]
    - (x1, y1)부터 (x2, y2)까지의 직사각형 합:
      = psum[x2][y2] - psum[x1-1][y2] - psum[x2][y1-1] + psum[x1-1][y1-1]

 3. 2차원 차분 배열 (IMOS법 / Programmers '파괴되지 않은 건물' 필수)
    - (x1, y1) ~ (x2, y2) 영역에 k를 더할 때:
      diff[x1][y1] += k;
      diff[x1][y2+1] -= k;
      diff[x2+1][y1] -= k;
      diff[x2+1][y2+1] += k;
    - 이후 가로 누적합, 세로 누적합을 1회씩 수행하면 전체 영역 반영 완료!
===================================================================
*/

const int MAX = 1005;
int arr1D[MAX];
int psum1D[MAX];

int arr2D[MAX][MAX];
int psum2D[MAX][MAX];

// 1차원 구간 합 구하기 예시
void solve1D() {
    int N = 5;
    int data[6] = {0, 10, 20, 30, 40, 50}; // 1-based

    for (int i = 1; i <= N; i++) {
        arr1D[i] = data[i];
        psum1D[i] = psum1D[i - 1] + arr1D[i];
    }

    // 2번째 원소부터 4번째 원소까지의 합 (20 + 30 + 40 = 90)
    int L = 2, R = 4;
    int rangeSum = psum1D[R] - psum1D[L - 1];
    cout << "1D [" << L << ", " << R << "] 구간 합: " << rangeSum << "\n";
}

// 2차원 직사각형 구간 합 구하기 예시
void solve2D() {
    int N = 4; // 4x4 행렬
    int sample[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 1, 2, 3, 4},
        {0, 2, 3, 4, 5},
        {0, 3, 4, 5, 6},
        {0, 4, 5, 6, 7}
    };

    // 2차원 누적 합 테이블 구축
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            arr2D[i][j] = sample[i][j];
            psum2D[i][j] = psum2D[i - 1][j] + psum2D[i][j - 1] - psum2D[i - 1][j - 1] + arr2D[i][j];
        }
    }

    // (2, 2) ~ (3, 4) 구간 합 질의
    int x1 = 2, y1 = 2, x2 = 3, y2 = 4;
    int rectSum = psum2D[x2][y2] - psum2D[x1 - 1][y2] - psum2D[x2][y1 - 1] + psum2D[x1 - 1][y1 - 1];
    cout << "2D (" << x1 << "," << y1 << ") ~ (" << x2 << "," << y2 << ") 구간 합: " << rectSum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "--- [1] 1차원 누적 합 데모 ---\n";
    solve1D();

    cout << "\n--- [2] 2차원 누적 합 데모 ---\n";
    solve2D();

    return 0;
}