#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
// ref:
// https://www.geeksforgeeks.org/find-four-elements-sum-given-value-set-3-hashmap/
int main(int argc, char const *argv[]){
	std::unordered_map<int,std::vector<int> > m;
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
	for(int i = 0;i < n && noAns;i++)
		for(int j = i + 1;j < n;j++){
			int sum = arr[i] + arr[j];
			if(sum >= 0){
				std::unordered_map<int,std::vector<int> >::iterator it = m.find(0 - sum);
				if(it != m.end())//maybe have ans
					for(int vi = 0;vi < it->second.size();vi++){
						int x = it->second[vi] / 10000,y = it->second[vi] % 10000;
						if(x != i && x != j && y != i && y != j){
							noAns = false;
							break;
						}
					}
			}
			m[sum].push_back(i * 10000 + j);
		}
	printf(noAns?"0\n":"1\n");
	return 0;
}