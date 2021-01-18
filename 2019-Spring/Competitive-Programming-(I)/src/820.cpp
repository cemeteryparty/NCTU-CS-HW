#include <iostream>
#include <string>
#include <vector>
#define ANS_SEG_MAX 1000000000
// https://oj.nctu.edu.tw/problems/820/
int main(int argc, char *argv[]) {
	std::string s;
	while (std::getline(std::cin, s)) {
		std::vector<long long int> ans;
		std::string num_str;
		char op = '+';
		s += ' ';
		for (int i = 0; i < s.length(); i++) {
			if ('0' <= s[i] && s[i] <= '9') { num_str += s[i]; }
			else {
				num_str = ' ' + num_str;
				std::vector<long long int> num;
				std::string sub;
				for (int si = num_str.length() - 1; si >= 0; si--) {
					if (num_str[si] == ' ' || sub.length() == 9) {
						num.push_back(atoll(sub.c_str()));
						sub.clear();
					}
					if ('0' <= num_str[si] && num_str[si] <= '9') {
						sub = num_str[si] + sub;
					}
				}
				if (op == '+') {
					int vi = 0;
					for (vi = 0; vi < num.size(); vi++) {
						if (vi >= ans.size()) { ans.push_back(0); }
						ans[vi] += num[vi];
						if (ans[vi] >= ANS_SEG_MAX) {
							if (vi + 1 >= ans.size()) { ans.push_back(0); }
							ans[vi + 1] += ans[vi] / ANS_SEG_MAX;
							ans[vi] %= ANS_SEG_MAX;
						}
					}
					for (int ai = vi; ai < ans.size(); ai++) {
						if (ans[ai] >= ANS_SEG_MAX) {
							if (ai + 1 >= ans.size()) { ans.push_back(0); }
							ans[ai + 1] += ans[ai] / ANS_SEG_MAX;
							ans[ai] %= ANS_SEG_MAX;
						}
						else { break; }
					}
				}
				else {
					if (num.size() == 1 && num[0] == 0) {
						ans.clear();
						ans.push_back(0);
						num_str.clear();
						num.clear();
						op = s[i];
						continue;
					}
					else if (num.size() == 1 && num[0] == 1) {
						num_str.clear();
						num.clear();
						op = s[i];
						continue;
					}
					std::vector<long long int> anscp;
					anscp.assign(ans.begin(), ans.end());
					num[0] -= 1;
					int ni = 0,ai = 0;
					for (ni = 0; ni < num.size(); ni++) {
						for (ai = 0; ai < anscp.size(); ai++){
							if (ai + ni >= ans.size()) { ans.push_back(0); }
							ans[ai + ni] += anscp[ai] * num[ni];
							if (ans[ai + ni] >= ANS_SEG_MAX) {
								if (ai + ni + 1 >= ans.size()) { ans.push_back(0); }
								ans[ai + ni + 1] += ans[ai + ni] / ANS_SEG_MAX;
								ans[ai + ni] %= ANS_SEG_MAX;
							}
						}
					}
					for (int a = ni + ai; a < ans.size(); a++) {
						if (ans[a] >= ANS_SEG_MAX) {
							if (a + 1 >= ans.size()) { ans.push_back(0); }
							ans[a + 1] += ans[a] / ANS_SEG_MAX;
							ans[a] %= ANS_SEG_MAX;
						}
						else { break; }
					}
				}
				num_str.clear();
				num.clear();
				op = s[i];
			} 
		}
		bool ops = false,stzero = false;
		for (int ai = ans.size() - 1; ai >= 0; ai--) {
			if(ans[ai]) { ops = true; }
			if (ops) {
				if (!stzero) {
					printf("%lld",ans[ai]);
					stzero = true;
				}
				else { printf("%09lld",ans[ai]); }
			}
		}
		if (!stzero) { printf("0"); }
		printf("\n");
		ans.clear();
	}
	return 0;
}