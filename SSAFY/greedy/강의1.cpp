
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    적용 원칙
    greedy choice property - 선택기준이 변경되면 안된다.
    optimal substructure - 부분 최적해
    수학적 검증 가능

    문제풀이 과정
    S-V-I
    Selection : 선택 기준 정하기
    Validation : 검증, 테스트 케이스 검증
    Implementation : 구현
*/

int main() {
    /*
        동전 교환
        cost와 동전이 존재.
        cost를 만들 수 있는 최소 동전 개수는 몇 개인가?
        cost : 1750
        동전 : 500, 100, 50, 10
    */

    /*
        ATM 존재
        총 N명의 사람, 각 사람마다 ATM 사용 시간
        모든 사람이 ATM 사용을 완료하는데 걸리는 최소 대기 시간 구하기
        5
        100 50 20 30 70

        0 20 50 100 170

        사용 시간이 가장 짧은 사람 우선
        N명 중 1명 사용한다면, 대기 인원 : N - 1
        20 * (N - 1) = 80
        30 * (N - 2) = 90
        50 * (N - 3) = 100
        70 * (N - 4) = 70
        == 340

    */

    int arr[100] = {0,};
    int N = 0;
    int ans = 0; // 최소 대기 시간
    
    cin >> N;

    int t = N - 1; // 초기 대기 인원 수
    for(int i=0; i<N; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + N);
    
    for(int i=0; i<N; i++) {
        ans += arr[i] * t;
        t--;    
    }

    cout << ans;

    /*
        회의실 배정
        미팅 정보가 주어진다.
        각각의 시작 시간과 종료 시간이 주어졌을 때 최대한 많은 회의가 열리도록 만들기
    */

}