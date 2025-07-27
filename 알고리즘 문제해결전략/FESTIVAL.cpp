#include <iostream>

using namespace std;

const double MAX = 100 * 1001;
double arr[1001];
double psum[1001];

int main(void) {
    int C, L, N;
    scanf("%d", &C);
    for(int i=0; i<C; i++) {
        for (int j = 1; j <= 1000; j++) {
            arr[j] = 0;
            psum[j] = 0;
        }
        scanf("%d %d", &N, &L);
        scanf("%lf", &arr[1]);
        psum[1] = arr[1];

        for(int j=2; j<=N; j++) {
            scanf("%lf", &arr[j]);
            psum[j] = psum[j-1] + arr[j];
        }

        double min = MAX;

        for(int j = N; j >= L; j--) {
            for(int k = L; j - k >= 0; k++) {
                // printf("test = %.d %.d %.2lf %.2lf\n", j, k, psum[j], psum[j-k]);
                if((psum[j] - psum[j-k]) / k < min) {
                    min = (psum[j] - psum[j-k]) / k;
                    // printf("min = %.2lf\n", min);
                }
            }
        }

        printf("%.12lf", min);
    }
    return 0;
}