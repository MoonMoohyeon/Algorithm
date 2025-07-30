#include <iostream>
typedef unsigned long long ull;

ull base, exp, modular, k;

/*
exp가 짝수: base^exp = base^(exp/2 + exp/2) = base^(exp/2) * base^(exp/2)
exp가 홀수: base^exp = base^(exp/2 + exp/2 + 1) = base^(exp/2) * base^(exp/2 + 1)
(-> base * base^(exp-1)로 생각하는 것이 더 일반적입니다)
모듈러 분배 법칙: (base * exp) % c = (base%c * exp%c) % c
*/

ull power(ull exp) {
    // 기저 사례 1: 지수가 0이면, base^0 = 1이므로 1을 반환합니다.
    if (exp == 0) return 1;

    // 기저 사례 2: 지수가 1이면, a^1 % c = a % c 이므로 a % c를 반환합니다.
    // (이 부분은 필수는 아니지만, 재귀를 한 단계 덜 할 수 있게 해주는 최적화입니다.)
    if (exp == 1) return base % modular;

    // 지수를 절반으로 줄여 재귀 호출합니다.
    // 예를 들어 power(10)은 power(5)를 호출합니다.
    // 그 결과에 modular로 나눈 나머지를 전역 변수 k에 저장합니다.
    k = power(exp / 2) % modular;

    // 지수(exp)가 짝수인 경우
    // base^exp = (base^(exp/2)) * (base^(exp/2)) 입니다.
    // 따라서 k * k 에 c로 나눈 나머지를 반환합니다.
    if (exp % 2 == 0) {
        return k * k % modular;
    }
    // 지수(exp)가 홀수인 경우
    // base^exp = (base^(exp/2)) * (base^(exp/2)) * a 입니다.
    // 따라서 k * k * a 에 c로 나눈 나머지를 반환합니다.
    else {
        return k * k % modular * base % modular;
    }
}

int main() {
    scanf("%llu %llu %llu", &base, &exp, &modular);

    printf("%llu\n", power(exp));

    return 0;
}