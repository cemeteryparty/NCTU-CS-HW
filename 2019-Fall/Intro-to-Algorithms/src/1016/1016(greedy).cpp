#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
// similar to 1006.cpp
class Assignment {
public:
	int score, deadline;
	friend bool operator<(const Assignment & a1, const Assignment & a2) {
		return a1.score < a2.score;
	}
};
int main(int argc, char const *argv[]) {
	int n;
	scanf("%d", &n);
	Assignment arr[n];
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &arr[i].score, &arr[i].deadline);
	}
	std::sort(arr, arr + n);
	long long int profit = 0;
	std::priority_queue<int, std::vector<int> > q;
	for (int i = n - 1; i >= 0; i--) {
		int period = arr[i].deadline - (i?arr[i - 1].deadline:0);
		q.push(arr[i].score);
		while (period && !q.empty()) {
			profit += q.top();
			q.pop();
			period--;
		}
	}
	printf("%lld\n", profit);
	return 0; 
}