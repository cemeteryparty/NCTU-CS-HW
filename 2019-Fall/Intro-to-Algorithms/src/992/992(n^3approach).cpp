#include <iostream>
#include <algorithm>
// ref:
// https://www.geeksforgeeks.org/find-four-numbers-with-sum-equal-to-given-sum/
int main(int argc,char* const argv[]){
	int n,pos_max = -1,neg_min = 1,zero = 0;
	bool noAns = true;
	scanf("%d",&n);
	int arr[n];
	for(int i = 0;i < n;i++){
		scanf("%d",(arr + i));
		if(!arr[i])
			zero++;
		else if(arr[i] > pos_max)
			pos_max = arr[i];    
		else if(arr[i] < neg_min)
			neg_min = arr[i];  
	}
	if(zero >= 4){
		printf("1\n");
		return 0;
	}
	if(pos_max == -1 || neg_min == 1){
		printf("0\n");
		return 0;
	}
	std::sort(arr,arr + n);
	for(int i = 0;i <= n - 4 && noAns && arr[i] < 0;i++)
		for(int j = i + 1;j <= n - 3 && noAns && arr[i] + arr[j] < 0;j++){
			int l = j + 1,r = n - 1;
			while(l < r){
				int sum = arr[i] + arr[j] + arr[l] + arr[r];
				if(!sum){
					noAns = false;
					break;
				}
				if(sum < 0)
					l++;
				else
					r--;
			}
		}
	printf(noAns?"0\n":"1\n");
	return 0;
}