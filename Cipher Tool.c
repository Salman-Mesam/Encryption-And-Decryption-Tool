//Mohammad Salman Mesam
//260860161

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void errorMsg(char *msg) {
  printf("%s\n\n"
         "./cipher SWITCH KEY LENGTH < FILENAME\n\n"
         "./cipher -e 10 100 < filename.txt\n"
         "./cipher -d 10 200 < filename.e\n",
         msg);
}

void encrypt(int key, int length) {
  char matrix[500][500];
  char inputData[500];

  memset(matrix, 0, sizeof(matrix));
  memset(inputData, 0, sizeof(inputData));

  for (int i = 0; i < length; i++) {
    const char c = getc(stdin);
    inputData[i] = c;
  }

  for (int i = 0; i < length; i++) {
    matrix[i / key][i % key] = inputData[i];
  }

  for (int w = 0; w < key; w++) {
    for (int h = 0; h <= length / key; h++) {
      if (matrix[h][w] != 0) {
        putc(matrix[h][w], stdout);
      } else {
        putc(' ', stdout);
      }
    }
  }
  //   putc('\n', stdout);
}

void decrypt(int key, int length) {
  char matrix[500][500];
  char inputData[500];

  memset(matrix, 0, sizeof(matrix));
  memset(inputData, 0, sizeof(inputData));

  for (int w = 0; w < key; w++) {
    for (int h = 0; h <= length / key; h++) {
      char c = getc(stdin);
      if (c != EOF) {
        matrix[h][w] = c;
      }
    }
  }

  for (int i = 0; i < length; i++) {
    inputData[i] = matrix[i / key][i % key];
  }

  puts(inputData);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    errorMsg("This program expects 3 valid arguments SWITCH KEY LENGTH");
    exit(1);
  }

  char switch_ = argv[1][1];
  int key = atoi(argv[2]);
  size_t len = atoi(argv[3]);

  if (!(0 < len && len < 500)) {
    errorMsg("LENGTH must between 1 (inclusive) and 500 (exclusive)");
    exit(1);
  }

  if (!(0 < key && key < len)) {
    errorMsg("KEY must between 1 (inclusive) and less than the LENGTH");
    exit(1);
  }

  switch (switch_) {
  case 'e': {
    encrypt(key, len);
    break;
  }
  case 'd': {
    decrypt(key, len);
    break;
  }
  default: {
    errorMsg("Only '-e' and '-d' are the allowed SWITCHES");
    exit(1);
  }
  }
}
