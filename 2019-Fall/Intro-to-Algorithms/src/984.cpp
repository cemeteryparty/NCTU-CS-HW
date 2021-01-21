#include <iostream>
// ref:
// http://alrightchiu.github.io/SecondRound/comparison-sort-merge-sorthe-bing-pai-xu-fa.html
// https://www.geeksforgeeks.org/counting-inversions/
// get ans in mergesort
long long int merge(int *array, int left, int mid, int right) { // mid = rsub.begin()
	int temp[right - left + 1], i = left, j = mid, k = 0;
	// i = lsub.begin(), j = rsub.begin(), k = temp.begin()
	long long int v = 0;
	while ((i < mid) && (j <= right)) {
		if (array[i] <= array[j]) { temp[k++] = array[i++]; }
		else {
			temp[k++] = array[j++];
			v += (mid - i);
		}
	}
	while (i < mid) { temp[k++] = array[i++]; }
	while (j <= right) { temp[k++] = array[j++]; }
	for (int i = 0; i <= right - left; i++) {
		array[left + i] = temp[i];
	}
	return v;
}
long long int mergesort(int *array, int left, int right) {
	int mid = ((left + right) >> 1);
	long long int v = 0;
	if (left < right) {
		v = mergesort(array, left, mid);
		v += mergesort(array, mid + 1, right);
		v += merge(array, left, mid + 1, right);
	}
	return v;
}
int main(int argc, char const *argv[]) {
	int n;
	scanf("%d", &n);
	int arr[n];
	for(int i = 0; i < n; i++) {
		scanf("%d",(arr + i));
	}
	printf("%lld\n", mergesort(arr, 0, n - 1) % 524287);
	return 0; 
}