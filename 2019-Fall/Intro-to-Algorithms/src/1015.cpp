#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define LLI long long int

std::priority_queue<LLI, std::vector<LLI>, std::greater<LLI> > q;
int main(int argc, char const *argv[]) {
    int n;
    LLI n1, n2;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &n1);
        q.push(n1);
    }
    while (q.size() != 1) {
        n1 = q.top();
        q.pop();
        n2 = q.top();
        q.pop();
        q.push((n1 + n2) << 1);
    }
    printf("%lld\n", q.top());
    return 0; 
}