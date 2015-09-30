#include <stdio.h>
int longestIncreasingRun(int array[], int length);



int main(){
    int arr[] = {3, 2, 4, 8, 8, 7, 9, 1,4};
    printf("The length of the longest increasing run is %d\n",longestIncreasingRun(arr,9));



    return 0;
}
int longestIncreasingRun(int array[], int length) {
    int longest = 0,i;
    for (i = 0;i<length-1;i++){
        if (array[i] - array[i+1]>longest)longest = array[i] - array[i+1];
    }

    return longest;

}
