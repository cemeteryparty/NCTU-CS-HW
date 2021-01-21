#include <iostream>

int arr[2500],n;
bool findAns(int pos,int tar,int len){
	if(!tar && len == 4)
		return true;
	if(len > 4 || pos >= n)
		return false;
	return findAns(pos + 1,tar - arr[pos],len + 1) || findAns(pos + 1,tar,len);
}
int main(int argc,char* const argv[]){
	scanf("%d",&n);
	for(int i = 0;i < n;i++)
		scanf("%d",(arr + i));
	printf(findAns(0,0,0)?"1\n":"0\n");
	return 0;
}