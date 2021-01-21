#include <stdio.h>

int arr[13];
int ans[6];
void comb(int id, int level, int len){
	if (level == 6) {
		for (int i = 0; i < 6; i++) { printf("%d ",ans[i]); }
		printf("\n");
		return;
	}
	for (int i = id; i <= len - 6 + level; i++){
		ans[level] = arr[i];
		comb(i + 1, level + 1, len);
	}
}
int main(int argc, char const *argv[]) {
	int k;
	while (scanf("%d", &k) == 1) {
		if (!k) { return 0; }
		for (int i = 0; i < k; i++) { scanf("%d", arr + i); }
		comb(0, 0, k);
		printf("\n");
	}
	return 0;
}