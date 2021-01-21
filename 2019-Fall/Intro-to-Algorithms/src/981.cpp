#include <iostream>
#include <algorithm>
using namespace std;

class alp{
public:
	int count, prior;
	friend bool operator<(alp obj1, alp obj2) {
		if (obj1.count == obj2.count) { return obj1.prior > obj2.prior; }
		return obj1.count < obj2.count;
	}
};
int main(int argc, char const *argv[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	alp arr[26];
	for (int i = 0; i < 26; i++){
		arr[i].count  = 0;
		arr[i].prior = i + 65;
	}
	string s;
	cin >> s;
	for (int i = 0; i < s.length(); i++) {
		arr[s[i] - 65].count++;
	}
	sort(arr, arr + 26);
	for(int i = 25; i >= 0; i--) {
		if (arr[i].count) { cout << arr[i].prior << ' ' << arr[i].count << '\n'; }
	}
	return 0; 
}