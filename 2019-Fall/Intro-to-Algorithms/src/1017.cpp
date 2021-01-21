#include <iostream>

int group[100001],count[100001];
int FindGroup(int key) {
	while (key != group[key]) { key = group[key]; }
	return key;
}
void UNION(int key1,int key2) {
	if (key1 < key2) { group[key2] = key1; }
	else { group[key1] = key2; }
	count[key1] += count[key2];
	count[key2] = count[key1];
}
int main(int argc, char const *argv[]) {
	int n, m, a, b;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		group[i] = i;
		count[i] = 1;
	}
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		a = FindGroup(a);
		b = FindGroup(b);
		if(a != b) { UNION(a,b); }
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", count[FindGroup(i)] - 1);
	}
	printf("\n");
	return 0;
}