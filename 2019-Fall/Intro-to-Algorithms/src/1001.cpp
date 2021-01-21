#include <iostream>

int n, arr[3000000];
long long int merge(int l, int m, int r) {
	int temp[r - l + 1], i = l, j = m + 1, k = 0;
	long long int v = 0;
	while ((i <= m) && (j <= r)) {
		if (arr[i] <= arr[j]) { temp[k++] = arr[i++]; }
		else {
			v += (m - i + 1);
			temp[k++] = arr[j++];
		}
	}
	while (i <= m) { temp[k++] = arr[i++]; }
	while (j <= r) { temp[k++] = arr[j++]; }
	for (int x = 0; x < k; x++) {
		arr[l + x] = temp[x];
	}
	return v;	
}
long long int mergesort(int l, int r) {
	if (l >= r) { return 0; }
	int m = (l + r) >> 1;
	long long int v = mergesort(l, m);
	v += mergesort(m + 1, r);
	v += merge(l, m, r);
	return v;
}
int main(int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	printf("%lld\n", mergesort(0, n - 1));
	return 0;
}