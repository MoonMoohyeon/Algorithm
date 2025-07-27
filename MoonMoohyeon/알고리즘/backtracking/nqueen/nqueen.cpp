#include <iostream>
#include <math.h> // abs 함수를 사용하기 위해 포함
using namespace std;

int cnt = 0; // 가능한 해의 개수를 저장하는 전역 변수
int n; // 체스판의 크기(N x N)이자 퀸의 개수
int board[16] = {0, }; // 퀸의 위치를 저장하는 배열. board[col] = row는 col열, row행에 퀸이 있음을 의미

// 현재 열(col)에 놓은 퀸이 이전에 놓인 퀸들과 충돌하는지 확인하는 함수
bool check(int col)
{
    // 1열부터 현재 열(col) 이전까지 모든 열을 순회
    for (int i = 1; i < col; i++)
    {
        // 같은 행에 다른 퀸이 있거나 (board[i] == board[col])
        // 대각선 상에 다른 퀸이 있는지 확인 (열의 차이와 행의 차이가 같으면 대각선에 위치)
        if (board[i] == board[col] || (col - i) == abs(board[i] - board[col]))
            return false; // 충돌하면 false 반환
    }

    return true; // 충돌하지 않으면 true 반환
}

// N-Queen 문제를 해결하기 위한 재귀 함수 (백트래킹 사용)
void nqueen(int col)
{
    // 모든 열(1부터 n까지)에 퀸을 성공적으로 배치한 경우
    if (col > n)
    {
        cnt++; // 해의 개수 증가
        return;
    }

    // 현재 열(col)의 모든 행(1부터 n까지)에 퀸을 놓아보는 시도
    for (int row = 1; row <= n; row++)
    {
        board[col] = row; // 현재 열(col)의 row행에 퀸을 배치
        
        // 방금 놓은 퀸이 유효한 위치인지 확인
        if (check(col))
        {
            // 유효하다면, 다음 열(col + 1)로 이동하여 퀸 배치를 계속 진행
            nqueen(col + 1);
        }
    }
}

int main()
{
    // 사용자로부터 체스판의 크기(n)를 입력받음
    scanf("%d", &n);

    // 1열부터 퀸 배치를 시작
    nqueen(1);

    // 찾은 모든 해의 개수를 출력
    printf("%d", cnt);

    return 0;
}