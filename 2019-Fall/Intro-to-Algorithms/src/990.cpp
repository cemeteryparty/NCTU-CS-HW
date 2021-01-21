#include <iostream>
#include <algorithm>
// ref:
// http://mypaper.pchome.com.tw/zerojudge/post/1326151101
// same technique in "984 Assignment 3 - Inversions"
class Dot{
public:
	int x, y, id;
	friend bool operator<(const Dot & d1, const Dot & d2) {
		return d1.x < d2.x || (d1.x == d2.x?d1.y < d2.y:false);
	}
};
int ans[300001];
void merge(Dot *array, int left, int mid, int right){
	Dot temp[right - left + 1];
	int i = left, j = mid, k = 0, v = 0;
	while ((i < mid) && (j <= right)) {
		if (array[i].y <= array[j].y) {
			temp[k++] = array[i++];
			v++;
		}
		else {
			ans[array[j].id] += v;
			temp[k++] = array[j++];
		}
	}
	while (i < mid) { temp[k++] = array[i++]; }
	while (j <= right) {
		ans[array[j].id] += v;
		temp[k++] = array[j++];
	}
	for (int i = 0; i <= right - left; i++) {
		array[left + i] = temp[i];
	}
}
void mergesort(Dot *array,int left,int right){
	int mid = ((left + right) >> 1);
	if(left < right){
		mergesort(array,left,mid);
		mergesort(array,mid + 1,right);
		merge(array,left,mid + 1,right);
	}
}
int main(int argc, char const *argv[]) {
	int n;
	scanf("%d", &n);
	Dot arr[n];
	for (int i = 0; i < n; i++){
		scanf("%d%d", &arr[i].x, &arr[i].y);
		arr[i].id = i;
		ans[i] = 0;
	}
	std::sort(arr, arr + n); // sort dot
	mergesort(arr, 0, n - 1); // sort y
	for(int i = 0; i < n; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0; 
}