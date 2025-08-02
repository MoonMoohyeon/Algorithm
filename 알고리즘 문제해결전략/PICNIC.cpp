#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <unordered_map>
using namespace std;

int C;
int N;
int M;
int cnt = 0;
bool isFriend[11][11] = {{false,},};
bool selected[11] = {false,};

/*
    문제 정의
    N명의 학생이 있고, M개의 친구 쌍이 존재할 때 친구끼리만 쌍을 만들 수 있는 모든 경우의 수를 출력한다.

    isFriend = 친구 쌍을 저장하는 배열

    matching 함수
    selectedNum = 현재까지 선택된 친구의 수
    selectedNum == N이면 cnt++; (cnt는 가능한 경우의 수)
    
    else
    
    selected[] 배열 = 현재까지 선택된 친구들을 기록하는 배열
    selected[]에 없는 친구들에 대해서 매칭이 되는지 확인(friends 배열을 확인한다)
    매칭이 되면 selected[]에 추가하고 selectedNum을 2만큼 증가시킨다.
*/

int matching(int selectedNum) {
    if(selectedNum == N) {
        return 1;
    }

    int start;
    for (int i = 0; i < N; i++) {
        if(selected[i] == false) {
            start = i;  
            break;
        }
    }

    int result = 0;

    for(int other = start+1; other < N; other++) {
        if(selected[start] == false && selected[other] == false && isFriend[start][other] == true) {
            selected[start] = true;
            selected[other] = true;
            selectedNum += 2;
            result = result + matching(selectedNum);
            selected[other] = false;
            selected[start] = false;
            selectedNum -= 2;
        }
    }

    return result;
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    for(int t=0; t<C; t++) {
        cin >> N >> M;
        cnt = 0;
        
        for(int i = 0; i < 11; i++)
        {
            selected[i] = false;
        }

        for(int i = 0; i < 11; i++)
        {
            for(int j = 0; j < 11; j++)
            {
                isFriend[i][j] = false;
            }
        }

        for(int i=0; i<M; i++) {
            int a, b;
            cin >> a >> b; // a와 b가 친구
            isFriend[a][b] = true;
            isFriend[b][a] = true;
        }

        int result = matching(0);
        cout << result << "\n";
    }

    return 0;
}
