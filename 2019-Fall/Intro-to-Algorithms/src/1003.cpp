#include <iostream>
#include <algorithm>
#include <vector>

class Point {
public:
	int x, y, idx;
	bool isDominated;
	friend bool operator<(const Point & p1, const Point & p2) {
		return p1.x < p2.x || (p1.x == p2.x?p1.y < p2.y:false);
	}
};
int n;
Point arr[1500000];
void merge(int l, int m, int r){
	Point temp[r - l + 1];
	int i = l, j = m + 1, k = 0;
	while ((i <= m) && (j <= r)) {
		if (arr[i].y < arr[j].y) {
			arr[i].isDominated = true;
			temp[k++] = arr[i++];
		}
		else if (arr[i].y == arr[j].y) {
			if (arr[i].x < arr[j].x) { arr[i].isDominated = true; }
			temp[k++] = arr[i++];
		}
		else { temp[k++] = arr[j++]; }
	}
	while (i <= m) { temp[k++] = arr[i++]; }
	while (j <= r) { temp[k++] = arr[j++]; }
	for (int x = 0; x < k; x++) { arr[l + x] = temp[x];	}
}
void mergesort(int l, int r) {
	if (l >= r) { return; }
	int m = (l + r) >> 1;
	mergesort(l, m);
	mergesort(m + 1, r);
	merge(l, m, r);
}
int main(int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d",&arr[i].x, &arr[i].y);
		arr[i].isDominated = false;
		arr[i].idx = i + 1;
	}
	std::sort(arr, arr + n);
	mergesort(0, n - 1);
	std::vector<int> v;
	for (int i = 0; i < n; i++) {
		if (!arr[i].isDominated) { v.push_back(arr[i].idx); }
	}
	std::sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) { printf("%d ", v[i]); }
	printf("\n");
	return 0;
}