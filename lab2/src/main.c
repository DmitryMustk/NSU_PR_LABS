#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_STR_SIZE 100
 
 
int is_char_unique(const char* str, const char c){
    int count = 0;
    const size_t str_len = strlen(str);
    for(size_t i = 0; i < str_len; ++i){
        if(str[i] == c)
            count++;
        if(count > 1)
            return 0;
    }
    return 1;
}
 
int is_str_correct(const char* str){
    const size_t str_len = strlen(str);
    for(size_t i = 0; i < str_len; ++i){
        if((str[i] < '0' || str[i] > '9') || !is_char_unique(str, str[i]))
            return 0;
    }
    return 1;
}

int read_input(char* str, int* n){
    if(scanf("%99[^\r\n]", str) != 1){
        return 0;
    }
    if(scanf("%d", n) != 1 || *n < 0){
        return 0;
    }
    return 1;
}
 
int is_input_correct(char* str, int* n){
    read_input(str, n);
    if(!is_str_correct(str) || *n < 0){
        return 0;
    }
    return 1;   
}
 
void swap(char* str, const int i, const int j){
    const char buf = str[i];
    str[i] = str[j];
    str[j] = buf;
}
 
void reverse(char* str, const unsigned int from, const unsigned int size){
    if(!from)
        return;
    for(size_t i = from; i < (size - from) / 2 + 1; ++i){
        swap(str, i, size - i);
    }
}
 
int next_permutation(char* str, const int size){
    int i = -1, j = -1;
    for(int k = size - 2; k >= 0; --k){
        if(str[k] < str[k + 1]){
            i = k;
            break;
        }
    }
    if(i == -1)
        return 0;
 
    for(int l = size - 1; l >= 0; --l){
        if(str[l] > str[i]){
            j = l;
            break;
        }
    }
    if(j == -1)
        return 0;
    swap(str, i, j);
    reverse(str, i + 1, size);
    return 1;  
}
 
int main(void){
    char str[MAX_STR_SIZE];
    int n;
    if(!is_input_correct(str, &n)){
        printf("bad input\n");
        return 0;
    }
 
    const int size = (int)strlen(str);
    if(size > 1){
        for(int i = 0; next_permutation(str, size) && i < n; ++i){
            printf("%s\n", str);
        }
    }
    return 0;
}
