#include <iostream>
// Problem: https://oj.nctu.edu.tw/problems/912/
int x, y, z;
std::string s1, s2; //s2 to s1
int findMin(int a, int b, int c){
	if (a <= b && a <= c) { return a; }
	if (b <= a && b <= c) { return b; }
	return c;
}
int main(int argc, char const *argv[]) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T, n, m;
	std::cin >> T;
	while (T--) {
		std::cin >> n >> m >> x >> y >> z;
		std::cin >> s1 >> s2;

		int dp[m + 1][n + 1]; //m = s2.pos(),n = s1.pos()
		for (int i = 0; i <= m; i++) {
			for (int j = 0; j <= n; j++) {
				if (!i) { //str2.empty() -> s1 --ins-> s2
					dp[i][j] = x * j;
				}
				else if (!j) { //str1.empty() -> s2 = "..." -> ""
					dp[i][j] = y * i;
				}
				else if (s2[i - 1] == s1[j - 1]) { //same char at cur pos
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					int ins = x + dp[i][j - 1], rm = y + dp[i - 1][j], rep = z + dp[i - 1][j - 1];
					dp[i][j] = findMin(ins, rm, rep);
				}
			}
		}
		std::cout << dp[m][n] << '\n';
	}
	return 0;
}