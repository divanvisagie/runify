#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "default.h"

char* get_help() {
  char* help = "Usage: runify [OPTION]... [STRING]\n"
               "Transliterate a string from Latin characters to Elder Futhark characters.\n"
               "\n"
               "Options:\n"
               "  -h, --help              Display this help and exit\n"
               "  -l, --list              List rune systems\n"
               "  -s, --system=SYSTEM\n   Specify rune system to use\n"
               "\n"
               "Examples:\n"
               "  runify hello world\n"
               "  runify -h\n";
  return help;
}

char* list_rune_systems() {
  char* systems = "elder:   Elder Futhark\n"
                  "younger: Younger Futhark\n";
  return systems;
}

int main(int argc, char **argv) {
  // if arg is for help
  if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
    char *help = get_help();
    printf("%s\n", help);
    return 0;
  }

  //if list
  if (argc == 2 && (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0)) {
    char *systems = list_rune_systems();
    printf("%s\n", systems);
    return 0;
  }

  //get the system flag value if it exists or set the default
  char *system = "elder";
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--system") == 0) {
      system = argv[i + 1];
    }
  }

  char *input = "No input was provided";
  size_t len = 0;
  ssize_t read;

  char all_input[1000];
  // TODO: if you for example pipe ls in, this will only get the first item
  // so we need some better input handling here
  // Read lines from stdin until EOF
  while ((read = getline(&input, &len, stdin)) != -1) {
    size_t input_len = strlen(input);
    strncat(all_input, input, input_len);
  }

  // trim last newline from input
  input[strcspn(input, "\n")] = 0;

  TokenMapper *mapper = token_mapper_elder_new();
  if (strcmp(system, "younger") == 0) {
    mapper = token_mapper_younger_new();
  }

  if (!mapper) {
    fprintf(stderr, "Error creating TokenMapper\n");
    return 1;
  }
  char *output = to_fut(mapper, all_input);
  if (!output) {
    fprintf(stderr, "Error transliterating input\n");
    return 1;
  }
  printf("%s\n", output);

  free(output);
  free(mapper);

}

