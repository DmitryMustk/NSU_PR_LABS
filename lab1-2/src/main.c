#include <stdlib.h>
#include <stdio.h>

#define SAMPLE_SIZE 16
#define BUFFER_SIZE 1024

void prefix(const int n, const char* s, char* shift_table) {
    shift_table[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = shift_table[i - 1];
        while ((j > 0) && (s[i] != s[j]))
            j = shift_table[j - 1];
        if (s[i] == s[j])
            ++j;
        shift_table[i] = j;
    }
}

void KMPSearch(const char* sample, const int sample_size) {
    char text[BUFFER_SIZE];
    int text_len = fread(text, sizeof(char), BUFFER_SIZE, stdin);
    char shift_table[SAMPLE_SIZE];
    prefix(sample_size, sample, shift_table);
    for (int i = 0; i < sample_size; i++)
        printf("%d ", shift_table[i]);
    printf("\n");
    if (sample_size > text_len)
        return;
    int text_pos = 0, buf_pos = 0, shift;
    while (sample_size <= text_len) {
        int matches = 0;
        while (sample[matches] == text[buf_pos + matches]) {
            matches++;
            if (matches >= sample_size)
                break;
        }
        if (matches != 0) {
            printf("%d %d ", text_pos + 1, matches);
            shift = matches - shift_table[matches - 1];
        }
        else
            shift = 1;
        int next_shift = buf_pos + shift;
        if (sample_size + next_shift > text_len) {
            int size = text_len - next_shift;
            for (int i = 0; i < size; i++)
                text[i] = text[next_shift + i];
            text_len = size + fread(&text[size], sizeof(char), BUFFER_SIZE - size, stdin);
            buf_pos = 0;
        }
        else
            buf_pos += shift;
        text_pos += shift;
    }
}

int main(void) {
    char sample[SAMPLE_SIZE + 2];
    if (fgets(sample, SAMPLE_SIZE + 2, stdin) == NULL) {
        printf("bad input");
        return 0;
    }
    int sample_size = 0;
    while (sample[sample_size] != '\n')
        sample_size++;
    KMPSearch(sample, sample_size);
    return 0;
}
