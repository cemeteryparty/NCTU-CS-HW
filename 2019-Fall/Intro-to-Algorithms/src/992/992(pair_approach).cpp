#include <iostream>
#include <algorithm>
// ref:
// https://www.geeksforgeeks.org/find-four-elements-that-sum-to-a-given-value-set-2/
class Pair{
	public:
		int sum;
		int index;
		friend bool operator<(const Pair& p1,const Pair& p2){
			return p1.sum < p2.sum;
		}
};
int main(int argc, char const *argv[]){
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
	if(zero >= 4){//if there has 4 zero
		printf("1\n");
		return 0;
	}
	if(pos_max == -1 || neg_min == 1){//all pos or all neg
		printf("0\n");
		return 0;
	}
	int k = 0,nc = 0,pc = 0;
	Pair parr[n * (n - 1) / 2];
	for(int i = 0;i < n;i++)
		for(int j = i + 1;j < n;j++){
			parr[k].sum = arr[i] + arr[j];
			if(parr[k].sum > 0)
				pc++;
			else if(parr[k].sum < 0)
				nc++;
			parr[k++].index = i * 10000 + j;
		}
	std::sort(parr,parr + k);
	int l = 0,r = k - 1;
	while(l < r){
		int sum = parr[l].sum + parr[r].sum;
		if(!sum){
			int x = parr[l].index / 10000,y = parr[l].index % 10000,i = parr[r].index / 10000,j = parr[r].index % 10000;
			if(x != i && x != j && y != i && y != j){
				noAns = false;
				break;
			}
		}
		//doing high speed iterating
		//move iterator for len / 2 steps
		//if sum(before_move) & sum(after_move) are both pos or neg,then move
		//else move 1 step only
		if(sum < 0){
			if(parr[l + (nc >> 1)].sum + parr[r].sum < 0 && nc > 0){
				l += (nc >> 1);
				nc >>= 1;
			}   
			else{
				nc--;
				l++;
			}
		}
		else{
			if(parr[l].sum + parr[r - (pc >> 1)].sum >= 0 && pc > 0){
				r -= (pc >> 1);
				pc >>= 1;
			}
			else{
				pc--;
				r--;
			}
		}
	}
	printf(noAns?"0\n":"1\n");
	return 0;
}
