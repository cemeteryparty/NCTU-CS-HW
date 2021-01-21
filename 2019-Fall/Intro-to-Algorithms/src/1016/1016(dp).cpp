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

int Maximum(const int & d1, const int & d2) {
	return d1 > d2?d1:d2;
}
int main(int argc, char const *argv[]) {
	int n, day = -1;
	long long int profit = 0;
	std::map<int, int> m;
	scanf("%d", &n);
	Assignment arr[n];
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &arr[i].score, &arr[i].deadline);
		m[arr[i].deadline] = arr[i].deadline;
		if (arr[i].deadline > day) { day = arr[i].deadline; }
	}

	std::sort(arr, arr + n);
	bool schedule[day] = {false};
	int full = 0; // no space lower than full
	for(int i = n - 1; i >= 0; i--) {
		for (int j = m[arr[i].deadline] - 1; j >= full; j--) { 
			// use map to speed up search
			if (!schedule[j]) {
				profit += arr[i].score;
				schedule[j] = true;
				m[arr[i].deadline] = j;
				break;
			}
			if (j == full) { full = Maximum(arr[i].deadline - 1, full); }
		}
	}
		
	printf("%lld\n", profit);
	return 0; 
}