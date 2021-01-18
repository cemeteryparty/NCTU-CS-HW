#include <iostream>
#include <string>
#include <vector>
// Problem: https://oj.nctu.edu.tw/problems/819/
int main(int argc, char *argv[]) {
	std::string s;
	while (std::getline(std::cin, s)) {          
		std::vector<unsigned long long int> v;
		v.push_back(0);
		s = ' ' + s;
		std::string sub;
		int vi = 0;
		for (int i = s.length() - 1; i >= 0; i--) {
			if (sub.length() == 18 || s[i] == ' ') {
				if(sub.empty())
					continue;
				v[vi] += stoull(sub,NULL);
				v.push_back(0);
				unsigned long long int n = 1000000000000000000U;
				for (int vx = vi; vx < v.size(); vx++){
					if (v[vx] >= n) {
						v[vx + 1]++;
						v[vx] -= n; 
					}
					else { break; }
				}
				sub.clear();
				vi++;
				if (s[i] == ' ') { vi = 0; }
			}
			if ('0' <= s [i] && s[i] <= '9') { sub = s[i] + sub; }
		}
		bool ops = false, stzero = false;
		for (int ai = v.size() - 1; ai >= 0; ai--) {
			if (v[ai]) { ops = true; }
			if (ops) {
				if(!stzero){
					printf("%llu",v[ai]);
					stzero = true;
				}
				else { printf("%018llu",v[ai]); }
			}
		}
		if (!stzero) { printf("0"); }
		printf("\n");
		v.clear();
	}
	return 0;
}
