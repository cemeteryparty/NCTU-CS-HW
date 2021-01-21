#include <iostream>
#include <queue>
#include <vector>
#define LLI long long int

std::priority_queue<LLI, std::vector<LLI>, std::greater<LLI> > q;
int main(int argc, char* const argv[]) {
	int n;
	LLI ans = 0, num;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%lld", &num);
		q.push(num);
	}
	while (q.size() != 1) {
		//sum the 2 most small element in q then push it in q
		num = q.top();
		q.pop();
		num += q.top();
		q.pop();
		q.push(num);
		ans += num;
	}
	printf("%lld\n", ans % 524287);
	return 0; 
}