#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "default.h"

int main(int argc, char **argv) {
  // read string piped in from stdin
  char *input = "helloworld";
  size_t len = 0;
  ssize_t read;

  // TODO: if you for example pipe ls in, this will only get the first item
  // so we need some better input handling here
  read = getline(&input, &len, stdin);
  if (read == -1) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }

  printf("raw input was: '%s'\n", input);
  // TODO: Update algorithm to handle newlines and other unexpected chars
  input[strcspn(input, "\n")] = 0; // Trim newlines from input

  printf("trimmed input was: '%s'\n", input);

  // create a new TokenMapper
  TokenMapper *mapper = token_mapper_new();
  if (!mapper) {
    fprintf(stderr, "Error creating TokenMapper\n");
    return 1;
  }
  //
  // transliterate the input string
  printf("Going to transliterate\n");
  char *output = to_fut(mapper, input);
  if (!output) {
    fprintf(stderr, "Error transliterating input\n");
    return 1;
  }
  // print the output string
  printf("%s\n", output);
}
