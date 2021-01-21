#include <iostream>
// ref:
// https://www.geeksforgeeks.org/space-optimized-dp-solution-0-1-knapsack-problem/
int Maximum(const int & d1, const int & d2){
	return d1 > d2?d1:d2;
}
int main(int argc, char const *argv[]) {
	int n, m;
	scanf("%d%d", &n,&m);
	int score[n], time[n], dp[m + 1];
	for (int i = 0; i <= m; i++) {
		dp[i] = 0;
		if (i < n) { scanf("%d%d", score + i, time + i); }
	}
	for (int i = 0; i < n; i++) {
		for (int j = m; j >= time[i]; j--) {
			dp[j] = Maximum(dp[j], dp[j - time[i]] + score[i]); // max(exclude,include)
		}
	}
	printf("%d\n", dp[m]);
	return 0; 
}