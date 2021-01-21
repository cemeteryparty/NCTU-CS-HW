#include <iostream>
#include <algorithm>
#include <ctime>

int arr[10];
void quicksort(int l,int r){
    //pivot = arr[r - 1]
    if(l >= r)
        return;
    int i = l;
    for(int j = l;j < r - 1;j++)
        if(arr[j] <= arr[r - 1]){
            std::swap(arr[i],arr[j]);
            i++;
        }
    std::swap(arr[i],arr[r - 1]);
    quicksort(l,i);
    quicksort(i + 1,r);
}
int main(int argc, char const *argv[]){
    srand(time(NULL));
    for(int i = 0;i < 10;i++){
        arr[i] = rand() % 10;
        printf("%d ",arr[i]);
    }    
    printf("\n");
    quicksort(0,10);
    for(int i = 0;i < 10;i++)
        printf("%d ",arr[i]);
    printf("\n");
    return 0;
}