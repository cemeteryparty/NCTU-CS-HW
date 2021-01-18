#include <iostream>
// Problem: https://oj.nctu.edu.tw/problems/858/
bool check(long long int tar, int section, int *array, int length, bool legal) {
	int cut = 1;
	int max = -1, count = 1;
	for (int i = 0; i < length; i++) {
		if (array[i] > max) { max = array[i]; }
		if ((long long int)max * count <= tar) {
			if ((long long int)max * count == tar) {
				//judge if this ans exist
				legal = true;
			}
			count++;
			continue; 
		}
        count = 1;
        max = -1;
        i--;
        cut++;
    }
	if (cut <= section && legal) { return true; }
	return false;
}
int main(int argc, char const *argv[]) {
	int n = 0, k = 0;
	scanf("%d%d", &n, &k);
	int arr[n], max = -1;
	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
		if (arr[i] > max) { max = arr[i]; }
	}
	if (n == k) { printf("%d\n", max); }
	else if (k == 1) { printf("%lld\n", (long long int)max * n); }
	else {
		long long int l = max, r = (long long int)max * (n - k + 1);
		while (l + 1 < r) {
			long long int mid = (l + r) >> 1;
			bool flag = check(mid, k, arr, n, true);
			if (flag) { r = mid; }
			else { l = mid; }
		}
		for (long long int i = r; i >= l; i--) {
			if (check(i, k, arr, n, false)) {
				printf("%lld\n", i);
				break; 
			}
		}
	}
	return 0;
}