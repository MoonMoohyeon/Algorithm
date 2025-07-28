#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

int psum[100001];
vector<int> res;

int main(void)
{
    int N, M, num;
    scanf("%d %d", &N, &M);
    psum[0] = 0;
    scanf("%d", &psum[1]);
    for (int i = 1; i < N; i++)
    {
        scanf("%d", &num);
        psum[i + 1] = psum[i] + num;
    }

    int st, ed, sum = 0;
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d", &st, &ed);
        sum = psum[ed] - psum[st-1];
        res.push_back(sum);
    }

    for (auto iter = res.begin(); iter != res.end(); iter++)
    {
        printf("%d\n", *iter);
    }

    return 0;
}