#include <iostream>
// Problem: https://oj.nctu.edu.tw/problems/913/
bool detector(int *arr, int length, int target){
	if (!target) { return true; }
	if (length == 0 && target != 0) { return false; }
	if (arr[length - 1] > target) { return detector(arr, length - 1, target); }
	return detector(arr, length - 1, target) || detector(arr, length - 1, target - arr[length - 1]);
}
int main(int argc, char const *argv[]){
	int T = 0;
	scanf("%d", &T);
	while(T--){
		int n, k, sum = 0;
		scanf("%d%d", &n, &k);
		int data[n];
		for (int i = 0; i < n; i++) {
			scanf("%d", data + i);
			sum += data[i];
		}
		int tar = 100 * sum / (100 + k);
		if ((100 + k) * tar != 100 * sum) {
			printf("No\n");
			continue;
		}
		printf(detector(data,n,sum - tar)?"Yes\n":"No\n");
	}
	return 0;
}