#include <iostream>
#include <map>
#include <cmath>
// Problem: https://oj.nctu.edu.tw/problems/848/
int main(int argc, char const *argv[]) {
	int n = 0;
	scanf("%d", &n);
	std::map<int, int> m;
	m[-1] = -1; m[2100000000] = -1;
	for (int i = 0; i < n; i++){
		int x, h, w;
		scanf("%d%d%d", &x, &h, &w);
		if(h == 0 || w == 0) { continue; }
		w += x;
		std::map<int, int>::iterator ep, en, fp, fn;
		std::map<int, int>::iterator it, eit;
		en = m.upper_bound(w);
		eit = en;
		ep = en;
		ep--;
		if (h > ep->second) {
			m[w] = (ep->second < 0)?0:ep->second;
			eit = m.lower_bound(w);
		}
		fn = m.lower_bound(x);
		it = fn;
		fp = fn;
		fp--;
		if (h > fp->second) {
			if (x == fn->first && h < fn->second) {	m[x] = fn->second; }
			else { m[x] = h; }
			it = m.upper_bound(x);
		}
		while (it != eit) {
			if (h >= it->second) {
				std::map<int, int>::iterator prev = it;
				prev--;
				if (prev->second > h) {	it->second = h; }
				else {
					m.erase(it);
					it = prev;
				}
			}
			it++;
		}
	}
	long long int area = 0, length = 0;
	for (std::map<int,int>::iterator it = m.begin(); it != m.end(); it++) {
		if (it->second == -1) { continue; }
		std::map<int, int>::iterator prev = it;
		prev--;
		if (prev->second == -1) { length += it->second; }
		else {
			area += (long long int)prev->second * (it->first - prev->first);
			if (prev->second != 0) {
				length += (it->first - prev->first); //exclude ground
			}
			length += abs(it->second - prev->second);
		}
	}
	printf("%lld %lld\n", length, area);
	return 0;
}