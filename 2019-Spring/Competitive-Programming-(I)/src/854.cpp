#include <iostream> 
// Problem: https://oj.nctu.edu.tw/problems/854/
int main(int argc, char const *argv[]) {
	int T = 0;
	scanf("%d", &T); 
	while (T--) {
		long long int a = 0;
		int p = 0;
		scanf("%lld%d", &a, &p);
		a %= p;
		long long int res = 1;
		int n = p - 2;
		while (n > 0) {
			if(n & 1) { res = res * a % p; }
			a = a * a % p;
			n >>= 1;
		}
		printf("%lld\n",res);
	} 
	return 0; 
}