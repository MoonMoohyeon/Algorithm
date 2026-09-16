#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    구현 & 시뮬레이션 핵심 템플릿
    
    1. 2차원 배열 시계 방향 90도 회전
    2. 2차원 배열 반시계 방향 90도 회전
    3. 테두리 회전 (프로그래머스 '행렬 테두리 회전하기' 스타일)
    4. 달팽이 배열 생성 (SWEA 1954 '달팽이 숫자' 스타일)
    5. 방향 전환 헬퍼 (시계방향 우회전, 반시계방향 좌회전, 180도 반대방향)
*/

// 상(0), 우(1), 하(2), 좌(3)
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

// 방향 전환 함수
int turn_right(int dir) { return (dir + 1) % 4; } // 시계 방향
int turn_left(int dir)  { return (dir + 3) % 4; } // 반시계 방향
int reverse_dir(int dir){ return (dir + 2) % 4; } // 반대 방향

// 1. N x M 배열 시계 방향 90도 회전
// 변환 공식: 회전 후 (r, c) = 원본 (N - 1 - c, r)  혹은  원본 (r, c) -> 회전 후 (c, N - 1 - r)
vector<vector<int>> rotate_90(const vector<vector<int>>& arr) {
    int n = arr.size();
    int m = arr[0].size();
    vector<vector<int>> ret(m, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ret[j][n - 1 - i] = arr[i][j];
        }
    }
    return ret;
}

// 2. N x M 배열 반시계 방향 90도 회전
vector<vector<int>> rotate_counter_90(const vector<vector<int>>& arr) {
    int n = arr.size();
    int m = arr[0].size();
    vector<vector<int>> ret(m, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ret[m - 1 - j][i] = arr[i][j];
        }
    }
    return ret;
}

// 3. 테두리 회전 (시계 방향 회전 및 최솟값 반환)
// (y1, x1) ~ (y2, x2) 직사각형의 테두리 원소들을 시계 방향으로 1칸 회전
int rotate_border(vector<vector<int>>& mat, int y1, int x1, int y2, int x2) {
    int temp = mat[y1][x1];
    int min_val = temp;

    // 좌측 열: 아래에서 위로
    for (int y = y1; y < y2; y++) {
        mat[y][x1] = mat[y + 1][x1];
        min_val = min(min_val, mat[y][x1]);
    }
    // 하단 행: 우에서 좌로
    for (int x = x1; x < x2; x++) {
        mat[y2][x] = mat[y2][x + 1];
        min_val = min(min_val, mat[y2][x]);
    }
    // 우측 열: 위에서 아래로
    for (int y = y2; y > y1; y--) {
        mat[y][x2] = mat[y - 1][x2];
        min_val = min(min_val, mat[y][x2]);
    }
    // 상단 행: 좌에서 우로
    for (int x = x2; x > x1 + 1; x--) {
        mat[y1][x] = mat[y1][x - 1];
        min_val = min(min_val, mat[y1][x]);
    }
    mat[y1][x1 + 1] = temp;

    return min_val;
}

// 4. 달팽이(소용돌이) 배열 생성 (N x N 크기)
vector<vector<int>> make_snail_matrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    int y = 0, x = 0, dir = 1; // 우측 방향(1)부터 시작: 우(1), 하(2), 좌(3), 상(0)

    for (int num = 1; num <= n * n; num++) {
        matrix[y][x] = num;

        int ny = y + dy[dir];
        int nx = x + dx[dir];

        // 범위를 벗어나거나 이미 숫자가 채워져 있다면 방향 전환
        if (ny < 0 || ny >= n || nx < 0 || nx >= n || matrix[ny][nx] != 0) {
            dir = turn_right(dir);
            ny = y + dy[dir];
            nx = x + dx[dir];
        }

        y = ny;
        x = nx;
    }

    return matrix;
}

void print_matrix(const string& title, const vector<vector<int>>& mat) {
    cout << title << "\n";
    for (const auto& row : mat) {
        for (int val : row) cout << val << "\t";
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 90도 회전 테스트
    vector<vector<int>> original = {
        {1, 2, 3},
        {4, 5, 6}
    };
    print_matrix("--- 원본 행렬 (2x3) ---", original);
    print_matrix("--- 시계 방향 90도 회전 (3x2) ---", rotate_90(original));
    print_matrix("--- 반시계 방향 90도 회전 (3x2) ---", rotate_counter_90(original));

    // 2. 테두리 회전 테스트
    vector<vector<int>> board = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    print_matrix("--- 테두리 회전 전 ---", board);
    int min_val = rotate_border(board, 0, 0, 3, 3);
    print_matrix("--- (0,0)~(3,3) 테두리 회전 후 ---", board);
    cout << "회전된 원소 중 최솟값: " << min_val << "\n\n";

    // 3. 달팽이 행렬 테스트
    vector<vector<int>> snail = make_snail_matrix(4);
    print_matrix("--- 달팽이 숫자 행렬 (4x4) ---", snail);

    return 0;
}
