#include <iostream>
#include <algorithm>
#include <map>

class Assignment {
public:
	int score, deadline;
	friend bool operator<(const Assignment & a1, const Assignment & a2) {
		return a1.score < a2.score;
	}
};
int main(int argc, char const *argv[]){
	int n;
	long long int profit = 0;
	std::map<int, bool> m; // simulate schedule dp array
	
	// init: all false
	m[0] = false;
	m[2147483647] = false;

	scanf("%d", &n);
	Assignment arr[n];
	for (int i = 0; i < n; i++) {
		scanf("%d%d",&arr[i].score, &arr[i].deadline);
	}
	std::sort(arr, arr + n);

	for (int i = n - 1; i >= 0; i--) {
		std::map<int, bool>::iterator nit = m.upper_bound(arr[i].deadline), it;
		it = nit;
		it--; // first (# in m) < arr[i].deadline
		
		if (it->first == 1) {// no free time for this assignment
			continue;
		}
		profit += arr[i].score;
		if (it->second) {
			// no free time between it->first and arr[i].deadline
			std::map<int, bool>::iterator pit = it;
			pit--;
			if (it->first - 1 == pit->first) {
				// ex: T==FT==F -> T==TT==F -> T======F
				m.erase(it);
				m.erase(pit);
			}
			else {
				m[it->first - 1] = true;
				m.erase(it);
			}
		}
		else {
			if (it->first == arr[i].deadline) {
				// ex: T==FT==F -> T==TT==F -> T======F
				m.erase(it);
			}
			else { m[arr[i].deadline] = true; }
			if (arr[i].deadline + 1 == nit->first) {
				// ex: TT===F -> T====F 
				m.erase(nit);
			}
			else { m[arr[i].deadline + 1] = false; }
		}
	}  
	printf("%lld\n", profit);
	return 0; 
}