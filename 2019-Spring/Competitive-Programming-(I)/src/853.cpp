#include <iostream>
// Problem: https://oj.nctu.edu.tw/problems/853/
int main(int argc, char const *argv[]){
	int n = 0, m = 0, q = 0;
	scanf("%d%d%d", &n, &m, &q);
	int a[50001], b[50001];
	for (int i = 0; i <= 50000; i++) {
		a[i] = 0;
		b[i] = 0;
	}
	a[0] = 1; b[0] = 1;
	int value, amax = 0, bmax = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &value);
		a[value]++;
		if(value > amax) { amax = value; }
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &value);
		b[value]++;
		if(value > bmax) { bmax = value; }
	}
	while (q--) {
		int xi = 0;
		long long int ans = 0;
		scanf("%d", &xi);
		for(int i = (xi - bmax > 0)?xi - bmax:0; i <= amax && i <= xi; i++) {
			ans += (long long int)a[i] * b[xi - i];	
		}
		printf("%lld\n",ans);
	}
	return 0;
}