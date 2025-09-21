#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ll long long

int N, M, K;
ll arr[1000001];
ll tree[4000004];
ll lazy[4000004];

ll build(int idx, int start, int end) {
    if (start == end) {
        return tree[idx] = arr[start];
    }

    int mid = (start + end) / 2;
    return tree[idx] = build(idx * 2, start, mid) + build(idx * 2 + 1, mid + 1, end);
}

void propagate(int idx, int start, int end) {
    if (lazy[idx] != 0) {
        tree[idx] += (end - start + 1) * lazy[idx];
        if (start != end) {
            lazy[idx * 2] += lazy[idx];
            lazy[idx * 2 + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update_range(int idx, int start, int end, int left, int right, ll diff) {
    propagate(idx, start, end);
    if (start > right || end < left) return;
    if (left <= start && end <= right) {
        tree[idx] += (end - start + 1) * diff;
        if (start != end) {
            lazy[idx * 2] += diff;
            lazy[idx * 2 + 1] += diff;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_range(idx * 2, start, mid, left, right, diff);
    update_range(idx * 2 + 1, mid + 1, end, left, right, diff);
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}

ll query(int idx, int start, int end, int left, int right) {
    propagate(idx, start, end);
    if (start > right || end < left) return 0;
    if (left <= start && end <= right) {
        return tree[idx];
    }

    int mid = (start + end) / 2;
    return query(idx * 2, start, mid, left, right) + query(idx * 2 + 1, mid + 1, end, left, right);
}

void printtree() {
    for (int i = 0; i < 20; ++i) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}

int main() {

    scanf("%d %d %d", &N, &M, &K);
    for (int i = 1; i <= N; ++i) {
        scanf("%lld", &arr[i]);
    }
    build(1, 1, N);
    //printtree();
    for (int i = 0; i < M + K; ++i) {
        int a;
        scanf("%d", &a);

        if (a == 1) {
            int b, c;
            ll d;
            scanf("%d %d %lld", &b, &c, &d);
            update_range(1, 1, N, b, c, d);
            //printtree();
        }
        else if (a == 2) {
            int b, c;
            scanf("%d %d", &b, &c);
            printf("%lld\n", query(1, 1, N, b, c));
        }
    }


    return 0;
}