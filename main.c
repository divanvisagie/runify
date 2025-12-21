#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/args.h"
#include "src/futharks/futhark.h"

#define INITIAL_BUFFER_SIZE 1024

// Callback for listing futhark systems
static void print_system(const FutharkSystem *system, void *userdata) {
  (void)userdata;
  printf("%-8s %s\n", system->name, system->display_name);
}

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

int main(int argc, char **argv) {
  // Initialize the futhark registry
  futhark_registry_init();

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
    futhark_registry_list(print_system, NULL);
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

  // Get token mapper for the specified system
  TokenMapper *mapper = token_mapper_for_system(args->system, args->phonetic);

  if (!mapper) {
    fprintf(stderr, "Error creating TokenMapper for system '%s'\n", args->system);
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
    token_mapper_free(mapper);
    return 1;
  }

  // Print and free resources
  printf("%s", output);
  free(output);
  token_mapper_free(mapper);
  free(all_input);

  return 0;
}
