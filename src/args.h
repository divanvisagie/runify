#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

#define RUNIFY_VERSION "1.0.0"

typedef struct {
  bool help;
  bool list;
  bool version;
  bool reverse;
  bool phonetic;
  char* system;
  char* error;
} Args;

Args* parse_args(int argc, char **argv);

#endif // ARGS_H
