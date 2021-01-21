#include <iostream>
#include <ctime>

void merge(int *array,int left,int mid,int right){//mid = rsub.begin()
    int temp[right - left + 1],i = left,j = mid,k = 0;
    //i = lsub.begin(),j = rsub.begin(),k = temp.begin()
    while((i < mid) && (j <= right)){
        if(array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }
    while(i < mid)
        temp[k++] = array[i++];
    while(j <= right)
        temp[k++] = array[j++];
    for(int i = 0;i <= right - left;i++)
        array[left + i] = temp[i];
}
void mergesort(int *array,int left,int right){
    int mid = ((left + right) >> 1);
    if(left < right){
        mergesort(array,left,mid);
        mergesort(array,mid + 1,right);
        merge(array,left,mid + 1,right);
    }
}
int main(int argc, char const *argv[]){
    srand(time(NULL));
    int arr[10];
    for(int i = 0;i < 10;i++){
        arr[i] = rand() % 10;
        printf("%d ",arr[i]);
    }    
    printf("\n");
    mergesort(arr,0,9);
    for(int i = 0;i < 10;i++)
        printf("%d ",arr[i]);
    printf("\n");
    return 0; 
 }