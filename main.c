#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "default.h"

#define INITIAL_BUFFER_SIZE 1024

char *get_help() {
  char *help = "Usage: runify [OPTION]...\n"
               "Transliterate Latin text to Futhark runes.\n"
               "\n"
               "Options:\n"
               "  -h, --help              Display this help and exit\n"
               "  -v, --version           Display version and exit\n"
               "  -l, --list              List rune systems\n"
               "  -s, --system=SYSTEM     Specify rune system (elder, younger)\n"
               "  -p, --phonetic          Enable phonetic mode (default)\n"
               "      --no-phonetic       Disable phonetic mode\n"
               "\n"
               "Examples:\n"
               "  echo 'hello' | runify -s elder           # ᚺᛖᛚᛚᛟ\n"
               "  echo 'thing' | runify -s elder           # ᚦᛁᛜ (phonetic)\n"
               "  echo 'thing' | runify --no-phonetic      # ᛏᚺᛁᛜ\n";
  return help;
}

char *list_rune_systems() {
  char *systems = "elder:   Elder Futhark\n"
                  "younger: Younger Futhark\n";
  return systems;
}

int main(int argc, char **argv) {
  Args *args = parse_args(argc, argv);
  if (args->help) {
    char *help = get_help();
    printf("%s\n", help);
    return 0;
  }

  if (args->version) {
    printf("runify %s\n", RUNIFY_VERSION);
    return 0;
  }

  if (args->list) {
    char *systems = list_rune_systems();
    printf("%s\n", systems);
    return 0;
  }

  if (args->error) {
    fprintf(stderr, "Error: %s\n", args->error);
    return 1;
  }

  size_t buffer_size = INITIAL_BUFFER_SIZE;
  char *all_input = malloc(buffer_size);
  if (!all_input) {
    perror("malloc");
    return 1;
  }
  all_input[0] = '\0'; // Initialize empty string

  size_t len = 0;
  ssize_t read;
  char *line = NULL;

  while ((read = getline(&line, &len, stdin)) != -1) {
    size_t current_len = strlen(all_input);
    size_t total_len = current_len + read;
    if (total_len >= buffer_size) {
      buffer_size *= 2;
      all_input = realloc(all_input, buffer_size);
      if (!all_input) {
        perror("realloc");
        free(line);
        return 1;
      }
    }
    strncat(all_input, line, read);
  }

  free(line);

  // Select the rune system based on system and phonetic flags
  TokenMapper *mapper = NULL;
  if (strcmp(args->system, "elder") == 0) {
    mapper = args->phonetic ? token_mapper_elder_new() : token_mapper_elder_basic_new();
  } else {
    // Default to younger
    mapper = args->phonetic ? token_mapper_younger_new() : token_mapper_younger_basic_new();
  }

  // Map and transliterate input
  if (!mapper) {
    fprintf(stderr, "Error creating TokenMapper\n");
    free(all_input);
    return 1;
  }

  char *output;
  if (args->reverse) {
    output = from_fut(mapper, all_input);
  } else {
    output = to_fut(mapper, all_input);
  }

  if (!output) {
    fprintf(stderr, "Error transliterating input\n");
    free(all_input);
    free(mapper);
    return 1;
  }

  // Print and free resources
  printf("%s", output);
  free(output);
  free(mapper);
  free(all_input);

  return 0;
}
