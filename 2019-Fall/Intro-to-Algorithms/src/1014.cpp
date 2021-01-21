#include <iostream>

int main(int argc, char const *argv[]) {
	int n;
	scanf("%d", &n);
	int arr[n];
	for(int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	int begin = 0, end = 0, bi = 0;
	long long int imax = 0, maxarr = -2147483648;
	for (int i = 0; i < n; i++) {
		imax += arr[i];
		if (imax > maxarr) {
			maxarr = imax;
			begin = bi;
			end = i + 1;
		}
		if (imax < 0) {
			imax = 0;
			bi = i + 1;
		}
	}
	printf("%d %d\n", begin, end);
	return 0; 
}