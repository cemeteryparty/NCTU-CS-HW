#include <iostream>
#include <map>
// Problem: https://oj.nctu.edu.tw/problems/843/
int main(int argc, char const *argv[]) {
	long long int x = 0, y = 0;
	int q = 0;
	scanf("%lld%lld%d", &x, &y, &q);
	long long int total = x * y;
	std::map<long long int, long long int> m;
	m[0] = 0;
	while (q--) {
		long long int i = 0, j = 0, count = 0;
		scanf("%lld%lld", &i, &j);
		long long int p1k = i, p1v = 0, p2k = 0, p2v = j;
		std::map<long long int, long long int>::iterator up = m.upper_bound(i), it;
		up--;
		for (it = up; ; it--) {
			if (j < it->second) { break; }
			count += ((i - it->first) * (j - it->second));
			i = it->first;
			if (it == m.begin()) { break; }
		}
		if (!count) { printf("QAQ\n"); }
		else {
			printf("%lld\n", count);
			p2k = i;
			p1v = up->second;
			m.erase(++it, ++up);
			m[p1k] = p1v;
			m[p2k] = p2v;
		}
		total -= count;
	}
	printf("%lld\n", total);
	return 0;
}