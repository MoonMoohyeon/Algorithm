# 구현 & 시뮬레이션 (Implementation & Simulation)

삼성전자 SW 역량테스트, SWEA A/B형, 카카오 코딩테스트의 **핵심 킬러 및 합격 결정 유형**입니다.

---

## 1. 2차원 배열 회전 공식

$N \times M$ 행렬을 회전할 때 좌표 변환 공식:

### ① 시계 방향 90도 회전
- 크기: $N \times M \rightarrow M \times N$
- **공식**: `ret[j][N - 1 - i] = arr[i][j]`

### ② 반시계 방향 90도 회전
- 크기: $N \times M \rightarrow M \times N$
- **공식**: `ret[M - 1 - j][i] = arr[i][j]`

### ③ 180도 회전
- 크기: $N \times M \rightarrow N \times M$
- **공식**: `ret[N - 1 - i][M - 1 - j] = arr[i][j]`

---

## 2. 방향 전환 모듈러 연산 팁
방향을 `상(0), 우(1), 하(2), 좌(3)` 시계 순서로 정의하면 편리합니다.
- **우회전 (시계방향 90도)**: `dir = (dir + 1) % 4;`
- **좌회전 (반시계방향 90도)**: `dir = (dir + 3) % 4;`  *(음수 방지: -1 대신 +3)*
- **뒤로 돌기 (180도 반대)**: `dir = (dir + 2) % 4;`

---

## 3. 시뮬레이션 문제 해결 4단계 프로세스
1. **상태 모델링**: 격자(Grid), 물체(좌표, 방향, 속력, 상태 등 `struct`)를 명확히 정의.
2. **동시 이동 문제(Concurrent Movement)**: 여러 물체가 동시에 움직일 때 한 배열에서 직접 갱신하면 덮어쓰기 오류 발생! 반드시 `임시 배열(temp)`을 만들어 한 번에 이동 후 원본에 복사.
3. **경계 검사 및 순서 제어**: 문제 조건의 실행 순서(예: 이동 -> 충돌 처리 -> 회전)를 단계별 함수로 나누어 작성.
4. **디버깅용 출력 함수 사전 준비**: 단계별로 맵 상태를 콘솔에 출력해보며 문제 지문과 대조.

---

## 4. 추천 연습 문제
- **SWEA**
  - [1954. 달팽이 숫자 (D2)](https://swexpertacademy.com/) : 방향 전환 및 경계 체크 감각 회복
  - [2001. 파리 퇴치 (D2)](https://swexpertacademy.com/) : 2차원 누적합 & 구현
  - [2117. [모의 SW 역량테스트] 홈 방범 서비스](https://swexpertacademy.com/) : 마름모 영역 탐색
- **Programmers**
  - [키패드 누르기 (Lv.1)](https://school.programmers.co.kr/learn/courses/30/lessons/67256)
  - [행렬 테두리 회전하기 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/77485)
  - [삼각 달팽이 (Lv.2)](https://school.programmers.co.kr/learn/courses/30/lessons/68645)
