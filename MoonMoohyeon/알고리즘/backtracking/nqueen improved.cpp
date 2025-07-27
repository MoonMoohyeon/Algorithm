#include <iostream>
#include <vector>
#include <cmath> // abs()를 위해

// 퀸의 위치를 저장하는 배열: board[col] = row
std::vector<int> board;

// 특정 위치가 유망한지 O(1)에 확인하기 위한 배열들 --> 개선사항
std::vector<bool> is_used_row;      // 특정 행이 사용 중인지 확인
std::vector<bool> is_used_diag1;    // 우상향 대각선(/)이 사용 중인지 확인
std::vector<bool> is_used_diag2;    // 우하향 대각선(\)이 사용 중인지 확인

int n;
int cnt = 0;

void nqueen(int col) {
    // 모든 열에 퀸을 성공적으로 배치한 경우
    if (col > n) {
        cnt++;
        return;
    }

    // 현재 열(col)의 모든 행(row)에 퀸을 놓아보는 시도
    for (int row = 1; row <= n; ++row) {
        // 현재 행과 대각선들이 사용 중이 아닌지 O(1) 만에 확인
        // 우상향 대각선 인덱스: col + row
        // 우하향 대각선 인덱스: col - row + n (음수 방지)
        if (is_used_row[row] || is_used_diag1[col + row] || is_used_diag2[col - row + n]) {
            continue; // 이미 사용 중이면 다음 행으로
        }

        // 퀸 배치 및 상태 업데이트
        board[col] = row;
        is_used_row[row] = true;
        is_used_diag1[col + row] = true;
        is_used_diag2[col - row + n] = true;

        // 다음 열로 재귀 호출
        nqueen(col + 1);

        // 백트래킹: 현재 위치의 퀸을 제거하고 상태를 원래대로 되돌림
        is_used_row[row] = false;
        is_used_diag1[col + row] = false;
        is_used_diag2[col - row + n] = false;
    }
}

int main() {
    // C++ 스타일 입출력 속도 향상 (선택 사항)
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> n;

    // 배열들 크기 초기화
    board.resize(n + 1);
    is_used_row.resize(n + 1, false);
    is_used_diag1.resize(2 * n + 2, false); // 대각선 인덱스 범위: 2 to 2n
    is_used_diag2.resize(2 * n + 2, false); // 대각선 인덱스 범위: 1-n to n-1 -> (보정) 1 to 2n-1

    nqueen(1);

    std::cout << cnt << "\n";

    return 0;
}