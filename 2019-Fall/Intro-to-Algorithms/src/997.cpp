#include <iostream>
#include <cmath>
#include <algorithm>
// ref:
// https://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/
int arr[500],n;
int main(int argc, char const *argv[]) {
	int sum = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", arr + i);
		sum += arr[i];
	}
	bool dp[n + 1][sum + 1]; // [index][sum detect]
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= sum; j++) {
			if (!i) { // when no element,only sum = 0 is true
				dp[i][j] = false;
			}
			if (!j) { // when sum = 0,always true for first i elements was handled
				dp[i][j] = true; 
			}
			else if (i) { // exclude || include arr[i - 1]
				dp[i][j] = dp[i - 1][j] || (arr[i - 1] <= j?dp[i - 1][j - arr[i - 1]]:false);
			}
		}
	}
	for (int j = (sum >> 1); j >= 0; j--) {
		if (dp[n][j]) {
			printf("%d\n", sum - (j << 1));
			break;
		}
	}
	return 0;
}