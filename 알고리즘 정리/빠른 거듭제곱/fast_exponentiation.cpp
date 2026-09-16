#include <iostream>

using namespace std;

typedef long long ll;

/*
===================================================================
 [빠른 거듭제곱 (Exponentiation by Squaring)]
 시간 복잡도: O(log exp)
 원리: a^b를 계산할 때, 지수를 절반으로 줄여가며 곱셈 횟수를 획기적으로 단축.
       - b가 짝수: a^b = (a^(b/2))^2
       - b가 홀수: a^b = (a^(b/2))^2 * a
 모듈러 연산 분배법칙: (A * B) % C = ((A % C) * (B % C)) % C
 필수 사용: BOJ 1629 (곱셈), SWEA 1217 (거듭 제곱), 페르마 소정리 기반 조합 계산
===================================================================
*/

// 1. 재귀 방식 (Recursive)
ll power_recursive(ll base, ll exp, ll mod) {
    if (exp == 0) return 1 % mod;
    if (exp == 1) return base % mod;

    // 지수를 절반으로 나눈 결과를 구함 (지역 변수 half로 안전하게 처리)
    ll half = power_recursive(base, exp / 2, mod);
    ll result = (half * half) % mod;

    // 지수가 홀수인 경우 밑(base)을 한 번 더 곱해줌
    if (exp % 2 == 1) {
        result = (result * (base % mod)) % mod;
    }

    return result;
}

// 2. 반복문 방식 (Iterative - 비트 연산 활용, 오버헤드가 적고 빠름)
ll power_iterative(ll base, ll exp, ll mod) {
    ll result = 1 % mod;
    base %= mod;

    while (exp > 0) {
        // 현재 비트가 1이면 (지수가 홀수이면) 누적 곱
        if (exp & 1) {
            result = (result * base) % mod;
        }
        // base를 제곱하고 지수를 절반으로 시프트
        base = (base * base) % mod;
        exp >>= 1;
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll base = 2, exp = 10, mod = 1000;
    // 2^10 = 1024 % 1000 = 24

    cout << "재귀 방식 결과: " << power_recursive(base, exp, mod) << "\n";
    cout << "반복문 방식 결과: " << power_iterative(base, exp, mod) << "\n";

    return 0;
}