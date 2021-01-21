#include <iostream>

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }
    if (n == 1) {
        printf("%d\n", arr[0]);
        return 0;
    }
    long long int sa1ex = 0, sa1in = arr[0], sa2ex = 0, sa2in = arr[1], tmp;
    for (int i = 1; i < n - 1; i++) {
        tmp = sa1ex + arr[i];
        sa1ex = sa1in > sa1ex?sa1in:sa1ex;
        sa1in = tmp;
        tmp = sa2ex + arr[i + 1];
        sa2ex = sa2in > sa2ex?sa2in:sa2ex;
        sa2in = tmp;
    }
    tmp = sa1in > sa1ex?sa1in:sa1ex;
    tmp = tmp > sa2ex?tmp:sa2ex;
    tmp = tmp > sa2in?tmp:sa2in;
    printf("%lld\n", tmp);
}