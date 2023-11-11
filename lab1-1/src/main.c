#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERN_SIZE 16

int fill_pattern(char *pattern) {
  for (int i = 0; i < MAX_PATTERN_SIZE + 1; ++i) {
    if (fread(&pattern[i], sizeof(char), 1, stdin) != 1)
      return 0;
    if (pattern[i] == '\n') {
      pattern[i] = '\0';
      break;
    }
  }
  return 1;
}

int fast_pow(const int base, const int power) {
  if (power == 0)
    return 1;
  if (power % 2 == 1)
    return base * fast_pow(base * base, power / 2);
  return fast_pow(base * base, power / 2);
}

int get_hash(const char *string, const int len) {
  int hash = 0;
  for (int i = 0; i < len; ++i)
    hash += ((unsigned int)string[i] % 3) * fast_pow(3, i);
  return hash;
}

void update_hash(int *hash, const char *buffer, const int pattern_size,
                 const int index) {
  *hash -= (unsigned int)buffer[index] % 3;
  *hash /= 3;
  *hash += ((unsigned int)buffer[index + pattern_size] % 3) *
           fast_pow(3, pattern_size - 1);
}

void compare(const char *buffer, const char *pattern, const int pattern_size,
             const int index) {
  for (int i = 0; i < pattern_size; ++i) {
    printf("%d ", index + 1 + i);
    if (buffer[index % pattern_size + i] != pattern[i])
      return;
  }
}

void find_pattern(const char *pattern, const int pattern_hash) {
  int pattern_size = strlen(pattern);
  char buffer[pattern_size * 2 + 1];
  char *buffer_r = buffer + pattern_size;
  int end = fread(buffer, sizeof(char), pattern_size * 2, stdin);
  buffer[end] = '\0';

  if (strlen(buffer) < strlen(pattern))
    return;

  int buffer_hash = get_hash(buffer, pattern_size);
  int index = 0;
  while (1) {
    for (int i = 0; i < pattern_size; ++i) {
      if (buffer_hash == pattern_hash)
        compare(buffer, pattern, pattern_size, index);
      if (buffer[i + pattern_size] == '\0')
        return;
      update_hash(&buffer_hash, buffer, pattern_size, i);
      index++;
    }
    memcpy(buffer, buffer_r, pattern_size);
    int end = fread(buffer_r, sizeof(char), pattern_size, stdin);
    buffer_r[end] = '\0';
  }
}

int main(void) {
  char pattern[MAX_PATTERN_SIZE + 1];
  if (!fill_pattern(pattern))
    return 0;

  int pattern_hash = get_hash(pattern, strlen(pattern));
  printf("%d ", pattern_hash);

  find_pattern(pattern, pattern_hash);
  return 0;
}
