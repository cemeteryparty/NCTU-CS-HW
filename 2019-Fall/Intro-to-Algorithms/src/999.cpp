#include <iostream>

int main(int argc, char const *argv[]) {
	int n, ans = -1000000, num;
	scanf("%d", &n);
	while (n--) {
		scanf("%d" ,&num);
		if(num > ans) { ans = num; }
	}
	printf("%d\n", ans);
	return 0;
}