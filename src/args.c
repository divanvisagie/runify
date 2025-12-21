#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"

bool is_valid_system(const char* system) {
  return strcmp(system, "elder") == 0 || strcmp(system, "younger") == 0;
}

Args* parse_args(int argc, char **argv) {
  Args *args = malloc(sizeof(Args));
  args->help = false;
  args->list = false;
  args->version = false;
  args->reverse = false;
  args->phonetic = true;  // phonetic mode on by default
  args->system = "younger";
  args->error = NULL;

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

    // Handle --system=value format
    if (strstr(argv[i], "--system=") != NULL) {
      args->system = argv[i] + 9;  // skip "--system="
    }
    // Handle -s value and --system value formats
    if ((strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--system") == 0) && i + 1 < argc) {
      args->system = argv[i + 1];
      i++;  // skip next arg since we consumed it
    }
  }

  // Validate system parameter
  if (!is_valid_system(args->system)) {
    args->error = malloc(256);
    snprintf(args->error, 256, "Unknown rune system: '%s'. Use 'elder' or 'younger'.", args->system);
  }

  return args;
}
