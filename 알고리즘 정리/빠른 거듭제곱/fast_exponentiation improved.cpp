#include <iostream>

typedef unsigned long long ull;

/**
 * @brief 빠른 거듭제곱 알고리즘으로 a^b를 계산합니다. (모듈러 연산 없음)
 * @param base 밑 (a)
 * @param exp 지수 (b)
 * @return ull a^b의 계산 결과
 * @warning 결과값이 매우 커질 수 있어 오버플로우 발생에 취약합니다.
 */
ull pure_power(ull base, ull exp) {
    // 기저 사례: 지수가 0이면 결과는 1입니다.
    if (exp == 0) {
        return 1;
    }

    // 지수를 절반으로 나누어 문제를 작게 만듭니다.
    ull half = pure_power(base, exp / 2);

    // 작은 문제의 답을 제곱합니다. (a^(b/2))^2 = a^b
    ull result = half * half;

    // 지수가 홀수였다면, 밑(base)을 한 번 더 곱해줍니다.
    if (exp % 2 != 0) {
        result = result * base;
    }

    return result;
}

int main() {
    ull a, b;
    std::cout << "a와 b를 입력하세요: ";
    std::cin >> a >> b;
    std::cout << a << "^" << b << " = " << pure_power(a, b) << std::endl;
    return 0;
}