#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"

Args* parse_args(int argc, char **argv) {
  Args *args = malloc(sizeof(Args));
  args->help = false;
  args->list = false;
  args->system = "younger";

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      args->help = true;
    }
    if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--list") == 0) {
      args->list = true;
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
