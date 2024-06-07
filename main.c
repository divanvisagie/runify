#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *translate(char *input) {
  char *result = malloc(strlen(input) + 1);
  strcpy(result, input);

  char *latinCharacters[] = {
      "f",  "u",   "þ",  "a",  "r",   "k",   "c",   "g",   "w",  "h",
      "n",  "i",   "j",  "y",  "æ",   "ï",   "p",   "z",   "s",  "t",
      "b",  "e",   "m",  "l",  "ŋ",   "o",   "d",   "v",   "ð",  "x",
      "ch", "ij",  "cc", "th", "eau", "chr", "ing", "chl", "ng", "chj",
      "nk", "chw", "ei", "ø",  "å",   "q",   NULL};
  char *elderFutharkCharacters[] = {
      "ᚠ", "ᚢ",  "ᚦ", "ᚨ",  "ᚱ",  "ᚲ",  "ᚲ", "ᚷ",  "ᚹ",  "ᚺ", "ᚾ", "ᛁ",
      "ᛃ", "ᛃ",  "ᛇ", "ᛇ",  "ᛈ",  "ᛉ",  "ᛋ", "ᛏ",  "ᛒ",  "ᛖ", "ᛗ", "ᛚ",
      "ᛜ", "ᛟ",  "ᛞ", "ᚠ",  "ᚦ",  "ᚲᛋ", "ᚷ", "ᛖ",  "ᚲᛋ", "ᚦ", "ᛟ", "ᚺᚱ",
      "ᛜ", "ᚺᛚ", "ᛜ", "ᚺᛃ", "ᛜᚲ", "ᚺᚹ", "ᛋ", "ᛟᛖ", "ᚨᚨ", "ᚲ", NULL};

  for (int i = 0; latinCharacters[i] != NULL; i++) {
    printf("i: %d\n", i);
    char *ptr = result;
    while ((ptr = strstr(ptr, latinCharacters[i])) != NULL) {
      printf("ptr: %s\n", ptr);
      char *temp = malloc(strlen(result) - strlen(latinCharacters[i]) +
                          strlen(elderFutharkCharacters[i]) + 1);
      printf("temp: %s\n", temp);
      break;
      // strncpy(temp, result, ptr - result);
      // temp[ptr - result] = '\0';
      // sprintf(temp + (ptr - result), "%s%s", elderFutharkCharacters[i],
      //         ptr + strlen(latinCharacters[i]));
      // // free(result);
      // result = temp;
    }
  }

  return result;
}

void translate_file(char *filename) {
  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    char line[1000];
    while (fgets(line, sizeof line, file) != NULL) {
      char *translated = translate(line);
      printf("%s", translated);
      free(translated);
    }
    fclose(file);
  } else {
    perror(filename);
  }
}

int main(int argc, char **argv) {
  // read from standard input
  if (argc == 1) {
    puts("Enter text to translate:");
    char line[1000];
    while (fgets(line, sizeof line, stdin) != NULL) {
      printf("%s", line);
      char *translated = translate(line);
      printf("Translated: %s", translated);
      // free(translated);
    }
    return 0;
  }
}
