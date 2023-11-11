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
    printf("\n");
}
 
void destroy_arr(int* arr){
    free(arr);
}
 
void swap(int* a, int* b){
    const int buf = *a;
    *a = *b;
    *b = buf;
}
 
int max(int* arr, const int arr_size, const int i, const int j, const int k){
    int max = i;
    if(j < arr_size && arr[j] > arr[max])
        max = j;
    if(k < arr_size && arr[k] > arr[max])
        max = k;
    return max;
}
 
void down_heap(int* arr, const int arr_size, int i){
    while(1){
        int j = max(arr, arr_size, i, 2 * i + 1, 2 * i + 2);
        if(j == i)
            break;
        swap(&arr[i], &arr[j]);
        i = j;
    }
}
 
void heap_sort(int* arr, const int arr_size){
    for(int i = (arr_size - 2) / 2; i >= 0; --i){
        down_heap(arr, arr_size, i);
    }
    for(int i = 0; i < arr_size; ++i){
        swap(&arr[arr_size - i - 1], &arr[0]);
        down_heap(arr, arr_size - i - 1, 0);
    }
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
        free(arr);
        return 0;
    }
 
    heap_sort(arr, arr_size);
    print_arr(arr, arr_size);
    destroy_arr(arr);
    return 0;
}
