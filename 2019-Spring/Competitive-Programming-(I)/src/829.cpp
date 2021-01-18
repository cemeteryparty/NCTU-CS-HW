#include <iostream>
#include <map>
#include <vector>
// Problem: https://oj.nctu.edu.tw/problems/829/
int main(int argc, char const *argv[]){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::string s, sub;
	std::map<std::string, int> m;
	std::vector<std::string> v;
	while (std::getline(std::cin, s)) {
		s += ' ';
		for (int i = 0; i < s.length(); i++) {
			if ('A' <= s[i] && s[i] <= 'Z') { s[i] += 32; }
			if ('a' <= s[i] && s[i] <= 'z') { sub += s[i]; }
			else if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\r') {
				if (sub.empty()) { continue; }
				else if (m.count(sub)) { m[sub]++; }
				else {
					m.insert(std::pair<std::string, int>(sub, 1));
					v.push_back(sub);
				}
				sub.clear();
			}
		}
	}
	for (int vi = 0; vi < v.size(); vi++) { printf("%s %d\n", v[vi].c_str(), m[v[vi]]); }
	return 0;
}
