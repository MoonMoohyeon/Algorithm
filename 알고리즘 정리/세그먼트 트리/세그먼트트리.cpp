#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ll long long

ll arr[1000001];
ll tree[4000004];

void build(int idx, int left, int right) {
    if (left == right) {
        tree[idx] = arr[left];
        return;
    }

    int mid = (left + right) / 2;
    build(idx * 2, left, mid);
    build(idx * 2 + 1, mid + 1, right);
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}

void update(int idx, int left, int right, int target, ll value) {
    if (target < left || target > right) {
        return;
    }
    if (left == right) {
        tree[idx] = value;
        arr[target] = value;
        return;
    }

    int mid = (left + right) / 2;
    if (target <= mid) {
        update(idx * 2, left, mid, target, value);
    }
    else {
        update(idx * 2 + 1, mid + 1, right, target, value);
    }

    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}

ll query(int idx, int left, int right, int lptr, int rptr) {
    if (lptr > right || rptr < left) {
        return 0;
    }
    if (lptr <= left && right <= rptr) {
        return tree[idx];
    }

    int mid = (left + right) / 2;
    return query(idx * 2, left, mid, lptr, rptr) + query(idx * 2 + 1, mid + 1, right, lptr, rptr);
}

int N, M, K;

int main(int argc, char** argv) {
    
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 1; i <= N; ++i) {
        scanf("%lld", &arr[i]);
    }

    build(1, 1, N);

    for (int i = 0; i < M + K; ++i) {
        ll a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);

        if (a == 1) {
            update(1, 1, N, b, c);
        }
        else if (a == 2) {
            printf("%lld\n", query(1, 1, N, b, c));
        }
    }

    return 0;
}