#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR_SIZE 2000000
 
int* create_arr(const int arr_size){
    return (int*)malloc(arr_size * sizeof(int));
}
 
int fill_arr(int* arr, const int arr_size){
    for(int i = 0; i < arr_size; ++i){
        if(scanf("%d", &arr[i]) != 1){
            return 0;
        }
    }
    return 1;
}
 
void print_arr(int* arr, const int arr_size){
    for(int i = 0; i < arr_size; ++i){
        printf("%d ", arr[i]);
    }
}
 
void destroy_arr(int* arr){
    free(arr);
}
 
void swap(int* a, int* b){
    const int buf = *a;
    *a = *b;
    *b = buf;
}
 
void quick_sort_recursion(int* arr, const int low, const int high){
    const int pivot_index = (low + high) / 2;
    int i = low, j = high;
    while(i < j){
        while(arr[i] < arr[pivot_index]) {i++;}
        while(arr[j] > arr[pivot_index]) {j--;}
        if(i <= j){
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
 
    }
    if(low < j)
        quick_sort_recursion(arr, low, j);
    if(i < high)
        quick_sort_recursion(arr, i, high);
}
 
int main(void) {
    int arr_size;
    if(scanf("%d", &arr_size) != 1 || arr_size < 0 || arr_size > MAX_ARR_SIZE){
        return 0;
    }
 
    int* arr = create_arr(arr_size);
    if(arr == NULL){
        return 0;
    }
    if(!fill_arr(arr, arr_size)){
        destroy_arr(arr);
        return 0;
    }
 
    quick_sort_recursion(arr, 0, arr_size - 1);
    print_arr(arr, arr_size);
    destroy_arr(arr);
    return 0;
}
