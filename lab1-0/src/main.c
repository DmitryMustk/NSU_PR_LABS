#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_PATTERN_SIZE 16
#define CHAR_SIZE 256

int fill_pattern(char *pattern) {
  for (int i = 0; i < MAX_PATTERN_SIZE + 1; i++) {
    if (fread(&pattern[i], sizeof(char), 1, stdin) != 1)
      return 0;
    if (pattern[i] == '\n') {
      pattern[i] = '\0';
      break;
    }
  }
  return 1;
}

int update_index(const char *buffer, const char *pattern, const int *shifts,
                 const int local_index, const int global_index) {
  int pattern_size = strlen(pattern);
  for (int i = 0; i < pattern_size; i++) {
    printf("%d ", global_index - i + 1);
    if (buffer[local_index - i] != pattern[pattern_size - 1 - i])
      return shifts[(int)buffer[local_index]];
  }
  return pattern_size;
}

void make_shift_table(int *shifts, const char *pattern) {
  int pattern_size = strlen(pattern);
  for (int i = 0; i < CHAR_SIZE; i++)
    shifts[i] = pattern_size;
  for (int i = 0; i < pattern_size - 1; i++)
    shifts[(int)pattern[i]] = pattern_size - i - 1;
}

void find_pattern(const char *pattern) {
  int pattern_size = strlen(pattern);
  int shifts[CHAR_SIZE];
  make_shift_table(shifts, pattern);
  char buffer[BUFFER_SIZE + 1];
  int end = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
  buffer[end] = '\0';
  if (end < pattern_size)
    return;
  int global_index = pattern_size - 1;
  int local_index = pattern_size - 1;
  while (1) {
    int delta =
        update_index(buffer, pattern, shifts, local_index, global_index);
    global_index += delta;
    local_index += delta;
    if (local_index % BUFFER_SIZE >= end)
      break;
    if (local_index % BUFFER_SIZE <= pattern_size - 1) {
      memcpy(buffer, &buffer[BUFFER_SIZE - pattern_size], pattern_size);
      end = fread(&buffer[pattern_size], sizeof(char),
                  BUFFER_SIZE - pattern_size, stdin) +
            pattern_size;
      buffer[end] = '\0';
      local_index = local_index % BUFFER_SIZE + pattern_size;
    }
  }
}

int main(void) {
  char pattern[MAX_PATTERN_SIZE + 1];
  if (!fill_pattern(pattern)) {
    return 0;
  }
  find_pattern(pattern);
  return 0;
}
