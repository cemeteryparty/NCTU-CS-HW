#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
// ref:
// https://cp-algorithms.com/schedules/schedule-with-completion-duration.html
class Assignment {
public:
	int deadline, time;
	friend bool operator<(const Assignment & a1, const Assignment & a2) {
		return a1.deadline < a2.deadline;
	}
};
int main(int argc, char const *argv[]) {
	int n;
	scanf("%d", &n);
	Assignment arr[n];
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &arr[i].deadline, &arr[i].time);
	}
	std::sort(arr, arr + n);
	int ans = 0;
	std::priority_queue<int, std::vector<int>, std::greater<int> > q;
	for (int i = n - 1; i >= 0; i--) {
		int period = arr[i].deadline - (i?arr[i - 1].deadline:0);
		q.push(arr[i].time);
		while (period && !q.empty()) {
			int q_min = q.top();
			q.pop();
			if (q_min <= period) {
				period -= q_min;
				ans++; // a job can be finished
			}
			else { // we still want to do this job
				q.push(q_min - period); // remain undone job
				period = 0;
			}
		}
	}
	printf("%d\n", ans);
	return 0; 
}