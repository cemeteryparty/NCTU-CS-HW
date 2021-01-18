#include <iostream>
// Problem: https://oj.nctu.edu.tw/problems/912/
int x, y, z;
std::string s1, s2; //s2 to s1
int findMin(int a, int b, int c){
	if (a <= b && a <= c) { return a; }
	if (b <= a && b <= c) { return b; }
	return c;
}
int editDist(int m, int n){ //m = s2.pos(), n = s1.pos()
	if (!m) { //str2.empty() -> s1 --ins-> s2
		return n * x;
	}
	if (!n) { //str1.empty() -> s2 = "..." -> ""
		return m * y;
	}
	if (s1[n - 1] == s2[m - 1]) { //same char at cur pos
		return editDist(m - 1, n - 1);
	}
	int ins = x + editDist(m, n - 1), rm = y + editDist(m - 1, n), rep = z + editDist(m - 1, n - 1);
	return findMin(ins, rm, rep);
}
int main(int argc, char const *argv[]) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T, n, m;
	std::cin >> T;
	while (T--) {
		std::cin >> n >> m >> x >> y >> z;
		std::cin >> s1 >> s2;
		std::cout << editDist(s2.length(), s1.length()) << '\n';
	}
	return 0;
}