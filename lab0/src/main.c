#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMB_MAX_SIZE (int)13
#define MAX_BASE (int)16
#define MIN_BASE (int)2

int char_to_num(const char c){
    int num = -1;
    if(c >= '0' && c <= '9')
        num = c - '0';
    else if(c >= 'a' && c <= 'z')
        num = c - 'a' + 10;
    else if(c == '.')
        num = (int)'.';
    return num; 
}

int read_input(int* base1, int* base2, char* number){
    if(scanf("%d %d", base1, base2) != 2){
        return 0;
    }
    if(scanf("%13s", number) != 1){
        return 0;
    }
    return 1;
}

void to_lower_number(char* number){
    const size_t number_len = strlen(number);
    for(size_t i = 0; i < number_len; ++i){
        number[i] = tolower(number[i]);
    }
}

int is_digit_in_base1(const char* number, const int base1){
    const size_t number_len = strlen(number);
    for(size_t i = 0; i < number_len; ++i){
        int k = char_to_num(number[i]);
        if(k < 0 || (k >= base1 && k != (int)'.')){
            return 0;
        }
    }
    return 1;
}

int count_dots(const char* number){
    int dot_count = 0;
    const size_t number_len = strlen(number);
    for(size_t i = 0; i < number_len; ++i){
        if(number[i] == '.')
            dot_count++;
    }
    return dot_count;
}

int is_input_valid(int* base1, int* base2, char* number){
    if(!read_input(base1, base2, number)){
        return 0;
    }
    if(*base1 < MIN_BASE || *base1 > MAX_BASE || *base2 < MIN_BASE || *base2 > MAX_BASE){
        return 0;
    }

    to_lower_number(number);
    if(!is_digit_in_base1(number, *base1)){
        return 0;
    }

    if(number[strlen(number) - 1] == '.' || number[0] == '.'){
        return 0;
    }

    if(count_dots(number) > 1){
        return 0;
    }

    return 1;
}

int find_dot_index(const char* number){
    const size_t number_len = strlen(number);
    for(size_t i = 0; i < number_len; ++i){
        if(number[i] == '.')
            return i;
    }
    return (int)strlen(number);
}

long long int to_decimal(const char* number, const int base1, const int from, const int to){
    long long int decimal = 0;
    for(int i = from; i < to; ++i){
        decimal *= base1;
        decimal += char_to_num(number[i]);
    }
    return decimal;
}

//function returns the index of '\0'
int int_to_string(char* result, long long int decimal_int_part, const int base2){
    if(decimal_int_part == 0){
        result[0] = '0';
        result[1] = '\0';
        return 1;
    }

    size_t int_part_size = 0;
    for(size_t i = 0; decimal_int_part > 0; ++i){
        int mod = decimal_int_part % base2;
        decimal_int_part /= base2;
 
        if(mod < 10)
            result[i] = (char)mod + '0';
        else
            result[i] = (char)mod - 10 + 'A';
 
        int_part_size++;
    }
 
    for(size_t j = 0; j < int_part_size / 2; ++j){
        char buf = result[j];
        result[j] = result[int_part_size - j - 1];
        result[int_part_size - j - 1] = buf; 
    }
    result[int_part_size] = '\0';
    return int_part_size;
}

void fract_to_string(char* result, long long int decimal_fract_part, const int base2, const long long int base_pow){
    size_t i = 0;
    for(i = 0; i < NUMB_MAX_SIZE && decimal_fract_part > 0; ++i){ 
        decimal_fract_part *= base2;
        int mod = decimal_fract_part / base_pow;
        decimal_fract_part %= base_pow;
 
        if(mod < 10)
            result[i] = (char)mod + '0';
        else
            result[i] = (char)mod - 10 + 'A';
    }
    result[i] = '\0';
}

int translate_number(const char* number, char* result, const int base1, const int base2){
    int dot_index = find_dot_index(number);
    int number_len = (int)strlen(number);
    long long int decimal_int_part = to_decimal(number, base1, 0, dot_index);
    int int_part_size = int_to_string(result, decimal_int_part, base2);
    if(dot_index == number_len){
        return 1;
    }
    
    long long int decimal_fract_part = to_decimal(number, base1, dot_index + 1, number_len);
    const long long int base_pow = pow(base1, number_len - dot_index - 1);

    result[int_part_size] = '.';
    fract_to_string(result + int_part_size + 1, decimal_fract_part, base2, base_pow);
    return 1;
}

int main(void){
    int base1, base2;
    char number[NUMB_MAX_SIZE + 1];
    if(!is_input_valid(&base1, &base2, number)){
        printf("bad input");
        return 0;
    }

    char result[NUMB_MAX_SIZE * NUMB_MAX_SIZE] = { 0 };
    if(!translate_number(number, result, base1, base2)){
        return 0;
    }
    printf("%s", result);
    return 0;
}
