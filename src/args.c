#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"

Args* parse_args(int argc, char **argv) {
  Args *args = malloc(sizeof(Args));
  args->help = false;
  args->list = false;
  args->version = false;
  args->reverse = false;
  args->phonetic = true;  // phonetic mode on by default
  args->system = "younger";

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      args->help = true;
    }
    if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--list") == 0) {
      args->list = true;
    }
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
      args->version = true;
    }
    if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--reverse") == 0) {
      args->reverse = true;
    }
    if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--phonetic") == 0) {
      args->phonetic = true;
    }
    if (strcmp(argv[i], "--no-phonetic") == 0) {
      args->phonetic = false;
    }

    // look for system={{system}}
    if (strstr(argv[i], "system=") != NULL) {
      char *system = strtok(argv[i], "=");
      system = strtok(NULL, "=");
      args->system = system;
    }
    if (strcmp(argv[i], "-s") == 0) {
      args->system = argv[i + 1];
    }
  }
  return args;
}
